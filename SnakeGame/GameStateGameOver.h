#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "TableRecordsPopup.h"

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
		sf::Font font;

		sf::RectangleShape popup;
		sf::RectangleShape background;

		sf::Text titleScreenText;
		sf::Text playerScoreText;
		sf::Text titleTableText;

		sf::Text recordsText;

		ButtonItem startGameButton;
		ButtonItem mainMenuButton;
		ButtonNav buttonNav;

		TableRecordsPopup tableRecords;
	};

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
}