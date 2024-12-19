#include "Weapon.h"
#include <cmath>

Projectile::Projectile(const sf::Vector2f& startPos, const sf::Vector2f& targetPos, bool isSpecial)
{
    setTexture();
    m_spearSprite.setPosition(startPos);

    sf::Vector2f direction = targetPos - startPos;
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0)
    {
        m_velocity = direction / magnitude * m_speed;
    }
    else
    {
        m_velocity = { 0.f, 0.f };
    }
}

void Projectile::update(float deltaTime)
{
    m_spearSprite.move(m_velocity * deltaTime);
}

void Projectile::setTexture()
{
    m_spearTexture.loadFromFile("C:\\Users\\guill\\Downloads\\spear.png");
    m_spearSprite.setTexture(m_spearTexture);
}

void Projectile::render(sf::RenderWindow& window) const
{
    window.draw(m_spearSprite);
}

sf::FloatRect Projectile::getBounds() const
{
    return m_spearSprite.getGlobalBounds();
}

bool Projectile::hasHitEnemy() const
{
    return false;
}

bool Projectile::isAlive()
{
    return false;
}

bool Projectile::isShooting()
{
    return false;
}

bool Projectile::isAttacking()
{
    return false;
}

bool Projectile::isInvulnerable()
{
    return false;
}

void Projectile::updateAnim()
{
}

void Projectile::movement()
{
}

int Projectile::getShield()
{
    return 0;
}

int Projectile::getHp()
{
    return 0;
}

void Projectile::takeDamage(int damage)
{
}

void Projectile::getWeapon()
{
}

void Projectile::switchWeapon()
{
}

void Projectile::setInvulnerable(float duration)
{
}
