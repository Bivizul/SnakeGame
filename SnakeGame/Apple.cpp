#include "Apple.h"
#include "GameSettings.h"
#include <assert.h>
#include <cstdlib>

namespace SnakeGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetItemOrigin(apple.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isEaten)
		{
			return;
		}

		apple.sprite.setPosition(OurVectorToSf(apple.position));
		window.draw(apple.sprite);
	}

	void MarkAppleAsEaten(Apple& apple)
	{
		apple.isEaten = true;
	}

	void ResetAppleState(Apple& apple, std::vector<Position> prohibitedPositions)
	{
		float newX, newY;
		do {
			newX = WALL_SIZE + ((float)(rand() % (SCREEN_WIDTH - ((int)WALL_SIZE * 2) + 1)));
			newY = INFO_HEIGHT + WALL_SIZE + ((float)(rand() % (SCREEN_HEIGHT - ((int)WALL_SIZE * 2) - INFO_HEIGHT + 1)));
		} while (IsPositionProhibited(newX, newY, prohibitedPositions));

		// Присваиваем новые координаты яблоку
		apple.position.x = newX;
		apple.position.y = newY;
		apple.isEaten = false;
	}

	void ClearApplesGrid(ApplesGrid& applesGrid)
	{
		applesGrid.cells.clear();
	}

	void AddAppleToGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		Vector2D appleCornerTL = apple.position + Vector2D{ -APPLE_SIZE / 2, -APPLE_SIZE / 2 };
		Vector2D appleCornerBR = apple.position + Vector2D{ APPLE_SIZE / 2, APPLE_SIZE / 2 };

		const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
		const float cellSizeY = (float)SCREEN_HEIGHT / APPLES_GRID_CELLS_VERTICAL;

		int minCellX = std::max((int)(appleCornerTL.x / cellSizeX), 0);
		int maxCellX = std::min((int)(appleCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_HORIZONTAL - 1);
		int minCellY = std::max((int)(appleCornerTL.y / cellSizeY), 0);
		int maxCellY = std::min((int)(appleCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_VERTICAL - 1);

		for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		{
			for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
			{
				applesGrid.cells[cellX][cellY].apples.insert(&apple);
			}
		}
	}

	void RemoveAppleFromGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		for (int i = 0; i < apple.numGridCells; ++i)
		{
			ApplesGridCell* cell = apple.gridCells[i];
			cell->apples.erase(&apple);
		}
		apple.numGridCells = 0;
	}

	bool FindPlayerCollisionWithApples(const Vector2D& playerPosition, const ApplesGrid& grid, Apple** result, int& numFoundApples)
	{
		Vector2D playerCornerTL = playerPosition + Vector2D{ -PLAYER_SIZE / 2, -PLAYER_SIZE / 2 };
		Vector2D playerCornerBR = playerPosition + Vector2D{ PLAYER_SIZE / 2, PLAYER_SIZE / 2 };

		const float cellSizeX = (float)SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL;
		const float cellSizeY = (float)SCREEN_HEIGHT / APPLES_GRID_CELLS_VERTICAL;

		int minCellX = std::max((int)(playerCornerTL.x / cellSizeX), 0);
		int maxCellX = std::min((int)(playerCornerBR.x / cellSizeX), (int)APPLES_GRID_CELLS_HORIZONTAL - 1);
		int minCellY = std::max((int)(playerCornerTL.y / cellSizeY), 0);
		int maxCellY = std::min((int)(playerCornerBR.y / cellSizeY), (int)APPLES_GRID_CELLS_VERTICAL - 1);

		numFoundApples = 0;

		for (int cellX = minCellX; cellX <= maxCellX; ++cellX)
		{
			for (int cellY = minCellY; cellY <= maxCellY; ++cellY)
			{
				if (grid.cells.find(cellX) != grid.cells.end() && grid.cells.at(cellX).find(cellY) != grid.cells.at(cellX).end())
				{
					for (Apple* apple : grid.cells.at(cellX).at(cellY).apples)
					{
						if (!apple->isEaten)
						{
							float dx = playerPosition.x - apple->position.x;
							float dy = playerPosition.y - apple->position.y;
							float distance = sqrt(dx * dx + dy * dy);
							if (distance < (PLAYER_SIZE + APPLE_SIZE) / 2)
							{
								result[numFoundApples] = apple;
								++numFoundApples;
							}
						}
					}
				}
			}
		}

		return numFoundApples > 0;
	}
}