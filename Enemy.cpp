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
    m_sharkTexture.loadFromFile("C:\\Users\\noemo\\Pictures\\Projet\\shark.png");
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
    m_crabTexture.loadFromFile("C:\\Users\\noemo\\Pictures\\Projet\\crabWalk.png");
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


// SharkBoss Class
SharkBoss::SharkBoss(sf::RenderWindow* window, Player* player)
    : Enemy(window, player)
{
    setTexture();
}

void SharkBoss::setTexture()
{
    m_sBossTexture.loadFromFile("C:\\Users\\noemo\\Pictures\\Projet\\sharkBoss.png");
    m_sBossSprite.setTexture(m_sBossTexture);
    m_sBossSprite.setScale(-1.f, 1.f);
}

void SharkBoss::movement()
{
    sf::Vector2u windowSize = m_renderWindow->getSize();
    moveNextToWindow(windowSize, 5.f);
}


bool SharkBoss::isAttacking()
{
    return true;
}

int SharkBoss::getHp()
{
    return 0;
}

int SharkBoss::getShield()
{
    return 0;
}

void SharkBoss::takeDamage(int damage)
{
}

void SharkBoss::setInvulnerable(float duration)
{
}

void SharkBoss::getWeapon()
{
}

void SharkBoss::switchWeapon()
{
}

void SharkBoss::updateAnim()
{

}

sf::Sprite& SharkBoss::getSprite()
{
    return m_sBossSprite;
}

sf::FloatRect SharkBoss::getHitbox() const
{
    return m_sBossSprite.getGlobalBounds();
}

void SharkBoss::moveNextToWindow(const sf::Vector2u& windowSize, float speed)
{
    sf::Vector2f position = m_sBossSprite.getPosition();

    sf::FloatRect bounds = m_sBossSprite.getGlobalBounds();

    static sf::Vector2f direction = { (rand() % 2 == 0 ? speed : -speed), 0 };

    if (position.x + bounds.width < 0 || position.x > static_cast<float>(windowSize.x)) {
        position.x = (rand() % 2 == 0) ? -bounds.width : static_cast<float>(windowSize.x);
        position.y = (rand() % 2 == 0) ? 0 : static_cast<float>(windowSize.y) - bounds.height;

        direction.x = (position.x < 0) ? speed : -speed;
        direction.y = 0; 

        m_sBossSprite.setPosition(position);
    }

    if (position.y <= 0) {
        position.y = 0;
    }
    else if (position.y + bounds.height >= static_cast<float>(windowSize.y)) {
        position.y = static_cast<float>(windowSize.y) - bounds.height;
    }

    m_sBossSprite.setPosition(position);

    m_sBossSprite.move(direction);
}

// CrabBoss Class
CrabBoss::CrabBoss(sf::RenderWindow* window, Player* player)
    : Enemy(window, player)
{
    setTexture();
    srand(static_cast<unsigned int>(time(nullptr)));
}

void CrabBoss::setTexture()
{
    m_cBossTexture.loadFromFile("C:\\Users\\noemo\\Pictures\\Projet\\CrabBoss.png");
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
            move = 1;
            m_cBossSprite.setRotation(90.f);
        }
        else if (position.x >= (windowSize.x - 10.f) - m_cBossSprite.getGlobalBounds().width) {
            move = -1;
            m_cBossSprite.setRotation(270.f); 
        }
        m_cBossSprite.move(move * 2.f, 0);
    }
    else {
        if (position.y <= 0) {
            move = 1;
            m_cBossSprite.setRotation(180.f); 
        }
        else if (position.y >= (windowSize.y - 10.f) - m_cBossSprite.getGlobalBounds().height) {
            move = -1;
            m_cBossSprite.setRotation(0.f); 
        }
        m_cBossSprite.move(0, move * 2.f);
    }
}

