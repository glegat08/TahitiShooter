#include "Game.h"
#include "Player.h"
#include "Enemy.h"

Game::Game(sf::RenderWindow* window, const float& framerate)
	: SceneBase(window, framerate)
{
    setMapTexture(window);
    setPlayer();
    setEnemiesCount(3);
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
    if (rand() % 2 == 0) {
        m_enemies.push_back(new SharkEnemy(window, m_player));
    }
    else {
        m_enemies.push_back(new CrabEnemy(window, m_player));
    }
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
}

void Game::update(const float& deltaTime)
{
    m_player->movement();
    m_player->updateAnim();

    for (Enemy* enemy : m_enemies)
    {
        enemy->updateAnim();
        enemy->movement();

        if (m_player->getHitbox().intersects(enemy->getHitbox()) && !m_player->isInvulnerable())
        {
            m_player->pushPlayer(enemy->getSprite().getPosition());
            m_player->setInvulnerable(0.5f);
        }
    }

    removeDeadEnemies();

    while (m_enemies.size() < m_enemiesCount)
    {
        spawnEnemy(m_renderWindow);
    }
}