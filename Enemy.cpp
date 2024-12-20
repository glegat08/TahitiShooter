#include "Enemy.h"
#include <cmath>

enum Corner
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};

Enemy::Enemy()
{
}

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
    float x, y;

    if (auto* shark = dynamic_cast<SharkEnemy*>(this))
    {
        const float margin = 50.f;
        int corner = rand() % 4;

        switch (corner)
        {
        case TOP_LEFT:
            x = margin;
            y = margin;
            break;
        case TOP_RIGHT:
            x = windowSize.x - margin - shark->getSprite().getGlobalBounds().width;
            y = margin;
            break;
        case BOTTOM_LEFT:
            x = margin;
            y = windowSize.y - margin - shark->getSprite().getGlobalBounds().height;
            break;
        case BOTTOM_RIGHT:
            x = windowSize.x - margin - shark->getSprite().getGlobalBounds().width;
            y = windowSize.y - margin - shark->getSprite().getGlobalBounds().height;
            break;
        }

        shark->getSprite().setPosition(x, y);
        shark->resetAnimation();
    }
    else if (auto* crab = dynamic_cast<CrabEnemy*>(this))
    {
        x = static_cast<float>(rand() % windowSize.x) - 20.f;
        y = static_cast<float>(rand() % windowSize.y) - 20.f;

        crab->getSprite().setPosition(x, y);
        crab->resetAnimation();
    }
}

// SharkEnemy Class
SharkEnemy::SharkEnemy(sf::RenderWindow* window, Player* player)
    : Enemy(window, player)
{
    m_health = 50;

    do 
    {
        m_directionX = (rand() % 3) - 1;
        m_directionY = (rand() % 3) - 1;

    } while (m_directionX == 0 && m_directionY == 0);

    setTexture();
    randomPos(window);
}

void SharkEnemy::setTexture()
{
    m_sharkTexture.loadFromFile("resource\\shark.png");
    m_sharkSprite.setTexture(m_sharkTexture);
}

void SharkEnemy::movement() 
{
    moveAlongBorder();
}

sf::FloatRect operator*(const sf::FloatRect& rect, float multiplier)
{
    return sf::FloatRect(rect.left, rect.top, rect.width * multiplier, rect.height * multiplier);
}

sf::FloatRect operator-(const sf::FloatRect& rect, float value)
{
    return sf::FloatRect(rect.left, rect.top, rect.width - value, rect.height - value);
}

void SharkEnemy::moveAlongBorder()
{
    sf::Vector2f position = m_sharkSprite.getPosition();
    sf::FloatRect bounds = m_sharkSprite.getGlobalBounds();

    if (movementSwitchClock.getElapsedTime().asSeconds() > 4.f)
    {
        switchMove = (std::rand() % 2 == 0);
        if (switchMove)
        {
            move = (std::rand() % 2 == 0) ? 1 : -1;
            m_sharkSprite.setRotation(move == 1 ? -90.f : 90.f);
        }
        else
        {
            move = (std::rand() % 2 == 0) ? 1 : -1;
            m_sharkSprite.setRotation(move == 1 ? 0.f : 180.f);
        }
        movementSwitchClock.restart();
    }

    if (switchMove)
    {
        if ((position.x <= 0 && move == -1) ||
            (position.x >= m_renderWindow->getSize().x - bounds.width && move == 1))
        {
            move = -move;
            m_sharkSprite.setRotation(move == 1 ? -90.f : 90.f);
        }
        m_sharkSprite.move(move * 2.f, 0);
    }
    else
    {
        if ((position.y <= 0 && move == -1) ||
            (position.y >= m_renderWindow->getSize().y - bounds.height && move == 1))
        {
            move = -move;
            m_sharkSprite.setRotation(move == 1 ? 0.f : 180.f);
        }
        m_sharkSprite.move(0, move * 2.f);
    }
}

void SharkEnemy::shoot(std::vector<std::unique_ptr<EnemyProjectile>>& enemyProjectiles)
{
    if (m_shootClock.getElapsedTime().asSeconds() > 6.f)
    {
        sf::Vector2f sharkCenter = getSharkCenter();
        sf::Vector2f playerPosition = m_player->getPlayerCenter();
        enemyProjectiles.emplace_back(std::make_unique<EnemyProjectile>(m_renderWindow, sharkCenter, playerPosition));
        m_shootClock.restart();
    }
}

sf::Vector2f SharkEnemy::getSharkCenter()
{
    sf::FloatRect bounds = m_sharkSprite.getGlobalBounds();
    return { bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f };
}

bool SharkEnemy::isShooting() 
{
    return true;
}

int SharkEnemy::getHp()
{
    return m_health;
}

int SharkEnemy::getShield()
{
    return 0;
}

void SharkEnemy::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health <= 0)
    {
        m_health = 0;
    }
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

void SharkEnemy::resetAnimation()
{
    m_currentFrame = 0;
    m_sharkSprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

sf::Sprite& SharkEnemy::getSprite()
{
    return m_sharkSprite;
}

sf::FloatRect SharkEnemy::getHitbox() const
{
    sf::FloatRect spriteBounds = m_sharkSprite.getGlobalBounds();

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


// CrabEnemy Class
CrabEnemy::CrabEnemy(sf::RenderWindow* window, Player* player)
    : Enemy(window, player) 
{
    m_health = 25;

    setTexture();
    randomPos(window);
}

void CrabEnemy::setTexture() 
{
    // WALK
    m_crabTexture.loadFromFile("resource\\crabWalk.png");
    m_crabSprite.setTexture(m_crabTexture);

    // ATTACK
    m_crabAttack.loadFromFile("resource\\crabAttack.png");
	m_crabAttackSprite.setTexture(m_crabAttack);
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
    return m_health;
}

int CrabEnemy::getShield()
{
    return 0;
}

void CrabEnemy::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health <= 0)
    {
        m_health = 0;
    }
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

void CrabEnemy::resetAnimation()
{
    m_currentFrame = 0;
    m_crabSprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

sf::Sprite& CrabEnemy::getSprite()
{
    return m_crabSprite;
}

sf::FloatRect CrabEnemy::getHitbox() const
{
    sf::FloatRect spriteBounds = m_crabSprite.getGlobalBounds();

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

void CrabEnemy::moveTowardsPlayer(const sf::Vector2f& playerPos, float speed)
{
    sf::Vector2f currentPos = m_crabSprite.getPosition();

    sf::FloatRect playerBounds = m_player->getHitbox();
    sf::Vector2f targetPos = 
    {
        playerPos.x + playerBounds.width,
        playerPos.y + playerBounds.height
    };

    float dx = targetPos.x - currentPos.x;
    float dy = targetPos.y - currentPos.y;

    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance > 0) 
    {
        dx /= distance;
        dy /= distance;
        m_crabSprite.move(dx * speed, dy * speed);
    }
}

CrabBoss::CrabBoss(sf::RenderWindow* window, Player* player)
    : Enemy(window, player)
{
    int m_Bosshealth = 150000;

    setTexture();
    srand(static_cast<unsigned int>(time(nullptr)));
}

void CrabBoss::setTexture()
{
    m_cBossTexture.loadFromFile("resource\\CrabBoss.png");
    m_cBossSprite.setTexture(m_cBossTexture);
    m_cBossSprite.setScale(0.5f, 0.5f);
    m_cBossSprite.setPosition(100.f, 100.f);
    m_cBossSprite.setRotation(0.f);
}

void CrabBoss::movement()
{
    sf::Vector2u windowSize = m_renderWindow->getSize();
    moveLikeACrab(windowSize);
}

bool CrabBoss::isAttacking()
{
    return true;
}

int CrabBoss::getHp()
{
    return 0;
}

int CrabBoss::getShield()
{
    return 0;
}

void CrabBoss::takeDamage(int damage)
{
    m_Bosshealth -= damage;
    if (m_Bosshealth <= 0)
    {
        m_Bosshealth = 0;
    }
}

void CrabBoss::setInvulnerable(float duration)
{
}

void CrabBoss::getWeapon()
{
}

void CrabBoss::switchWeapon()
{
}

void CrabBoss::updateAnim()
{
}

sf::Sprite& CrabBoss::getSprite()
{
    return m_cBossSprite;
}

sf::FloatRect CrabBoss::getHitbox() const
{
    return m_cBossSprite.getGlobalBounds();
}

void CrabBoss::moveLikeACrab(const sf::Vector2u& windowSize)
{
    static sf::Clock movementSwitchClock;
    static bool switchMove = true;
    static int move = 1;

    sf::Vector2f position = m_cBossSprite.getPosition();

    if (movementSwitchClock.getElapsedTime().asSeconds() > 3.f) {
        switchMove = (std::rand() % 2 == 0);
        movementSwitchClock.restart();
    }

    if (switchMove) {
        if (position.x <= 0) {
            move = 10;
            m_cBossSprite.setRotation(90.f);
        }
        else if (position.x >= (windowSize.x - 10.f) - m_cBossSprite.getGlobalBounds().width) {
            move = -10;
            m_cBossSprite.setRotation(270.f);
        }
        m_cBossSprite.move(move * 2.f, 0);
    }
    else {
        if (position.y <= 0) {
            move = 10;
            m_cBossSprite.setRotation(180.f);
        }
        else if (position.y >= (windowSize.y - 10.f) - m_cBossSprite.getGlobalBounds().height) {
            move = -10;
            m_cBossSprite.setRotation(0.f);
        }
        m_cBossSprite.move(0, move * 2.f);
    }
}