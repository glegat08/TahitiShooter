#pragma once

#include "SceneBase.h"

class SceneManager;

class Pause : public SceneBase
{
public:
    Pause(sf::RenderWindow* window, const float& framerate);

    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void setPauseText(sf::RenderWindow* window);
    void render() override;
    //void displayBackButton();
    //void handleBackButtonClick(const sf::Vector2f& mousePos);

private:
    SceneManager* m_sceneManager;
    sf::Text m_text;
    sf::Font m_font;
    sf::Text m_backPauseText;
    sf::RectangleShape m_pauseScreen;
};
