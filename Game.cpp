#include "Game.h"
#include "Player.h"
#include "Enemy.h"

Game::Game(sf::RenderWindow* window, const float& framerate)
    : SceneBase(window, framerate)
{

    m_fpsFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    m_scoreFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    setMapTexture(window);
    setPlayer();
    setEnemiesCount(5);
}

Game::~Game()
{
    delete m_player;
    for (Enemy* enemy : m_enemies)
    {
        delete enemy;
    }
}

void Game::setMapTexture(sf::RenderWindow* window)
{
    m_map.loadFromFile("resource\\beach.png");
    m_mapSprite.setTexture(m_map);
}

void Game::setPlayer()
{
    m_player = new Player();
    m_player->m_playerSprite.setPosition(m_renderWindow->getSize().x / 2.f, m_renderWindow->getSize().y / 2.f);
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
    if (rand() % 2 == 0) {
        m_enemies.push_back(new SharkEnemy(window, m_player));
    }
    else {
        m_enemies.push_back(new SharkEnemy(window, m_player));
    }
}

void Game::removeDeadEnemies()
{
    auto it = std::remove_if(m_enemies.begin(), m_enemies.end(), [this](Enemy* enemy)
        {
            if (!enemy->isAlive())
            {
                m_score += 10;
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
}

void Game::processInput(const sf::Event& event)
{
}

void Game::displayFPS()
{
    static sf::Clock fpsClock;
    static int frameCount = 0;
    static float elapsedTime = 0.f;
    m_fpsText.setFont(m_fpsFont);
    m_fpsText.setPosition(10, 10);
    m_fpsText.setCharacterSize(18);
    m_fpsText.setFillColor(sf::Color::Black);

    frameCount++;
    elapsedTime += fpsClock.restart().asSeconds();

    if (elapsedTime >= 0.1f)
    {
        float fps = frameCount / elapsedTime;
        m_fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
        frameCount = 0;
        elapsedTime = 0.f;
    }

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

void Game::update(const float& deltaTime)
{
    m_player->movement();
    m_player->updateAnim();
    m_player->updateInvulnerabilityEffect();

    // Player shooting
    m_player->shoot(m_projectiles, m_renderWindow);

    // Update projectiles
    for (auto& projectile : m_projectiles)
    {
        projectile->update();
    }

    for (auto& projectile : m_enemyProjectiles)
    {
        projectile->update();
    }

    for (Enemy* enemy : m_enemies)
    {
        enemy->updateAnim();
        enemy->movement();

        // Enemy shooting logic
        if (SharkEnemy* shark = dynamic_cast<SharkEnemy*>(enemy))
        {
            // Call shoot for each SharkEnemy
            shark->shoot(m_enemyProjectiles);
        }

        if (m_player->getHitbox().intersects(enemy->getHitbox()) && !m_player->isInvulnerable())
        {
            m_player->takeDamage(10);
            m_player->setInvulnerable(2.f);
        }
    }

    removeDeadEnemies();

    while (m_enemies.size() < m_enemiesCount)
    {
        spawnEnemy(m_renderWindow);
    }
}

void Game::render()
{
    m_renderWindow->draw(m_mapSprite);

    if (m_player->m_isIdle)
        m_renderWindow->draw(m_player->m_idleSprite);
    else
        m_renderWindow->draw(m_player->m_playerSprite);

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
        m_renderWindow->draw(projectile->getShape());
    }

    displayFPS();
    displayScore();
}
