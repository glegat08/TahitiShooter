#include "Enemy.h"
#include <cmath>

// Base Enemy Class
Enemy::Enemy(sf::RenderWindow* window, Player* player)
    : m_renderWindow(window), m_player(player) 
{
    randomPos(window);
}

bool Enemy::isAlive() 
{
    return m_health > 0;
}

bool Enemy::isShooting() 
{
    return false;
}

bool Enemy::isAttacking() 
{
    return false;
}

bool Enemy::isInvulnerable() 
{
    return false;
}

void Enemy::setTexture() 
{
}

void Enemy::updateAnim() 
{
}

void Enemy::movement() 
{
}

void Enemy::randomPos(sf::RenderWindow* window) 
{
    sf::Vector2u windowSize = window->getSize();
    float x = static_cast<float>(rand() % windowSize.x);
    float y = static_cast<float>(rand() % windowSize.y);

    // Positionne l'ennemi
    if (auto* shark = dynamic_cast<SharkEnemy*>(this))
        shark->getSprite().setPosition(x, y);
    else if (auto* crab = dynamic_cast<CrabEnemy*>(this))
        crab->getSprite().setPosition(x, y);
}

// SharkEnemy Class
SharkEnemy::SharkEnemy(sf::RenderWindow* window, Player* player)
    : Enemy(window, player) 
{
    setTexture();
    randomPos(window);
}

void SharkEnemy::setTexture()
{
    m_sharkTexture.loadFromFile("C:\\Users\\guill\\Downloads\\shark.png");
    m_sharkSprite.setTexture(m_sharkTexture);
}

void SharkEnemy::movement() 
{
    moveAlongBorder();
}

void SharkEnemy::moveAlongBorder() 
{
    sf::Vector2f pos = m_sharkSprite.getPosition();
    sf::Vector2u windowSize = m_renderWindow->getSize();

    if (pos.x <= 0 || pos.x >= windowSize.x - m_frameWidth) 
    {
        m_sharkSprite.move(0.f, 2.f);
    }
    else if (pos.y <= 0 || pos.y >= windowSize.y - m_frameHeight) 
    {
        m_sharkSprite.move(2.f, 0.f);
    }
    else 
    {
        m_sharkSprite.move(-2.f, 0.f);
    }
}

bool SharkEnemy::isShooting() 
{
    return true;
}

int SharkEnemy::getHp()
{
    return 0;
}

int SharkEnemy::getShield()
{
    return 0;
}

void SharkEnemy::takeDamage(int damage)
{
}

void SharkEnemy::setInvulnerable(float duration)
{
}

void SharkEnemy::getWeapon()
{
}

void SharkEnemy::switchWeapon()
{
}

void SharkEnemy::updateAnim()
{
    if (m_animationClock.getElapsedTime().asSeconds() > 0.2f)
    {
        m_currentFrame = (m_currentFrame + 1) % m_numFrames;
        int textureX = m_currentFrame * m_frameWidth;

        m_sharkSprite.setTextureRect(sf::IntRect(textureX, 0, m_frameWidth, m_frameHeight));

        m_animationClock.restart();
    }
}

sf::Sprite& SharkEnemy::getSprite()
{
    return m_sharkSprite;
}

sf::FloatRect SharkEnemy::getHitbox() const
{
    return m_sharkSprite.getGlobalBounds();
}


// CrabEnemy Class
CrabEnemy::CrabEnemy(sf::RenderWindow* window, Player* player)
    : Enemy(window, player) 
{
    setTexture();
    randomPos(window);
}

void CrabEnemy::setTexture() 
{
    m_crabTexture.loadFromFile("C:\\Users\\guill\\Downloads\\crabWalk.png");
    m_crabSprite.setTexture(m_crabTexture);
}

void CrabEnemy::movement() 
{
    moveTowardsPlayer(m_player->getPlayerPosition(), 1.f);
}

bool CrabEnemy::isAttacking() 
{
    return true;
}

int CrabEnemy::getHp()
{
    return 0;
}

int CrabEnemy::getShield()
{
    return 0;
}

void CrabEnemy::takeDamage(int damage)
{
}

void CrabEnemy::setInvulnerable(float duration)
{
}

void CrabEnemy::getWeapon()
{
}

void CrabEnemy::switchWeapon()
{
}

void CrabEnemy::updateAnim()
{
    if (m_animationClock.getElapsedTime().asSeconds() > 0.2f)
    {
        m_currentFrame = (m_currentFrame + 1) % m_numFrames;
        int textureX = m_currentFrame * m_frameWidth;

        m_crabSprite.setTextureRect(sf::IntRect(textureX, 0, m_frameWidth, m_frameHeight));

        m_animationClock.restart();
    }
}

sf::Sprite& CrabEnemy::getSprite()
{
    return m_crabSprite;
}

sf::FloatRect CrabEnemy::getHitbox() const
{
    return m_crabSprite.getGlobalBounds();
}

void CrabEnemy::moveTowardsPlayer(const sf::Vector2f& playerPos, float speed)
{
	float dx = playerPos.x - m_crabSprite.getPosition().x;
	float dy = playerPos.y - m_crabSprite.getPosition().y;

	float distance = std::sqrt(dx * dx + dy * dy);
	dx /= distance;
	dy /= distance;
	m_crabSprite.move(dx * speed, dy * speed);
}
