#include "Player.h"

enum Direction
{
    BOTTOM
    , LEFT
    , RIGHT
    , TOP
};

Player::Player()
{
	setTexture();
}

bool Player::isAlive()
{
    return true;
}

bool Player::isShooting()
{
    return false;
}

bool Player::isAttacking()
{
    return false;
}

bool Player::isInvulnerable()
{
    return false;
}

void Player::setTexture()
{
    // MOVEMENT
	m_texture.loadFromFile("C:\\Users\\guill\\Downloads\\Unarmed_Run\\Unarmed_Run_full.png");
    m_playerSprite.setTexture(m_texture);
    m_playerSprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    m_playerSprite.setScale(2.f, 2.f);

    // IDLE
    m_idleTexture.loadFromFile("C:\\Users\\guill\\Downloads\\Unarmed_Idle\\Unarmed_Idle_full.png");
    m_idleSprite.setTexture(m_idleTexture);
    m_idleSprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    m_idleSprite.setScale(2.f, 2.f);

    // IDLE POS = MOVEMENT POS
    m_idleSprite.setPosition(m_playerSprite.getPosition());
}

void Player::updateAnim()
{
    // IDLE
    if (m_isIdle && m_movementAnimation.getElapsedTime().asSeconds() > 0.14f)
    {
        m_currentFrame = (m_currentFrame + 1) % 2;
        int left = m_currentFrame * m_frameWidth;
        int top = m_currentDirection * m_frameHeight;
        m_idleSprite.setTextureRect(sf::IntRect(left, top, m_frameWidth, m_frameHeight));
        m_movementAnimation.restart();
    }
    // MOVEMENT
    else if (m_animationClock.getElapsedTime().asSeconds() > 0.1f)
    {
        m_currentFrame = (m_currentFrame + 1) % m_numFrames;
        int left = m_currentFrame * m_frameWidth;
        int top = m_currentDirection * m_frameHeight;
        m_playerSprite.setTextureRect(sf::IntRect(left, top, m_frameWidth, m_frameHeight));
        m_animationClock.restart();
    }
}

void Player::movement()
{
    m_isIdle = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        m_playerSprite.move(0.f, -4.f);
        m_currentDirection = TOP;
        m_isIdle = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_playerSprite.move(0.f, 4.f);
        m_currentDirection = BOTTOM;
        m_isIdle = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        m_playerSprite.move(-4.f, 0.f);
        m_currentDirection = LEFT;
        m_isIdle = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_playerSprite.move(4.f, 0.f);
        m_currentDirection = RIGHT;
        m_isIdle = false;
    }

    m_idleSprite.setPosition(m_playerSprite.getPosition());
}

void Player::getShield()
{
}

void Player::getHp()
{
}

void Player::getHit()
{
}

void Player::getWeapon()
{
}

void Player::switchWeapon()
{
}

void Player::setInvulnerable()
{
}
