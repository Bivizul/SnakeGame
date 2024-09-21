#pragma once
#include "SFML/Graphics.hpp"
#include "Math.h"

namespace SnakeGame
{
	struct ButtonItem
	{
		sf::Text text;
		sf::RectangleShape shape;

		Orientation childrenOrientation = Orientation::Vertical;

		sf::Color selectedColor = sf::Color::Green;
		sf::Color deselectedColor = sf::Color::White;

		bool isEnabled = true;
		std::vector<ButtonItem*> children;

		ButtonItem* parent = nullptr;
	};

	struct ButtonNav
	{
		ButtonItem rootButtons;
		ButtonItem* selectedButton = nullptr;
	};

	void InitButtonItem(ButtonItem& button);
	void SelectButtonNavItem(ButtonNav& buttonNav, ButtonItem* item);
	bool SelectPreviousButtonNavItem(ButtonNav& buttonNav);
	bool SelectNextButtonNavItem(ButtonNav& buttonNav);
	void DrawButton(ButtonItem& button, float x, float y, sf::RenderWindow& window);
}