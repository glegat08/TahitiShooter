#include "StartMenu.h"
#include "Game.h"
#include "SceneManager.h"

// START MENU
StartMenu::StartMenu(sf::RenderWindow* window, SceneManager* sceneManager, const float& framerate)
    : SceneBase(window, framerate), m_sceneManager(sceneManager)
{
    setStartText(window);
    setBackground(window);
    playAudio(window);
}

void StartMenu::setStartText(sf::RenderWindow* window)
{
    // TITLE
    m_titleFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    m_gameTitle.setFont(m_titleFont);
    m_gameTitle.setString("T A H I T I  S H O O T E R");
    m_gameTitle.setCharacterSize(72);
    m_gameTitle.setFillColor(sf::Color(255, 215, 0));
    m_gameTitle.setStyle(sf::Text::Bold);
    m_gameTitle.setOutlineThickness(2);
    m_gameTitle.setOutlineColor(sf::Color::Black);

    sf::FloatRect textBounds = m_gameTitle.getLocalBounds();
    m_gameTitle.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    m_gameTitle.setPosition(window->getSize().x / 2.f, 100.f);

    // MENU
    std::vector<std::string> titles = { "P L A Y", "C R E D I T", "E X I T" };

    m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    float boxWidth = 350.f;
    float boxHeight = 80.f;
    float startX = (window->getSize().x - boxWidth) / 2.f;
    float startY = 300.f;
    float spacing = 20.f;

    for (size_t i = 0; i < titles.size(); ++i)
    {
        sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
        box.setPosition(startX, startY + i * (boxHeight + spacing));
        m_menuBoxes.push_back(box);

        m_menuTitles.push_back(titles[i]);
    }
}

void StartMenu::setBackground(sf::RenderWindow* window)
{
    m_background.loadFromFile("resource\\tahiti.jpg");
    m_backgroundSprite.setTexture(m_background);
}

void StartMenu::playAudio(sf::RenderWindow* window)
{
    m_music.openFromFile("resource\\menu.mp3");
    m_music.play();
    m_music.setVolume(50);
}

void StartMenu::processInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_renderWindow);

        for (size_t i = 0; i < m_menuBoxes.size(); ++i)
        {
            if (m_menuBoxes[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                m_selectedIndex = i;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (m_selectedIndex < m_menuTitles.size())
        {
            const std::string& selectedOption = m_menuTitles[m_selectedIndex];

            if (selectedOption == "P L A Y")
            {
                m_sceneManager->setCurrentScene(1);
                Game* gameScene = dynamic_cast<Game*>(m_sceneManager->getCurrentScene());
                if (gameScene)
                {
                    gameScene->setAudio();
                }
                m_music.stop();
            }
            else if (selectedOption == "E X I T")
                m_renderWindow->close();
        }
    }
}

void StartMenu::update(const float& deltaTime)
{

}

void StartMenu::render()
{
    m_renderWindow->draw(m_backgroundSprite);
    m_renderWindow->draw(m_gameTitle);

    for (size_t i = 0; i < m_menuBoxes.size(); ++i)
    {


        m_renderWindow->draw(m_menuBoxes[i]);

        sf::Text text;
        text.setFont(m_font);
        text.setString(m_menuTitles[i]);
        text.setCharacterSize(36);
        text.setOutlineThickness(1);
        text.setOutlineColor(sf::Color::Black);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        text.setPosition(m_menuBoxes[i].getPosition().x + m_menuBoxes[i].getSize().x / 2.f
            , m_menuBoxes[i].getPosition().y + m_menuBoxes[i].getSize().y / 2.5f);

        if (i == m_selectedIndex)
        {
            m_menuBoxes[i].setFillColor(sf::Color(0, 0, 0, 200));
            text.setFillColor(sf::Color::Yellow);
        }
        else
        {
            m_menuBoxes[i].setFillColor(sf::Color(0, 0, 0, 80));
            text.setFillColor(sf::Color(255, 215, 0));
        }

        m_renderWindow->draw(text);
    }
}