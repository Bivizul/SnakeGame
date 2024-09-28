#pragma once
#include "GameSettings.h"
#include "Math.h"
#include <deque>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	enum class PlayerDirection
	{
		Up = 0,
		Right,
		Down,
		Left
	};

	struct SnakeSegment 
	{
		Position position;
		sf::Sprite sprite;
		PlayerDirection direction;

		SnakeSegment(const sf::Texture& texture, float x, float y, PlayerDirection dir) : direction(dir)
		{
			position = { x, y };
			sprite.setTexture(texture);
			sprite.setPosition(x, y);
			sprite.setOrigin(GetItemOrigin(sprite, { 0.5f, 0.5f }));
			sprite.setScale(GetSpriteScale(sprite, { PLAYER_SIZE, PLAYER_SIZE }));
		}
	};

	struct Player
	{
		Position position;
		float speed = 0.f;
		PlayerDirection direction = PlayerDirection::Up;
		std::deque<SnakeSegment> segments;
		std::vector<Position> segmentsPositions;
		float timeSinceLastMove = 0.f;
	};

	void InitPlayer(Player& player, const sf::Texture& texture);
	void UpdatePlayer(Player& player, const float timeDelta);
	void Grow(Player& player, const sf::Texture& bodyTexture);
	bool HasPlayerCollisionWithScreenBorder(const Player& player);
	bool HasPlayerCollisionWithBody(const Player& player);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
}