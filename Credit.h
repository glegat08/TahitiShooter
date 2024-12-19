#pragma once

#include "SceneBase.h"

class SceneManager;

class Credit : public SceneBase
{
public:
    Credit(sf::RenderWindow* window, SceneManager* sceneManager, const float& framerate);
    void setAudio();
    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void render() override;

private:
    void setBackground();
    void setText();
    void displayCredits();
    void displayBackButton();
    void handleBackButtonClick(const sf::Vector2f& mousePos);

    SceneManager* m_sceneManager;
    sf::Font m_font;
    sf::Text m_creditsText;
    sf::Text m_backText;
    sf::RectangleShape m_backButton;
    sf::Texture m_background;
    sf::Sprite m_backgroundSprite;
    sf::Music m_creditMusic;
};