#pragma once

#include "SceneBase.h"
class Player;
class Enemy;

class Game : public SceneBase
{
public:
    Game(sf::RenderWindow* window, const float& framerate);


    // PLAYER
    void setPlayer();

    // ENEMIES
    void setEnemiesCount(int count);
    void spawnEnemy(sf::RenderWindow* window);
    void removeDeadEnemies();
    sf::Vector2f getPlayerPosition() const;

    // GAME MAP
    void setMapTexture(sf::RenderWindow* window);
    void setAudio();
    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void render() override;

private:
    sf::Music m_gameMusic;
    sf::Texture m_map;
    sf::Sprite m_mapSprite;

    Player* m_player;
    std::vector<Enemy*> m_enemies;
    int m_enemiesCount;
};