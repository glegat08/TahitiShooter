#include "Credit.h"

Credit::Credit(sf::RenderWindow* window, const float& framerate)
	: SceneBase(window, framerate)
{
	setText();
	setBackground();
}

void Credit::setBackground()
{
	m_background.loadFromFile("resource\\tahiti.jpg");
	m_backgroundSprite.setTexture(m_background);
	m_backgroundSprite.setColor(sf::Color(0, 0, 0, 128));
}

void Credit::setText()
{
	m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	m_creditsText.setFont(m_font);
	m_creditsText.setString("Game created by:\n\n- Guillaume LE GAT\n- Noe MOCHON");
	m_creditsText.setCharacterSize(24);
	m_creditsText.setFillColor(sf::Color::White);
	m_creditsText.setPosition(200, 200);
	m_creditsText.setOrigin(m_creditsText.getLocalBounds().width / 2.f, m_creditsText.getLocalBounds().height / 2.f);
	m_backText.setFont(m_font);
	m_backText.setString("Back");
	m_backText.setCharacterSize(24);
	m_backText.setFillColor(sf::Color::White);
	m_backText.setPosition(200, 400);
	m_backText.setOrigin(m_backButton.getLocalBounds().width / 2.f, m_backButton.getLocalBounds().height / 2.f);
	m_backText.setOutlineThickness(2);
	m_backText.setOutlineColor(sf::Color::Black);
}

void Credit::processInput(const sf::Event& event)
{
}

void Credit::update(const float& deltaTime)
{
}

void Credit::render()
{
}

void Credit::displayCredits()
{
}

void Credit::displayBackButton()
{
}

void Credit::handleBackButtonClick(const sf::Vector2f& mousePos)
{
}
