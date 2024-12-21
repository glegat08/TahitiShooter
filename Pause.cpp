#include "Pause.h"
#include "SceneManager.h"
#include "StartMenu.h"

Pause::Pause(sf::RenderWindow* window, const float& framerate)
    : SceneBase(window, framerate)
{
    setPauseText(window);
}

void Pause::processInput(const sf::Event& event)
{

}

void Pause::update(const float& deltaTime)
{

}

void Pause::setPauseText(sf::RenderWindow* window)
{
    m_pauseScreen.setFillColor(sf::Color(0, 0, 0, 128));
    m_pauseScreen.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    m_pauseScreen.setPosition(0, 0);

    m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    m_text.setFont(m_font);
    m_text.setString("P A U S E");
    m_text.setCharacterSize(50);
    m_text.setFillColor(sf::Color::White);

    m_backPauseText.setFont(m_font);
	m_backPauseText.setString("B A C K  T O  M E N U");
    m_backPauseText.setCharacterSize(40);
	m_backPauseText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    m_text.setPosition(window->getSize().x / 2, window->getSize().y / 2);

    sf::FloatRect backBounds = m_backPauseText.getLocalBounds();
    m_backPauseText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    m_backPauseText.setPosition(window->getSize().x / 2 - 80, 800);
}

void Pause::render()
{
    m_renderWindow->draw(m_pauseScreen);
    m_renderWindow->draw(m_text);

    //m_renderWindow->draw(m_backPauseText);
    //displayBackButton();
}

//void Pause::displayBackButton()
//{
//    sf::Vector2f mousePos = m_renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_renderWindow));
//    if (m_backPauseText.getGlobalBounds().contains(mousePos))
//    {
//        m_backPauseText.setFillColor(sf::Color::Yellow);
//    }
//    else
//    {
//        m_backPauseText.setFillColor(sf::Color::White);
//    }
//
//    m_renderWindow->draw(m_backPauseText);
//}
//
//void Pause::handleBackButtonClick(const sf::Vector2f& mousePos)
//{
//    if (m_backPauseText.getGlobalBounds().contains(mousePos))
//    {
//        m_sceneManager->setCurrentScene(0);
//        StartMenu* menuScene = dynamic_cast<StartMenu*>(m_sceneManager->getCurrentScene());
//        if (menuScene)
//        {
//            menuScene->playAudio(m_renderWindow);
//        }
//    }
//}