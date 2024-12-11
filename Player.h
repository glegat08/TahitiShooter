#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player() { GameObject* m_texture; GameObject* m_sprite; }

	bool isAlive = true;
	bool isShooting = false;

	void movement() override;
	void getShield() override;
	void getHp() override;
	void getHit() override;
	void getWeapon() override;
	void switchWeapon() override;

private:
	GameObject* m_texture;
	GameObject* m_sprite;

	int m_health;
	int m_shield;
};