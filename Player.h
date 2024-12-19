#pragma once

#include "GameObject.h"
#include "Weapon.h"

class Enemy;
class Projectile;

class Player : public GameObject
{
public:
	Player();

	// BOOL METHOD
	bool isAlive() override;
	bool isShooting() override;
	bool isAttacking() override;
	bool isInvulnerable() override;

	// VOID METHOD
	void setTexture() override;
	void updateAnim() override;
	void movement() override;
	int getShield() override;
	int getHp() override;
	void takeDamage(int damage) override;
	void getWeapon() override;
	void switchWeapon() override;
	void setInvulnerable(float duration) override;
	void updateInvulnerabilityEffect();


	// OTHER METHOD
	sf::Vector2f getPlayerPosition();
	const sf::Sprite& getPlayerSprite() const;
	sf::FloatRect getHitbox() const;

	// PUBLIC PARAMETERS
	sf::Texture m_texture;
	sf::Texture m_idleTexture;
	sf::Texture m_attackTexture;

	sf::Sprite m_playerSprite;
	sf::Sprite m_idleSprite;
	sf::Sprite m_attackSprite;

	bool m_isIdle;

private:
	// ANIMATION
	sf::Clock m_movementClock;
	sf::Clock m_movementAnimation;
	sf::Clock m_animationClock;
	const int m_frameWidth = 64;
	const int m_frameHeight = 64;
	const int m_numFrames = 8;
	const int m_numDirections = 4;
	int m_currentFrame = 0;
	int m_currentDirection = 0;
	float m_speed = 200.f;

	// GAMEPLAY
	sf::Clock m_invulnerableClock;
	sf::Clock m_blinkClock;
	float m_invulnerableDuration;
	bool m_isInvulnerable = false;
	sf::FloatRect m_hitbox;
	std::vector<Projectile> m_projectiles;

	int m_health;
	int m_shield;
};