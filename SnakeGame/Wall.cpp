#include "GameSettings.h"
#include "Math.h"
#include "Wall.h"

namespace SnakeGame
{
	void InitWall(Wall& wall, const sf::Texture& texture)
	{
		wall.sprite.setTexture(texture);
		wall.sprite.setOrigin(GetItemOrigin(wall.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		wall.sprite.setScale(GetSpriteScale(wall.sprite, { WALL_SIZE, WALL_SIZE }));
		//wall.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		//for (int x = 0; x < SCREEN_WIDTH; x += 20) {
			// Верхняя стена
			//sf::Sprite topWall;
			//wall.sprite.setTexture(texture);
			//wall.sprite.setPosition(x, 20); // Позиция сверху
			//wall.sprite.setRotation(180); // Поворачиваем верхушкой к центру
			//walls.push_back(topWall);

			//// Нижняя стена
			//sf::Sprite bottomWall;
			//bottomWall.setTexture(wallTexture);
			//bottomWall.setPosition(x, window.getSize().y - tileSize); // Позиция снизу
			//bottomWall.setRotation(0); // Верхушка смотрит вверх
			//walls.push_back(bottomWall);
		//}

		/*wall.shape.setSize(sf::Vector2f(WALL_SIZE, WALL_SIZE));
		wall.shape.setFillColor(sf::Color::Cyan);
		wall.shape.setOrigin(WALL_SIZE / 2, WALL_SIZE / 2);
		wall.shape.setPosition(playerX, playerY);*/
	}

	void InitWalls(std::vector<Wall>& walls, const sf::Texture& texture)
	{
		//wall.sprite.setTexture(texture);
		//wall.sprite.setOrigin(GetItemOrigin(wall.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		//wall.sprite.setScale(GetSpriteScale(wall.sprite, { WALL_SIZE, WALL_SIZE }));
		//wall.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		for (float x = 0.f; x < SCREEN_WIDTH; x += WALL_SIZE)
		{
			// Верхняя стена
			Wall topWall;
			topWall.sprite.setTexture(texture);
			topWall.sprite.setRotation(180); // Поворачиваем верхушкой к центру
			topWall.sprite.setOrigin(GetItemOrigin(topWall.sprite, { 0.5f, 0.5f }));
			topWall.sprite.setScale(GetSpriteScale(topWall.sprite, { WALL_SIZE, WALL_SIZE }));
			topWall.sprite.setPosition(x + WALL_SIZE / 2, INFO_HEIGHT + WALL_SIZE / 2); // Позиция сверху
			topWall.position = Vector2D{ x + WALL_SIZE / 2, WALL_SIZE / 2 };
			walls.push_back(topWall);

			// Нижняя стена
			Wall bottomWall;
			bottomWall.sprite.setTexture(texture);
			bottomWall.sprite.setRotation(0); // Поворачиваем верхушкой к центру
			bottomWall.sprite.setOrigin(GetItemOrigin(topWall.sprite, { 0.5f, 0.5f }));
			bottomWall.sprite.setScale(GetSpriteScale(bottomWall.sprite, { WALL_SIZE, WALL_SIZE }));
			bottomWall.sprite.setPosition(x + WALL_SIZE / 2, SCREEN_HEIGHT - WALL_SIZE / 2); // Позиция сверху
			bottomWall.position = Vector2D{ x + WALL_SIZE / 2, SCREEN_HEIGHT - WALL_SIZE / 2 };
			walls.push_back(bottomWall);
		}


		for (float y = INFO_HEIGHT; y < SCREEN_HEIGHT - (WALL_SIZE * 2); y += WALL_SIZE)
		{
			// Левая стена
			Wall leftWall;
			leftWall.sprite.setTexture(texture);
			leftWall.sprite.setRotation(90); // Поворачиваем верхушкой к центру
			leftWall.sprite.setOrigin(GetItemOrigin(leftWall.sprite, { 0.5f, 0.5f }));
			leftWall.sprite.setScale(GetSpriteScale(leftWall.sprite, { WALL_SIZE, WALL_SIZE }));
			leftWall.sprite.setPosition(WALL_SIZE / 2, y + WALL_SIZE + WALL_SIZE / 2); // Позиция сверху
			leftWall.position = Vector2D{ WALL_SIZE / 2,y + WALL_SIZE + WALL_SIZE / 2 };
			walls.push_back(leftWall);

			// Правая стена
			Wall rightWall;
			rightWall.sprite.setTexture(texture);
			rightWall.sprite.setRotation(270); // Поворачиваем верхушкой к центру
			rightWall.sprite.setOrigin(GetItemOrigin(rightWall.sprite, { 0.5f, 0.5f }));
			rightWall.sprite.setScale(GetSpriteScale(rightWall.sprite, { WALL_SIZE, WALL_SIZE }));
			rightWall.sprite.setPosition(SCREEN_WIDTH - WALL_SIZE / 2, y + WALL_SIZE + WALL_SIZE / 2); // Позиция сверху
			rightWall.position = Vector2D{ SCREEN_WIDTH - WALL_SIZE / 2, y + WALL_SIZE + WALL_SIZE / 2 };
			walls.push_back(rightWall);
		}
	}

	void DrawWall(Wall& wall, sf::RenderWindow& window)
	{
		//wall.sprite.setPosition(OurVectorToSf(wall.position));
		window.draw(wall.sprite);
	}

	bool FindPlayerCollisionWithWall(const Vector2D& playerPosition, const Vector2D& wallPosition)
	{
		float deltaX = (float)fabs(playerPosition.x - wallPosition.x);
		float deltaY = (float)fabs(playerPosition.y - wallPosition.y);
		return (deltaX <= (PLAYER_SIZE + WALL_SIZE) / 2.f && deltaY <= (PLAYER_SIZE + WALL_SIZE) / 2.f);
	}
}