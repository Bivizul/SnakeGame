#pragma once
#include "GameSettings.h"
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <unordered_set>

namespace SnakeGame
{
	struct Apple
	{
		Position position;
		sf::Sprite sprite;
		bool isEaten = false;

		struct ApplesGridCell* gridCells[4] = { nullptr };
		int numGridCells = 0;
	};

	void InitApple(Apple& apple, const sf::Texture& texture);
	void ResetAppleState(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	void MarkAppleAsEaten(Apple& apple);

	struct ApplesGridCell
	{
		std::unordered_set<Apple*> apples;
	};

	struct ApplesGrid
	{
		std::unordered_map<int, std::unordered_map<int, ApplesGridCell>> cells;
	};

	void ClearApplesGrid(ApplesGrid& applesGrid);
	void AddAppleToGrid(ApplesGrid& applesGrid, Apple& apple);
	void RemoveAppleFromGrid(ApplesGrid& applesGrid, Apple& apple);
	bool FindPlayerCollisionWithApples(const Vector2D& playerPosition, const ApplesGrid& grid, Apple** result, int& numFoundApples); // Result should be a pointer to an array of MAX_APPLES / 4 pointers to apples
}