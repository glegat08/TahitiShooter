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
    return m_isInvulnerable && m_invulnerableClock.getElapsedTime().asSeconds() < 0.5f;
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
    m_idleSprite.setPosition(getPlayerPosition());
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
    sf::Vector2f currentPos = getPlayerPosition();
    m_isIdle = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        float leftX = currentPos.x - 4.f;
        if (leftX >= 50.f) // SIZE OF MAP.X (LEFT)
        {
            m_playerSprite.move(-4.f, 0.f);
            m_currentDirection = LEFT;
            m_isIdle = false;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        float rightX = currentPos.x + 4.f;
        if (rightX <= 1645.f) // SIZE OF MAP.X (RIGHT)
        {
            m_playerSprite.move(4.f, 0.f);
            m_currentDirection = RIGHT;
            m_isIdle = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        float upY = currentPos.y - 4.f;
        if (upY >= 80.f) // SIZE OF MAP.Y (UP)
        {
            m_playerSprite.move(0.f, -4.f);
            m_currentDirection = TOP;
            m_isIdle = false;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        float downY = currentPos.y + 4.f;
        if (downY <= 830.f) // SIZE OF MAP.Y (DOWN)
        {
            m_playerSprite.move(0.f, 4.f);
            m_currentDirection = BOTTOM;
            m_isIdle = false;
        }
    }

    m_idleSprite.setPosition(getPlayerPosition());
}

int Player::getShield()
{
    return 0;
}

int Player::getHp()
{
    return 0;
}

void Player::takeDamage(int damage)
{
}

void Player::getWeapon()
{
}

void Player::switchWeapon()
{
}

void Player::setInvulnerable(float duration)
{
    m_isInvulnerable = true;
    m_invulnerableClock.restart();
}

void Player::pushPlayer(const sf::Vector2f& enemyPos)
{
    sf::Vector2f direction = m_playerSprite.getPosition() - enemyPos;
    direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);

    m_playerSprite.move(-direction.x * -50.f, -direction.y * -50.f);
}

sf::Vector2f Player::getPlayerPosition()
{
	return m_playerSprite.getPosition();
}

const sf::Sprite& Player::getPlayerSprite() const
{
    return m_playerSprite;
}

sf::FloatRect Player::getHitbox() const
{
    sf::FloatRect spriteBounds = m_playerSprite.getGlobalBounds();

    // FREE TO MODIFY THE HITBOX
    float offsetX = spriteBounds.width * 0.4f;
    float offsetY = spriteBounds.height * 0.35f;
    float reducedWidth = spriteBounds.width - 2 * offsetX;
    float reducedHeight = spriteBounds.height - 2 * offsetY;

    return sf::FloatRect
    (
        spriteBounds.left + offsetX,
        spriteBounds.top + offsetY,
        reducedWidth,
        reducedHeight
    );
}
