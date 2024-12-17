#pragma once

#include "GameObject.h"

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
	void getShield() override;
	void getHp() override;
	void getHit() override;
	void getWeapon() override;
	void switchWeapon() override;
	void setInvulnerable() override;

	// PUBLIC PARAMETERS
	sf::Texture m_texture;
	sf::Sprite m_playerSprite;
	sf::Texture m_idleTexture;
	sf::Sprite m_idleSprite;
	bool m_isIdle;

private:
	// ANIMATION
	sf::Clock m_movementAnimation;
	sf::Clock m_animationClock;
	const int m_frameWidth = 64;
	const int m_frameHeight = 64;
	const int m_numFrames = 8;
	const int m_numDirections = 4;
	int m_currentFrame = 0;
	int m_currentDirection = 0;

	int m_health;
	int m_shield;
};