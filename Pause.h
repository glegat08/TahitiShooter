#pragma once

#include "SceneBase.h"

class Pause : public SceneBase
{
public:
    Pause(sf::RenderWindow* window, const float& framerate);

    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void setPauseText(sf::RenderWindow* window);
    void render() override;

private:
    sf::Text m_text;
    sf::Font m_font;
    sf::RectangleShape m_pauseScreen;
};
