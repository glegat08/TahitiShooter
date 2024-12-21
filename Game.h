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
    void displayFPS();
    void displayScore();
    void displayHP();

private:
    sf::Music m_gameMusic;
    sf::Texture m_map;
    sf::Sprite m_mapSprite;

    // SCORE
    sf::Font m_scoreFont;
	sf::Text m_scoreText;
	int m_score = 0;

    // FPS COUNTER
    sf::Font m_fpsFont;
	sf::Text m_fpsText;
    SceneBase* m_currentScene;

    // PARAMETERS FOR FUNCTIONS
    Player* m_player;
    std::vector<Enemy*> m_enemies;
    std::vector<std::unique_ptr<PlayerProjectile>> m_projectiles;
    std::vector<std::unique_ptr<EnemyProjectile>> m_enemyProjectiles;
    int m_enemiesCount;

    // GAME OVER
    void displayGameOver();
    sf::Text m_gameOverText;
    sf::Text m_winText;
    bool m_isGameOver = false;

    // HP
    sf::Text m_HP;
    sf::Font m_hpFont;
};