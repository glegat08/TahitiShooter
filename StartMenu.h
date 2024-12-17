#pragma once

class SceneManager;

#include "SceneBase.h"

class StartMenu : public SceneBase
{
public:
    StartMenu(sf::RenderWindow* window, SceneManager* sceneManager, const float& framerate);

    void setStartText(sf::RenderWindow* window);
    void setBackground(sf::RenderWindow* window);
    void playAudio(sf::RenderWindow* window);
    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void render() override;

private:
    SceneManager* m_sceneManager;

    // MENU
    std::vector<std::string> m_menuTitles;
    std::vector<sf::RectangleShape> m_menuBoxes;
    sf::Font m_font;
    size_t m_selectedIndex = 0;
    std::string m_nextScene;

    // BACKGROUND
    sf::Texture m_background;
    sf::Sprite m_backgroundSprite;

    // TITLE
    sf::Text m_gameTitle;
    sf::Font m_titleFont;

    // AUDIO
    sf::Music m_music;
};