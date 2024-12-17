#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
public:
	// Constructor & Destructor
	GameObject() {}
	virtual ~GameObject() = default;

	// Virtual Bool method
	virtual bool isAlive() = 0;
	virtual bool isShooting() = 0;
	virtual bool isAttacking() = 0;
	virtual bool isInvulnerable() = 0;

	// Virtual Void method
	virtual void setTexture() = 0;
	virtual void updateAnim() = 0;
	virtual void movement() = 0;
	virtual void getShield() = 0;
	virtual void getHp() = 0;
	virtual void getHit() = 0;
	virtual void getWeapon() = 0;
	virtual void switchWeapon() = 0;
	virtual void setInvulnerable(float duration) = 0;
};