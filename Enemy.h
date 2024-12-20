#pragma once

#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject 
{
public:
    Enemy();
    Enemy(sf::RenderWindow* window, Player* player);
    virtual ~Enemy() = default;

    // Pure virtual methods
    virtual sf::Sprite& getSprite() = 0;
    virtual sf::FloatRect getHitbox() const = 0;

    virtual bool isAlive() override;
    virtual bool isShooting() override;
    virtual bool isAttacking() override;
    virtual bool isInvulnerable() override;

    virtual void setTexture() override;
    virtual void updateAnim() override;
    virtual void movement() override;
    virtual void randomPos(sf::RenderWindow* window);

protected:
    sf::RenderWindow* m_renderWindow;
    Player* m_player;

    int m_health = 100;
    int m_shield = 0;
};


// Subclass SharkEnemy
class SharkEnemy : public Enemy 
{
public:
    SharkEnemy(sf::RenderWindow* window, Player* player);

    void setTexture() override;
    void movement() override;
    bool isShooting() override;
    int getHp() override;
    int getShield() override;
    void takeDamage(int damage) override;
    void setInvulnerable(float duration) override;
    void getWeapon() override;
    void switchWeapon() override;
    void updateAnim() override;
    void resetAnimation();
    void shoot(std::vector<std::unique_ptr<EnemyProjectile>>& enemyProjectiles);

    sf::Sprite& getSprite() override;
    sf::FloatRect getHitbox() const;
    sf::Vector2f getSharkCenter();

private:
    void moveAlongBorder();
    sf::Clock m_animationClock;
    int m_currentFrame = 0;
    int m_frameWidth = 52;
    int m_frameHeight = 80;
    int m_numFrames = 5;

    float m_directionX;
    float m_directionY;
    float m_moveSpeed = 2.f;

    sf::Texture m_sharkTexture;
	sf::Sprite m_sharkSprite;

    sf::Clock movementSwitchClock;
    bool switchMove = false;
    int move = 1;

    sf::Clock m_shootClock;
};

// Subclass CrabEnemy
class CrabEnemy : public Enemy 
{
public:
    CrabEnemy(sf::RenderWindow* window, Player* player);

    void setTexture() override;
    void movement() override;
    bool isAttacking() override;
    int getHp() override;
    int getShield() override;
    void takeDamage(int damage) override;
    void setInvulnerable(float duration) override;
    void getWeapon() override;
    void switchWeapon() override;
    void updateAnim() override;
    void resetAnimation();

    sf::Sprite& getSprite() override;
    sf::FloatRect getHitbox() const;

private:
	sf::Texture m_crabTexture;
    sf::Texture m_crabAttack;
    sf::Sprite m_crabAttackSprite;
	sf::Sprite m_crabSprite;
    sf::Clock m_animationClock;
    int m_currentFrame = 0;
    int m_frameWidth = 55;
    int m_frameHeight = 50;
    int m_numFrames = 4;

    void moveTowardsPlayer(const sf::Vector2f& playerPos, float speed);
};

// CRAB BOSS
class CrabBoss : public Enemy
{
public:
    CrabBoss(sf::RenderWindow* window, Player* player);

    void setTexture() override;
    void movement() override;
    bool isAttacking() override;
    int getHp() override;
    int getShield() override;
    void takeDamage(int damage) override;
    void setInvulnerable(float duration) override;
    void getWeapon() override;
    void switchWeapon() override;
    void updateAnim() override;

    sf::Sprite& getSprite() override;
    sf::FloatRect getHitbox() const;

private:
    int m_Bosshealth;
    sf::Texture m_cBossTexture;
    sf::Sprite m_cBossSprite;

    void moveLikeACrab(const sf::Vector2u& windowSize);
};