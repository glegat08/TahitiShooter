#include "Game.h"
#include "Player.h"
#include "Enemy.h"

void Game::initPlayer()
{
	player.setPosition(100, 100);
	player.setTexture(playerTexture);
}

void Game::initEnemy()
{
	enemy.setPosition(200, 200);
	enemy.setTexture(enemyTexture);
}

void Game::initLevel()
{
}

void Game::update()
{
	player.move(0, 0);
	enemy.move(0, 0);
}

void Game::render()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Tahiti Shooter");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(player);
		window.draw(enemy);
		window.display();
	}
}

void Game::handleInput()
{
	// TODO: Implement handle input
}

void Game::checkCollision()
{
	// TODO: Implement collision detection
}

void Game::handleWinCondition()
{
	// TODO: Implement winning condition
}

void Game::handleLoseCondition()
{
	// TODO: Implement losing condition
}

void Game::saveGame()
{
	// TODO: Implement saving game state
}

void Game::loadGame()
{
	// TODO: Implement loading game state
}

void Game::resetGame()
{
	// TODO: Implement resetting game state
}

void Game::quitGame()
{
	// TODO: Implement quitting the game
}
