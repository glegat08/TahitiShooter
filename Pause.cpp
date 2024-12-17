#include "Pause.h"

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

    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    m_text.setPosition(window->getSize().x / 2, window->getSize().y / 2);
}

void Pause::render()
{
    m_renderWindow->draw(m_pauseScreen);
    m_renderWindow->draw(m_text);
}
