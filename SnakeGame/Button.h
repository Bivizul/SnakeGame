#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	struct Button
	{
		sf::Text text;
		sf::RectangleShape shape;
	};

	void InitButton(Button& button, sf::Font& font, std::string& text);
	//void InitButton(Button& button, sf::Font& font, std::wstring& text);
	//void InitButton(Button& button, sf::Font& font, const wchar_t text[]);

	void DrawButton(Button& button, float x, float y, sf::RenderWindow& window);
}