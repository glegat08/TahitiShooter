#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:
    Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, bool isSpecial = false);

    void update(float deltaTime);
    void render(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool hasHitEnemy() const;

    // USELESS METHOD
	bool isAlive() override;
	bool isShooting() override;
	bool isAttacking() override;
	bool isInvulnerable() override;

	void updateAnim() override;
	void movement() override;
	int getShield() override;
	int getHp() override;
	void takeDamage(int damage) override;
	void getWeapon() override;
	void switchWeapon() override;
	void setInvulnerable(float duration) override;

private:
    void setTexture();

    sf::Texture m_spearTexture;
	sf::Sprite m_spearSprite;
    sf::Vector2f m_velocity;
    float m_speed = 500.f; // Vitesse en pixels par seconde
    bool hitEnemy = false;
};