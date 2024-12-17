#pragma once

#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
	Enemy(sf::RenderWindow* window, Player* player);

	// BOOL METHOD
	bool isAlive() override;
	bool isShooting() override;
	bool isAttacking() override;
	bool isInvulnerable() override;
	bool checkCollision();

	// VOID METHOD
	void setTexture() override;
	void updateAnim() override;
	void movement() override;
	void moveTowardsPlayer(const sf::Vector2f& playerPos);
	void getShield() override;
	void getHp() override;
	void getHit() override;
	void getWeapon() override;
	void switchWeapon() override;
	void setInvulnerable(float duration) override;
	void randomPos(sf::RenderWindow* window);
	void resetPosition();

	// OTHER METHOD
	sf::FloatRect getHitbox() const;

	// PUBLIC PARAMETERS
	sf::Texture m_texture;
	sf::Sprite m_enemySprite;

private:
	// ANIMATION
	sf::Clock m_animationClock;
	const int m_frameWidth = 52;
	const int m_frameHeight = 80;
	const int m_numFrames = 5;
	const int m_numDirections = 0;
	int m_currentFrame = 0;
	int m_currentDirection = 0;

	// ENEMY POS
	sf::RenderWindow* m_renderWindow;
	Player* m_player;

	int m_health;
	int m_shield;
};

class CrabEnemy : public GameObject
{

};