#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"

namespace SnakeGame
{
	struct Game;

	enum GameOverButton
	{
		StartGameButton = 0,
		MainMenuButton
	};

	struct GameStateGameOverData
	{
		// Resources
		sf::Font font;

		//float timeSinceGameOver = 0.f;

		// UI data
		sf::RectangleShape popup;
		sf::RectangleShape background;

		sf::Text titleScreenText;
		sf::Text playerScoreText;
		sf::Text titleTableText;

		sf::Text recordsText;
		//std::vector<ProfileItem> records;

		//GameOverButton selectButton;
		ButtonItem startGameButton;
		ButtonItem mainMenuButton;
		ButtonNav buttonNav;
	};

	// Returns pointer to the allocated data
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
}