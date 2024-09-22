#include "Apple.h"
#include "GameSettings.h"
#include "Player.h"
#include <assert.h>
#include <iostream>

namespace SnakeGame
{
	void InitPlayer(Player& player, const sf::Texture& texture)
	{
		// Init player state
		player.position.x = (float)SCREEN_WIDTH / 2.f;
		player.position.y = (float)SCREEN_HEIGHT / 2.f;

		player.direction = PlayerDirection::Right;

		// Init sprite
		// Добавляем голову змейки  с текстурой головы
		player.segments.push_back(SnakeSegment(texture, player.position.x, player.position.y, player.direction));
	}

	void UpdatePlayer(Player& player, const float timeDelta)
	{
		// Увеличиваем время с момента последнего перемещения
		player.timeSinceLastMove += timeDelta;

		// Если прошло достаточно времени для перемещения на одну клетку
		if (player.timeSinceLastMove >= player.speed)
		{
			// Сохраняем текущую позицию и направление головы перед её перемещением
			sf::Vector2f previousHeadPosition = player.segments.front().sprite.getPosition();
			PlayerDirection previousHeadDirection = player.direction;

			// Перемещаем голову в зависимости от направления
			switch (player.direction)
			{
			case PlayerDirection::Up:
				player.position.y -= PLAYER_SIZE;  // Перемещаем на одну клетку
				break;
			case PlayerDirection::Right:
				player.position.x += PLAYER_SIZE;
				break;
			case PlayerDirection::Down:
				player.position.y += PLAYER_SIZE;
				break;
			case PlayerDirection::Left:
				player.position.x -= PLAYER_SIZE;
				break;
			}

			// Обновляем позицию головы на основе новой позиции
			player.segments.front().sprite.setPosition(player.position.x, player.position.y);
			player.segments.front().direction = player.direction;

			// Обновляем позиции сегментов тела
			sf::Vector2f prevPos = previousHeadPosition;
			for (size_t i = 1; i < player.segments.size(); ++i)
			{
				sf::Vector2f tempPos = player.segments[i].sprite.getPosition();
				PlayerDirection tempDir = player.segments[i].direction;

				// Устанавливаем сегмент на позицию предыдущего сегмента
				player.segments[i].sprite.setPosition(prevPos);
				player.segments[i].direction = previousHeadDirection;

				// Обновляем предыдущую позицию и направление
				prevPos = tempPos;
				previousHeadDirection = tempDir;
			}

			// Сбрасываем счетчик времени после перемещения
			player.timeSinceLastMove = 0.f;

			player.segmentsPositions.clear();
			for (const auto& segment : player.segments) {
				player.segmentsPositions.push_back(segment.position);
			}
		}
	}

	// Функция для удлинения змейки
	void Grow(Player& player, const sf::Texture& bodyTexture) {
		// Получаем позицию и направление последнего сегмента
		sf::Vector2f tailPos = player.segments.back().sprite.getPosition();
		PlayerDirection tailDirection = player.segments.back().direction;

		// Добавляем новый сегмент с той же текстурой и направлением, что у последнего сегмента
		player.segments.push_back(SnakeSegment(bodyTexture, tailPos.x, tailPos.y, tailDirection));
	}

	bool HasPlayerCollisionWithScreenBorder(const Player& player)
	{
		return !IsPointInRect(player.position, { WALL_SIZE + PLAYER_SIZE / 2,INFO_HEIGHT + WALL_SIZE + PLAYER_SIZE / 2 }, { (float)SCREEN_WIDTH - WALL_SIZE - PLAYER_SIZE / 2, (float)SCREEN_HEIGHT - WALL_SIZE - PLAYER_SIZE / 2 });
	}

	bool HasPlayerCollisionWithBody(const Player& player)
	{
		if (player.segments.size() > 2)
		{
			const auto& headPosition = player.segments.front().sprite.getPosition();
			for (size_t i = 1; i < player.segments.size(); ++i)
			{
				const auto& bodySegmentPosition = player.segments[i].sprite.getPosition();
				if (headPosition.x == bodySegmentPosition.x && headPosition.y == bodySegmentPosition.y)
				{
					return true;
				}
			}
		}
		return false;
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		for (auto& segment : player.segments)
		{
			// Поворот сегмента в зависимости от его направления
			const sf::Vector2f spriteScale = GetSpriteScale(segment.sprite, { PLAYER_SIZE, PLAYER_SIZE });
			switch (segment.direction)
			{
			case PlayerDirection::Up:
				segment.sprite.setScale(spriteScale.x, spriteScale.y);
				segment.sprite.setRotation(-90.f);
				break;
			case PlayerDirection::Right:
				segment.sprite.setScale(spriteScale.x, spriteScale.y);
				segment.sprite.setRotation(0.f);
				break;
			case PlayerDirection::Down:
				segment.sprite.setScale(spriteScale.x, spriteScale.y);
				segment.sprite.setRotation(90.f);
				break;
			case PlayerDirection::Left:
				segment.sprite.setScale(-spriteScale.x, spriteScale.y);
				segment.sprite.setRotation(0.f);
				break;
			}
			window.draw(segment.sprite);
		}
	}
}