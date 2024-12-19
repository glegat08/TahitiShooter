#include "Weapon.h"
#include <cmath>
#define M_PI 3.141592653589793

Projectile::Projectile(sf::RenderWindow* window)
    : m_renderWindow(window)
{
    m_shape.setRadius(5.f);
    m_shape.setFillColor(sf::Color::White);
}

PlayerProjectile::PlayerProjectile(sf::RenderWindow* window, const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition)
    : Projectile(window)
{
    m_spearTexture.loadFromFile("resource\\spear.png");
    m_spearSprite.setTexture(m_spearTexture);

    sf::Vector2u textureSize = m_spearTexture.getSize();
    m_spearSprite.setOrigin(textureSize.x / 2.f, textureSize.y / 2.f);
    m_spearSprite.setPosition(startPosition);

    sf::Vector2f direction = targetPosition - startPosition;
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude != 0)
    {
        m_velocity = direction / magnitude * 5.f;

        float angle = atan2(direction.y, direction.x) * 180 / M_PI;
        angle += 45;

        m_spearSprite.setRotation(angle);
    }
    else
    {
        m_velocity = { 0.f, 0.f };
    }
}

sf::Sprite& PlayerProjectile::getShape()
{
    return m_spearSprite;
}

void PlayerProjectile::update()
{
    movement();
    m_renderWindow->draw(m_spearSprite);
}

void PlayerProjectile::movement()
{
    m_spearSprite.move(m_velocity);
}

// Enemy Projectile
EnemyProjectile::EnemyProjectile(sf::RenderWindow* window, const sf::Vector2f& targetPosition)
    : Projectile(window)
{
    m_shape.setFillColor(sf::Color::Red);

    sf::Vector2f direction = targetPosition - m_shape.getPosition();
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0)
        m_velocity = direction / magnitude * 3.f;
    else
        m_velocity = { 0.f, 0.f };
}

void EnemyProjectile::update()
{
    movement();
    m_renderWindow->draw(m_shape);
}

void EnemyProjectile::movement()
{
    m_shape.move(m_velocity);
}

// Boss Projectile
BossProjectile::BossProjectile(sf::RenderWindow* window)
    : Projectile(window)
{
    m_shape.setFillColor(sf::Color::Yellow);
    m_shape.setRadius(10.f);
}

void BossProjectile::update()
{
    movement();
    m_renderWindow->draw(m_shape);
}

void BossProjectile::movement()
{
    m_shape.move(-2.f, 4.f);
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

void Projectile::setTexture()
{
}

void Projectile::updateAnim()
{
}

int Projectile::getHp()
{
    return 0;
}

int Projectile::getShield()
{
    return 0;
}

void Projectile::takeDamage(int damage)
{
}

void Projectile::setInvulnerable(float duration)
{
}

void Projectile::getWeapon()
{
}

void Projectile::switchWeapon()
{
}