#include "SceneBase.h"

class Credit : public SceneBase
{
	Credit(sf::RenderWindow* window, const float& framerate);

	void setBackground();
	void setText();
	void processInput(const sf::Event& event) override;
	void update(const float& deltaTime) override;
	void render() override;
	void displayCredits();
	void displayBackButton();
	void handleBackButtonClick(const sf::Vector2f& mousePos);

private:
	sf::Texture m_background;
	sf::Sprite m_backgroundSprite;
	sf::Font m_font;
	sf::Text m_creditsText;
	sf::Text m_backText;
	sf::RectangleShape m_backButton;
	bool m_backButtonClicked = false;
};