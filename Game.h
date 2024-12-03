#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	// Constructor and destructor
	Game() = default;
	virtual ~Game() = default;

private:
	// Define the member variables
	sf::Texture playerTexture;
	sf::Sprite player;
	sf::Texture enemyTexture;
	sf::Sprite enemy;


	// Define the member functions
	void initPlayer();
	void initEnemy();
	void initLevel();
	void update();
	void render();
	void handleInput();
	void checkCollision();
	void handleWinCondition();
	void handleLoseCondition();
	void saveGame();
	void loadGame();
	void resetGame();
	void quitGame();

	// Add any other necessary member functions and variables here
};