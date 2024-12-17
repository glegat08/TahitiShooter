#include "Enemy.h"
#include "SceneBase.h"

Enemy::Enemy(sf::RenderWindow* window)
{
    m_renderWindow = window;
	setTexture();
	randomPos(window);
}

bool Enemy::isAlive()
{
    //if (m_health <= 0)
    //{
    //    //resetPosition();
    //    m_health = 100;
    //    return false;
    //}
    return true;
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
	m_texture.loadFromFile("C:\\Users\\guill\\Downloads\\shark.png");
	m_enemySprite.setTexture(m_texture);
    m_enemySprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    m_enemySprite.setScale(1.5f, 1.5f);
}

void Enemy::updateAnim()
{
    if (m_animationClock.getElapsedTime().asSeconds() > 0.2f)
    {
		m_currentFrame = (m_currentFrame + 1) % m_numFrames;
		int left = m_currentFrame * m_frameWidth;
		int top = 0;
		m_enemySprite.setTextureRect(sf::IntRect(left, top, m_frameWidth, m_frameHeight));
		m_animationClock.restart();
	}
}

void Enemy::movement()
{
}

void Enemy::moveTowardsPlayer(const sf::Vector2f& playerPos)
{
    sf::Vector2f direction = playerPos - m_enemySprite.getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.1f)
        m_enemySprite.move((direction / distance) * 2.f);
}

void Enemy::getShield()
{
}

void Enemy::getHp()
{
}

void Enemy::getHit()
{
}

void Enemy::getWeapon()
{
}

void Enemy::switchWeapon()
{
}

void Enemy::setInvulnerable()
{
}

void Enemy::randomPos(sf::RenderWindow* window)
{
	float x = rand() % window->getSize().x;
	float y = rand() % window->getSize().y;
	m_enemySprite.setPosition(x, y);
}

//void Enemy::resetPosition()
//{
//    int x, y;
//    int windowWidth = m_renderWindow->getSize().x;
//    int windowHeight = m_renderWindow->getSize().y;
//
//    int side = rand() % 4;
//    switch (side)
//    {
//    case 0: // Gauche
//        x = 0;
//        y = rand() % windowHeight;
//        break;
//    case 1: // Droite
//        x = windowWidth;
//        y = rand() % windowHeight;
//        break;
//    case 2: // Haut
//        x = rand() % windowWidth;
//        y = 0;
//        break;
//    case 3: // Bas
//        x = rand() % windowWidth;
//        y = windowHeight;
//        break;
//    }
//
//    m_sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
//}