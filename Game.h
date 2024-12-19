#pragma once

#include "SceneBase.h"
#include "Weapon.h"
#include <vector>
#include <memory>

class Player;
class Enemy;

class Game : public SceneBase
{
public:
    Game(sf::RenderWindow* window, const float& framerate);
    ~Game();

    // PLAYER
    void setPlayer();
    void removeProjectiles();

    // ENEMIES
    void setEnemiesCount(int count);
    void spawnEnemy(sf::RenderWindow* window);
    void removeDeadEnemies();

    // GAME MAP
    void setMapTexture(sf::RenderWindow* window);
    void setAudio();
    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void render() override;
    void setScore(const float& deltaTime);

private:
    sf::Music m_gameMusic;
    sf::Texture m_map;
    sf::Sprite m_mapSprite;

    Player* m_player;
    std::vector<Enemy*> m_enemies;
    std::vector<std::unique_ptr<PlayerProjectile>> m_projectiles; 
    int m_enemiesCount;
    int m_score;
};

