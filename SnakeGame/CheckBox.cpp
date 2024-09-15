#include <SFML/Graphics.hpp>
#include <iostream>
#include "CheckBox.h"

namespace SnakeGame
{
	void InitCheckBox(CheckBox& checkBox, float x, float y, float size, const sf::Font& font, const std::string& labelText)
	{
		// Создание квадрата для чекбокса
		checkBox.box.setSize(sf::Vector2f(size, size));
		checkBox.box.setFillColor(sf::Color::Black);
		checkBox.box.setOutlineThickness(2);
		checkBox.box.setOutlineColor(sf::Color::White);

		// Создание текста для галочки
		checkBox.checkMark.setFont(font);
		//checkBox.checkMark.setString(L"✔");  // Символ галочки
		checkBox.checkMark.setString("V");  // Символ галочки
		checkBox.checkMark.setCharacterSize(size);
		checkBox.checkMark.setFillColor(sf::Color::White);
		
		// Текст рядом с чекбоксом
		/*checkBox.label.setFont(font);
		checkBox.label.setString(labelText);
		checkBox.label.setCharacterSize(size);
		checkBox.label.setFillColor(sf::Color::White);*/
	}

	void DrawCheckBox(CheckBox& checkBox, sf::RenderWindow& window)
	{
		int size = 30;
		checkBox.box.setPosition(checkBox.position.x, checkBox.position.y);
		checkBox.checkMark.setPosition(checkBox.position.x, checkBox.position.y - 0.1f * size);  // Позиция чуть смещена для лучшего отображения
		//checkBox.label.setPosition(checkBox.position.x + size + 10, checkBox.position.y - 0.1f * size);

		window.draw(checkBox.box);
		if (checkBox.isChecked) {
			window.draw(checkBox.checkMark);  // Рисуем галочку, если включено
		}
		//window.draw(checkBox.label);
	}

	void UpdateCheckBoxPosition(CheckBox& checkBox, const sf::Text& menuItemText)
	{
		// Получаем позицию текста и ширину
		sf::Vector2f textPosition = menuItemText.getPosition();
		float textWidth = menuItemText.getGlobalBounds().width;

		// Устанавливаем чекбокс справа от текста
		//checkBox.position = { textPosition.x + textWidth + 20, textPosition.y };
		checkBox.position = { textPosition.x + 160, textPosition.y };
	}

	// Проверка нажатия на чекбокс
	void HandleClick(CheckBox& checkBox, float mouseX, float mouseY)
	{
		if (checkBox.box.getGlobalBounds().contains(mouseX, mouseY))
		{
			checkBox.isChecked = !checkBox.isChecked;  // Меняем состояние чекбокса
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