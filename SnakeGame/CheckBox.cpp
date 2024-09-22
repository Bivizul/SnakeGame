#include <SFML/Graphics.hpp>
#include <iostream>
#include "CheckBox.h"

namespace SnakeGame
{
	void InitCheckBox(CheckBox& checkBox, float x, float y, float size, const sf::Font& font, const std::string& labelText)
	{
		checkBox.box.setSize(sf::Vector2f(size, size));
		checkBox.box.setFillColor(sf::Color::Black);
		checkBox.box.setOutlineThickness(2);
		checkBox.box.setOutlineColor(sf::Color::White);

		checkBox.checkMark.setFont(font);
		//checkBox.checkMark.setString(L"✔");
		checkBox.checkMark.setString("V");
		checkBox.checkMark.setCharacterSize(size);
		checkBox.checkMark.setFillColor(sf::Color::White);
	}

	void DrawCheckBox(CheckBox& checkBox, sf::RenderWindow& window)
	{
		int size = 30;
		checkBox.box.setPosition(checkBox.position.x, checkBox.position.y);
		checkBox.checkMark.setPosition(checkBox.position.x, checkBox.position.y - 0.1f * size);

		window.draw(checkBox.box);
		if (checkBox.isChecked) {
			window.draw(checkBox.checkMark);
		}
	}

	void UpdateCheckBoxPosition(CheckBox& checkBox, const sf::Text& menuItemText)
	{
		sf::Vector2f textPosition = menuItemText.getPosition();
		float textWidth = menuItemText.getGlobalBounds().width;
		checkBox.position = { textPosition.x + 160, textPosition.y };
	}

	void HandleClick(CheckBox& checkBox, float mouseX, float mouseY)
	{
		if (checkBox.box.getGlobalBounds().contains(mouseX, mouseY))
		{
			checkBox.isChecked = !checkBox.isChecked;
		}
	}

	void HandleChecked(CheckBox& checkBox, bool check)
	{
		checkBox.isChecked = check;
		checkBox.box.setFillColor(check ? sf::Color::Green : sf::Color::Black);
	}

	bool IsCheckedStatus(CheckBox& checkBox)
	{
		return checkBox.isChecked;
	}
}