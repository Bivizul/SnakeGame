#pragma once
#include "Button.h"
#include "Game.h"
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	struct TableRecordsPopup
	{
		sf::Font font;
		sf::RectangleShape popupBackground;

		sf::Text titleText;
		sf::Text recordsText;
	};

	void InitTableRecordsPopup(TableRecordsPopup& data, Game& game);
	void UpdateTableRecordsPopup(TableRecordsPopup& data, Game& game);
	void DrawTableRecordsPopup(TableRecordsPopup& data, float x, float y, sf::RenderWindow& window);
}