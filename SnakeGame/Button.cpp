#include "Button.h"
#include "Math.h"
#include <iostream>

namespace SnakeGame
{
	void InitButton(Button& button, sf::Font& font, std::string& text)
	//void InitButton(Button& button, sf::Font& font, std::wstring& text)
	//void InitButton(Button& button, sf::Font& font, const wchar_t text[])
	{
		button.shape.setSize({ 200.f, 80.f });
		button.shape.setFillColor(sf::Color::White);
		//button.shape.setOrigin({ 0.5f, 0.5f });
		button.shape.setOrigin(button.shape.getSize().x / 2, button.shape.getSize().y / 2);
		button.shape.setOutlineColor(sf::Color::Cyan);
		button.shape.setOutlineThickness(4.f);

		button.text.setFont(font);
		button.text.setCharacterSize(24);
		button.text.setFillColor(sf::Color::Red);
		button.text.setString(text);
		button.text.setOrigin(GetItemOrigin(button.text, { 0.0f, 0.5f }));
	}

	void DrawButton(Button& button, float x, float y, sf::RenderWindow& window)
	{
		button.shape.setPosition(x, y);
		window.draw(button.shape);

		button.text.setPosition(x, y);
		CenterText(button.text, window);
		//window.draw(button.text);
	}
}