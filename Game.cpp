#include "Game.h"
#include "Player.h"
#include "Enemy.h"

Game::Game(sf::RenderWindow* window, const float& framerate)
	: SceneBase(window, framerate)
{
    setMapTexture(window);
    setPlayer();
    setEnemiesCount(1);
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
    m_map.loadFromFile("C:\\Users\\guill\\Downloads\\beach.png");
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
    Enemy* enemy = new Enemy(window, m_player);
    m_enemies.push_back(enemy);
}

void Game::removeDeadEnemies()
{
    m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [](Enemy* enemy) 
        {
        return !enemy->isAlive();
        }), m_enemies.end());
}

void Game::setAudio()
{
    m_gameMusic.openFromFile("C:\\Users\\guill\\Downloads\\AirFight.mp3");
    m_gameMusic.setVolume(10);
    m_gameMusic.play();
}

void Game::processInput(const sf::Event& event)
{
    //if (event.type == sf::Event::KeyPressed)
    //{
    //    // Exemple de mouvements du joueur
    //    if (event.key.code == sf::Keyboard::Left)
    //        m_player->m_sprite.move(-5.f, 0.f);
    //    else if (event.key.code == sf::Keyboard::Right)
    //        m_player->m_sprite.move(5.f, 0.f);
    //    else if (event.key.code == sf::Keyboard::Up)
    //        m_player->m_sprite.move(0.f, -5.f);
    //    else if (event.key.code == sf::Keyboard::Down)
    //        m_player->m_sprite.move(0.f, 5.f);
    //}
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
        m_renderWindow->draw(enemy->m_enemySprite);

        sf::FloatRect enemyHitbox = enemy->getHitbox();
        sf::RectangleShape enemyHitboxShape(sf::Vector2f(enemyHitbox.width, enemyHitbox.height));
        enemyHitboxShape.setPosition(enemyHitbox.left, enemyHitbox.top);
        enemyHitboxShape.setFillColor(sf::Color::Transparent);
        enemyHitboxShape.setOutlineColor(sf::Color::Red);
        enemyHitboxShape.setOutlineThickness(1.f);
        m_renderWindow->draw(enemyHitboxShape);
    }

    sf::FloatRect playerHitbox = m_player->getHitbox();
    sf::RectangleShape playerHitboxShape(sf::Vector2f(playerHitbox.width, playerHitbox.height));
    playerHitboxShape.setPosition(playerHitbox.left, playerHitbox.top);
    playerHitboxShape.setFillColor(sf::Color::Transparent);
    playerHitboxShape.setOutlineColor(sf::Color::Green);
    playerHitboxShape.setOutlineThickness(1.f);
    m_renderWindow->draw(playerHitboxShape);
}

void Game::update(const float& deltaTime)
{
    m_player->movement();
    m_player->updateAnim();

    for (Enemy* enemy : m_enemies)
    {
        //enemy->updateAnim();
        //enemy->moveTowardsPlayer(m_player->getPlayerPosition());

        if (m_player->getHitbox().intersects(enemy->getHitbox()) && !m_player->isInvulnerable())
        {
            m_player->pushPlayer(enemy->m_enemySprite.getPosition());
            m_player->setInvulnerable(0.5f); 
        }
    }

    removeDeadEnemies();

    while (m_enemies.size() < m_enemiesCount)
    {
        spawnEnemy(m_renderWindow);
    }
}