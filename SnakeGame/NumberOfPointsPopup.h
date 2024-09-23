#pragma once
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "Button.h"

namespace SnakeGame
{
	struct NumberOfPointsPopup
	{

		sf::Font font;

		sf::RectangleShape popupBackground;
		sf::RectangleShape background;

		sf::Text titleScreenText;
		sf::Text playerScoreText;
		sf::Text titleTableText;

		sf::Text recordsText;

		ButtonItem startGameButton;
		ButtonItem mainMenuButton;
		ButtonNav buttonNav;
	};

	void InitNumberOfPointsPopup(NumberOfPointsPopup& data, Game& game);
	void ShutdownNumberOfPointsPopup(NumberOfPointsPopup& data, Game& game);
	void HandleNumberOfPointsPopupWindowEvent(NumberOfPointsPopup& data, Game& game, const sf::Event& event);
	void UpdateNumberOfPointsPopup(NumberOfPointsPopup& data, Game& game);
	void DrawNumberOfPointsPopup(NumberOfPointsPopup& data, float x, float y, sf::RenderWindow& window);
}