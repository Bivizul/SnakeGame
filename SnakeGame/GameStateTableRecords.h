#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "Game.h"

namespace SnakeGame
{
	struct GameStateTableRecordsData
	{
		// Resources
		sf::Font font;

		sf::Text titleScreen;
		sf::Text playerScore;
		sf::Text titleTable;

		sf::Text recordsText;
		//std::vector<ProfileItem> records;

		ButtonItem startGameButton;
		ButtonItem mainMenuButton;
	};

	// Returns pointer to the allocated data
	void InitGameStateTableRecords(GameStateTableRecordsData& data, Game& game);
	void DrawGameStateTableRecords(GameStateTableRecordsData& data, sf::RenderWindow& window);
}
