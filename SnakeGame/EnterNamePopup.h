#pragma once
#include "Game.h"
#include "Menu.h"
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	struct EnterNamePopup
	{
		sf::Font font;
		sf::RectangleShape popupBackground;

		sf::Text titleText;

		MenuItem noItem;
		MenuItem yesItem;
		Menu menu;

		bool isNeedEnterNamePopupVisible;

		std::string playerName;
		bool isEnteringName = false;

		sf::Clock caretClock;
		bool isCaretVisible = true;
	};

	void InitEnterNamePopup(EnterNamePopup& data, Game& game);
	void ShutdownEnterNamePopup(EnterNamePopup& data, Game& game);
	void HandleEnterNamePopupWindowEvent(EnterNamePopup& data, Game& game, const sf::Event& event);
	void UpdateEnterNamePopup(EnterNamePopup& data, Game& game);
	void DrawEnterNamePopup(EnterNamePopup& data, float x, float y, sf::RenderWindow& window);
}