#include "Credit.h"
#include "SceneManager.h"
#include "StartMenu.h"

Credit::Credit(sf::RenderWindow* window, SceneManager* sceneManager, const float& framerate)
    : SceneBase(window, framerate)
    , m_sceneManager(sceneManager) 
{
	setText();
	setBackground();
}

void Credit::setAudio()
{
	m_creditMusic.openFromFile("resource\\credit.mp3");
	m_creditMusic.setVolume(50);
	m_creditMusic.play();
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
    m_creditsText.setString("                 Game created by:\n\n\n- Guillaume LE GAT\n- Noe MOCHON\n\n\n- A LA MEMOIRE DE LENI PERRICHOT -");
    m_creditsText.setCharacterSize(24);
    m_creditsText.setFillColor(sf::Color::White);

    sf::FloatRect creditsBounds = m_creditsText.getLocalBounds();
    m_creditsText.setOrigin(creditsBounds.width / 2.f, creditsBounds.height / 2.f);
    m_creditsText.setPosition(m_renderWindow->getSize().x / 2.f, m_renderWindow->getSize().y / 2.f - 100.f);

    m_backText.setFont(m_font);
    m_backText.setString("Back to Menu");
    m_backText.setCharacterSize(24);
    m_backText.setFillColor(sf::Color::White);
    m_backText.setOutlineThickness(2);
    m_backText.setOutlineColor(sf::Color::Black);

    sf::FloatRect backBounds = m_backText.getLocalBounds();
    m_backText.setOrigin(backBounds.width / 2.f, backBounds.height / 2.f);
    m_backText.setPosition(m_renderWindow->getSize().x / 2.f, m_renderWindow->getSize().y / 2.f + 100.f);
}

void Credit::processInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = m_renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_renderWindow));
        handleBackButtonClick(mousePos);
    }
}

void Credit::update(const float& deltaTime)
{
}

void Credit::render()
{
    m_renderWindow->draw(m_backgroundSprite);
    displayCredits();
    displayBackButton();
}

void Credit::displayCredits()
{
    m_renderWindow->draw(m_creditsText);
}

void Credit::displayBackButton()
{
    sf::Vector2f mousePos = m_renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_renderWindow));
    if (m_backText.getGlobalBounds().contains(mousePos))
    {
        m_backText.setFillColor(sf::Color::Yellow);
    }
    else
    {
        m_backText.setFillColor(sf::Color::White);
    }

    m_renderWindow->draw(m_backText);
}

void Credit::handleBackButtonClick(const sf::Vector2f& mousePos)
{
    if (m_backText.getGlobalBounds().contains(mousePos))
    {
        m_creditMusic.stop();
        m_sceneManager->setCurrentScene(0);
        StartMenu* menuScene = dynamic_cast<StartMenu*>(m_sceneManager->getCurrentScene());
        if (menuScene)
        {
            menuScene->playAudio(m_renderWindow);
        }
    }
}