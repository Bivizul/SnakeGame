#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	struct Wall
	{
		Position position;
		sf::Sprite sprite;
	};

	void InitWall(Wall& wall, const sf::Texture& texture);
	void InitWalls(std::vector<Wall>& walls, const sf::Texture& texture);
	void DrawWall(Wall& wall, sf::RenderWindow& window);
	bool FindPlayerCollisionWithWall(const Vector2D& playerPosition, const Vector2D& wallPosition);
}