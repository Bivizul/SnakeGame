#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace SnakeGame
{
	struct CheckBox
	{
		sf::RectangleShape box;
		sf::Text checkMark;
		sf::Text label;
		Position position;
		bool isChecked;
	};

	void InitCheckBox(CheckBox& checkBox, float x, float y, float size, const sf::Font& font, const std::string& labelText);

	void DrawCheckBox(CheckBox& checkBox, sf::RenderWindow& window);

	void UpdateCheckBoxPosition(CheckBox& checkBox, const sf::Text& menuItemText);

	void HandleClick(CheckBox& checkBox, float mouseX, float mouseY);

	void HandleChecked(CheckBox& checkBox, bool check);

	bool IsCheckedStatus(CheckBox& checkBox);

}