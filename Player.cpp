#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"

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
    return m_health > 0;
}

bool Player::isShooting()
{
    bool shooting = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    return shooting;
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
	m_texture.loadFromFile("resource\\Unarmed_Run_full.png");
    m_playerSprite.setTexture(m_texture);
    m_playerSprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    m_playerSprite.setScale(2.f, 2.f);

    // IDLE
    m_idleTexture.loadFromFile("resource\\Unarmed_Idle_full.png");
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
    float deltaTime = m_movementClock.restart().asSeconds();
    sf::Vector2f currentPos = getPlayerPosition();
    m_isIdle = true;

    float frameSpeed = m_speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        float leftX = currentPos.x - frameSpeed;
        if (leftX >= 50.f) // SIZE OF MAP.X (LEFT)
        {
            m_playerSprite.move(-frameSpeed, 0.f);
            m_currentDirection = LEFT;
            m_isIdle = false;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        float rightX = currentPos.x + frameSpeed;
        if (rightX <= 1645.f) // SIZE OF MAP.X (RIGHT)
        {
            m_playerSprite.move(frameSpeed, 0.f);
            m_currentDirection = RIGHT;
            m_isIdle = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        float upY = currentPos.y - frameSpeed;
        if (upY >= 80.f) // SIZE OF MAP.Y (UP)
        {
            m_playerSprite.move(0.f, -frameSpeed);
            m_currentDirection = TOP;
            m_isIdle = false;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        float downY = currentPos.y + frameSpeed;
        if (downY <= 830.f) // SIZE OF MAP.Y (DOWN)
        {
            m_playerSprite.move(0.f, frameSpeed);
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
    return m_health;
}

void Player::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health <= 0)
    {
        m_health = 0;
    }
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
    m_invulnerableDuration = duration;
    m_invulnerableClock.restart();
    m_blinkClock.restart();
}

void Player::updateInvulnerabilityEffect()
{
    if (m_isInvulnerable)
    {
        if (m_invulnerableClock.getElapsedTime().asSeconds() > m_invulnerableDuration)
        {
            m_isInvulnerable = false;
            m_idleSprite.setColor(sf::Color::White);
            m_playerSprite.setColor(sf::Color::White);
        }
        else
        {
            if (m_blinkClock.getElapsedTime().asSeconds() > 0.1f)
            {
                sf::Color currentColor = m_idleSprite.getColor();
                if (currentColor.a == 255)
                {
                    m_idleSprite.setColor(sf::Color(255, 255, 255, 128));
                    m_playerSprite.setColor(sf::Color(255, 255, 255, 128));
                }
                else
                {
                    m_idleSprite.setColor(sf::Color(255, 255, 255, 255));
                    m_playerSprite.setColor(sf::Color(255, 255, 255, 255));
                }
                m_blinkClock.restart();
            }
        }
    }
}

void Player::shoot(std::vector<std::unique_ptr<PlayerProjectile>>& projectiles, sf::RenderWindow* window)
{
    static sf::Clock shootClock;
    if (isShooting() && shootClock.getElapsedTime().asSeconds() > 0.2f)
    {
        sf::Vector2f mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        sf::Vector2f playerPosition = getPlayerCenter();

        projectiles.push_back(std::make_unique<PlayerProjectile>(window, playerPosition, mousePosition));
        shootClock.restart();
    }
}

void Player::attacking()
{
	m_isAttacking = true;
	m_attackSprite.setPosition(getPlayerPosition());
}

sf::Vector2f Player::getPlayerPosition()
{
	return m_playerSprite.getPosition();
}

sf::Vector2f Player::getPlayerCenter()
{
    sf::FloatRect bounds = m_playerSprite.getGlobalBounds();
    return { bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f };
}

const sf::Sprite& Player::getPlayerSprite() const
{
    return m_idleSprite;
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