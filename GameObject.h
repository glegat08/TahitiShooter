#pragma once

#include "Game.h"

class GameObject
{
public:
	// Constructor & Destructor
	GameObject(){}
	virtual ~GameObject() = default;
	
	// Virtual Bool method
	virtual bool isAlive() = 0;
	virtual bool isShooting() = 0;
	
	// Virtual Void method
	virtual void movement() = 0;
	virtual void getShield() = 0;
	virtual void getHp() = 0;
	virtual void getWeapon() = 0;
	virtual void switchWeapon() = 0;
	virtual void getHit() = 0;

private:
	// Texture/Sprite for game objects
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};