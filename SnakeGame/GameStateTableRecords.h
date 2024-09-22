#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "Game.h"

namespace SnakeGame
{
	struct GameStateTableRecordsData
	{
		sf::Font font;

		sf::Text titleScreen;
		sf::Text playerScore;
		sf::Text titleTable;

		sf::Text recordsText;

		ButtonItem startGameButton;
		ButtonItem mainMenuButton;
	};

	void InitGameStateTableRecords(GameStateTableRecordsData& data, Game& game);
	void DrawGameStateTableRecords(GameStateTableRecordsData& data, sf::RenderWindow& window);
}
