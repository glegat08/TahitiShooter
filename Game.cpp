#include "Game.h"
#include "Player.h"
#include "Enemy.h"

Game::Game(sf::RenderWindow* window, const float& framerate)
    : SceneBase(window, framerate)
{
    setMapTexture(window);
    setPlayer();
    setEnemiesCount(10);
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
    Enemy* enemy = new Enemy(window);
    m_enemies.push_back(enemy);
}

void Game::removeDeadEnemies()
{
    m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [](Enemy* enemy) 
        {
        return !enemy->isAlive();
        }), m_enemies.end());
}

sf::Vector2f Game::getPlayerPosition() const
{
    return m_player->m_playerSprite.getPosition();
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
    }
}

void Game::update(const float& deltaTime)
{
    m_player->movement();
    m_player->updateAnim();

    for (Enemy* enemy : m_enemies)
    {
        enemy->updateAnim();
        enemy->moveTowardsPlayer(getPlayerPosition());
    }

    removeDeadEnemies();

    while (m_enemies.size() < m_enemiesCount)
    {
        spawnEnemy(m_renderWindow);
    }
}