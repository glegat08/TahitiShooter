#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "SceneBase.h"

Game::Game(sf::RenderWindow* window, const float& framerate)
	: SceneBase(window, framerate)
{
    m_enemies.reserve(200);
    m_fpsFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    m_scoreFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    m_hpFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    m_fpsStartTime = m_fpsClock.getElapsedTime().asMilliseconds();
    m_fpsText.setFont(m_fpsFont);
    m_fpsText.setPosition(10, 10);
    m_fpsText.setCharacterSize(18);
    m_fpsText.setFillColor(sf::Color::Black);

    setMapTexture(window);
    setPlayer();
    setEnemiesCount(40);
}

Game::~Game()
{
    for (Player* player : m_players)
    {
        delete player;
    }
    for (Enemy* enemy : m_enemies)
	{
		delete enemy;
	}

    //for (PlayerProjectile* projectile : m_projectiles)
//{
//    delete projectile;
//}

}

void Game::setMapTexture(sf::RenderWindow* window)
{
    m_map.loadFromFile("resource\\beach.png");
    m_mapSprite.setTexture(m_map);
}

void Game::setPlayer()
{
    // Clear existing players if any
    for (Player* player : m_players)
    {
        delete player;
    }
    m_players.clear();

    // Create new players
    for (size_t i = 0; i < m_maxPlayers; ++i)
    {
        Player* player = new Player();
        player->movementSprite().setPosition(
            m_renderWindow->getSize().x / 2.f,
            m_renderWindow->getSize().y / 2.f
        );
        m_players.push_back(player);
    }
}

void Game::removeProjectiles()
{
    m_projectiles.erase(std::remove_if(m_projectiles.begin(), m_projectiles.end(), [this](const std::unique_ptr<PlayerProjectile>& p)
        {
            sf::FloatRect bounds = p->getShape().getGlobalBounds();
            return bounds.left + bounds.width < 0 || bounds.top + bounds.height < 0 ||
                bounds.left > m_renderWindow->getSize().x || bounds.top > m_renderWindow->getSize().y;
        }), m_projectiles.end());
}

void Game::setEnemiesCount(int count)
{
    m_enemiesCount = count;
    while (m_enemies.size() < m_enemiesCount)
    {
        spawnEnemy(m_renderWindow);
    }
}

void Game::spawnEnemy(sf::RenderWindow* window)
{
    for (Player* player : m_players)
    {
        if (m_score >= 5000 && std::none_of(m_enemies.begin(), m_enemies.end(), [](Enemy* e) { return dynamic_cast<CrabBoss*>(e); })) // EASTER EGG (INVICIBLE BOSS)
        {
            for (Enemy* enemy : m_enemies)
            {
                delete enemy;
            }
            m_enemies.clear();

            m_enemies.push_back(new CrabBoss(window, player));
        }
        else if (rand() % 2 == 0) {
            m_enemies.push_back(new SharkEnemy(window, player));
        }
        else {
            m_enemies.push_back(new CrabEnemy(window, player));
        }
    }
}

void Game::removeDeadEnemies()
{
    auto it = std::remove_if(m_enemies.begin(), m_enemies.end(), [this](Enemy* enemy)
    {
            bool isCrabBoss = false;
            if (!enemy->isAlive())
            {
                if (CrabBoss* crabBoss = dynamic_cast<CrabBoss*>(enemy))
                {
                    isCrabBoss = true;
                    m_winText.setString("YOU WIN");
                    m_winText.setCharacterSize(72);
                    m_winText.setFillColor(sf::Color::Green);
                    m_winText.setPosition(
                        (m_renderWindow->getSize().x - m_winText.getLocalBounds().width) / 2,
                        (m_renderWindow->getSize().y - m_winText.getLocalBounds().height) / 2
                    );
                }

                m_score += 10;

                if (isCrabBoss)
                    m_score += 90;

                delete enemy;
                return true;
            }
            return false;
    });

    m_enemies.erase(it, m_enemies.end());
}

void Game::setAudio()
{
    m_gameMusic.openFromFile("resource\\game.mp3");
    m_gameMusic.setVolume(10);
    m_gameMusic.play();
    m_gameMusic.setLoop(true);
}

void Game::processInput(const sf::Event& event)
{
}

void Game::render()
{
    m_renderWindow->draw(m_mapSprite);

    for (Player* player : m_players)
    {
        if (player->m_isIdle)
            m_renderWindow->draw(player->idleSprite());
        else
            m_renderWindow->draw(player->movementSprite());
    }

    for (Enemy* enemy : m_enemies)
    {
        m_renderWindow->draw(enemy->getSprite());
    }

    for (const auto& projectile : m_projectiles)
    {
        m_renderWindow->draw(projectile->getShape());
    }

    for (const auto& projectile : m_enemyProjectiles)
    {
        m_renderWindow->draw(projectile->getSprite());
    }

    displayFPS();
    displayScore();
    displayHP();

    if (m_isGameOver)
    {
        displayGameOver();
    }
}

void Game::displayFPS()
{
    m_renderWindow->draw(m_fpsText);
}

void Game::displayScore()
{
    sf::RectangleShape rec(sf::Vector2f(250.f, 50.f));
	rec.setPosition((m_renderWindow->getSize().x / 2) - 120, 0);
    rec.setFillColor(sf::Color(0, 0, 0, 128));
    m_scoreText.setFont(m_scoreFont);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition((m_renderWindow->getSize().x / 2) - 80, 0);
    m_scoreText.setString("S C O R E : " + std::to_string(m_score));

    m_renderWindow->draw(rec);
    m_renderWindow->draw(m_scoreText);
}

void Game::displayHP()
{
    for (Player* player : m_players)
    {
        m_HP.setFont(m_hpFont);
        m_HP.setCharacterSize(18);
        m_HP.setFillColor(sf::Color::Black);
        m_HP.setPosition(10, 40);
        m_HP.setString("H P : " + std::to_string(player->getHp()));

        m_renderWindow->draw(m_HP);
    }
}

void Game::displayGameOver()
{
    sf::RectangleShape overlay(sf::Vector2f(m_renderWindow->getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));

    m_gameOverText.setFont(m_scoreFont);
    m_gameOverText.setString("GAME OVER");
    m_gameOverText.setCharacterSize(72);
    m_gameOverText.setFillColor(sf::Color::Red);

    sf::FloatRect textBounds = m_gameOverText.getLocalBounds();
    m_gameOverText.setPosition(
        (m_renderWindow->getSize().x - textBounds.width) / 2,
        (m_renderWindow->getSize().y - textBounds.height) / 2
    );

    m_renderWindow->draw(overlay);
    m_renderWindow->draw(m_gameOverText);
}

void Game::update(const float& deltaTime)
{
    float currentTime = m_fpsClock.getElapsedTime().asMilliseconds();
    if (currentTime - m_fpsStartTime > 1000)
    {
        m_fpsText.setString("FPS: " + std::to_string(m_fpsCounter));
        m_fpsStartTime = currentTime;
        m_fpsCounter = 0;
    }
    m_fpsCounter++;

    if (m_isGameOver)
        return;

    for (Player* player : m_players)
    {
        if (!player->isAlive())
        {
            m_isGameOver = true;
            return;
        }

        player->movement();
        player->updateAnim();
        player->updateInvulnerabilityEffect();
        player->shoot(m_projectiles, m_renderWindow);

        auto projectileIterator = m_projectiles.begin();
        while (projectileIterator != m_projectiles.end())
        {
            (*projectileIterator)->update();
            bool projectileHit = false;

            for (Enemy* enemy : m_enemies)
            {
                if ((*projectileIterator)->getShape().getGlobalBounds().intersects(enemy->getHitbox()))
                {
                    enemy->takeDamage(25);
                    projectileHit = true;
                    break;
                }
            }

            if (projectileHit)
                projectileIterator = m_projectiles.erase(projectileIterator);
            else
                ++projectileIterator;
        }

        auto enemyProjectileIterator = m_enemyProjectiles.begin();
        while (enemyProjectileIterator != m_enemyProjectiles.end()) 
        {
            (*enemyProjectileIterator)->update();
            bool shouldDestroy = (*enemyProjectileIterator)->updateProjectiles();

            if (shouldDestroy ||
                (!player->isInvulnerable() &&
                    (*enemyProjectileIterator)->getHitbox().intersects(player->getHitbox())))
            {
                enemyProjectileIterator = m_enemyProjectiles.erase(enemyProjectileIterator);
                if (!shouldDestroy) {
                    player->takeDamage(5);
                    player->setInvulnerable(2.f);
                }
            }
            else {
                ++enemyProjectileIterator;
            }
        }

        removeProjectiles();

        for (Enemy* enemy : m_enemies)
        {
            enemy->updateAnim();
            enemy->movement();

            if (SharkEnemy* shark = dynamic_cast<SharkEnemy*>(enemy))
            {
                shark->shoot(m_enemyProjectiles);
            }

            if (player->getHitbox().intersects(enemy->getHitbox()) && !player->isInvulnerable())
            {
                player->takeDamage(10);
                player->setInvulnerable(2.f);
            }
        }

        removeDeadEnemies();

        while (m_enemies.size() < m_enemiesCount)
        {
            spawnEnemy(m_renderWindow);
        }
    }
}