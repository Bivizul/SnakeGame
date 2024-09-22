#pragma once
#include "Apple.h"
#include "Player.h"
#include "Wall.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>

namespace SnakeGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// Resources
		sf::Font font;

		sf::Texture snakeHeadTexture;
		sf::Texture snakeBodyTexture;
		sf::Texture appleTexture;
		sf::Texture wallTexture;

		sf::Texture cupTexture;
		sf::Sprite cupSprite;

		sf::Texture grassTexture;
		sf::Sprite grassSprite;

		sf::SoundBuffer appleEatBuffer;
		sf::SoundBuffer deathBuffer;
		sf::Sound appleEatSound;
		sf::Sound deathSound;

		// Game data
		Player player;
		std::vector<Apple> apples;
		ApplesGrid applesGrid;
		int numEatenApples = 0;
		int playerScore = 0;
		std::vector<Wall> walls;

		// UI data
		sf::Text currentScoreText;
		sf::Text maxScoreText;
		//sf::Text inputHintText;
		Apple scoreApple;

		sf::RectangleShape infoBackground;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta);
	void SetGameOverState(GameStatePlayingData& data, Game& game);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}