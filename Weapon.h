#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player;

// weapon.h

class Projectile : public GameObject
{
public:
    Projectile(sf::RenderWindow* window);
    virtual ~Projectile() = default;

    virtual void update() = 0;
    virtual void movement() = 0;

    bool isAlive() override;
    bool isShooting() override;
    bool isAttacking() override;
    bool isInvulnerable() override;
    void setTexture() override;
    void updateAnim() override;
    int getHp() override;
    int getShield() override;
    void takeDamage(int damage) override;
    void setInvulnerable(float duration) override;
    void getWeapon() override;
    void switchWeapon() override;

protected:
    sf::RenderWindow* m_renderWindow;
    sf::CircleShape m_shape;
};

class PlayerProjectile : public Projectile
{
public:
    PlayerProjectile(sf::RenderWindow* window, const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition);
    sf::Sprite& getShape();
    void update() override;
    void movement() override;

private:
    sf::Vector2f m_velocity;
    sf::Texture m_spearTexture;
    sf::Sprite m_spearSprite;
};

class EnemyProjectile : public Projectile
{
public:
    EnemyProjectile(sf::RenderWindow* window, const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition);

    sf::CircleShape& getShape();
    void update() override;
    void movement() override;

private:
    sf::Vector2f m_velocity;
    Player* player;
    sf::Vector2f m_position;
    sf::Vector2f direction;
    int projectileSpeed;
};

class BossProjectile : public Projectile
{
public:
    BossProjectile(sf::RenderWindow* window);

    void update() override;
    void movement() override;
};


class ContactWeapon : public GameObject
{
public:
    ContactWeapon(sf::RenderWindow* window, ContactWeapon* contactWeapon);
    virtual ~ContactWeapon() = default;

    sf::Sprite& getSprite();
    sf::CircleShape getHitbox() const;

    virtual void setTexture() override;
    virtual void updateAnim() override;
    virtual void movement() override;
    virtual void position(sf::RenderWindow* window);

protected:
    sf::Clock m_animationCaC;
    const int m_frameWidth = 64;
    const int m_frameHeight = 64;
    const int m_numFrames = 8;
    const int m_numDirections = 4;
    int m_currentFrame = 0;
    int m_currentDirection = 0;

    sf::RenderWindow* m_renderWindow;
    ContactWeapon* m_contactWeapon;
    sf::Texture m_CaC;
	sf::Sprite m_CaCSprite;
	sf::CircleShape m_hitbox;
	float m_moveSpeed = 1.f;
	float m_directionX;
	float m_directionY;

    Player* player;
};