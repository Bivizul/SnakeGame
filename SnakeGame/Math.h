#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
	Vector2D GetRandomPositionInScreen(float screenWidth, float screenHeight);

	typedef Vector2D Position;

	sf::Vector2f OurVectorToSf(const Vector2D& v);
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2D& desiredSize);
	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition);
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

	// Helper method for organizing text items
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

	struct ProfileItem
	{
		std::string name;
		int score = 0;
	};

	bool operator<(const ProfileItem& lhs, const ProfileItem& rhs);

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

	bool IsPointInRect(Vector2D point, Vector2D rectTL, Vector2D rectBR);

	std::string FormatTableProfile(std::string name, int score);
	std::string FormatTableScore(int number, int score);
	std::string FormatLine(std::string name, int score, int maxLineWidth);
	std::string FormatLine(int number, int score, int maxLineWidth);
	std::string FormatNumber(int value);
	std::vector<std::string> SplitString(const std::string& str, char delimiter);
	void CenterText(sf::Text& text, sf::RenderWindow& window);
	std::string ReplaceNewlines(const std::string& input);
}