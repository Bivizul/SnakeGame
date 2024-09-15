#include "Game.h"
#include "GameStatePlaying.h"
#include <assert.h>
#include <iostream>

namespace SnakeGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Init game resources (terminate if error)
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		assert(data.grassTexture.loadFromFile(RESOURCES_PATH + "Grass.jpg"));

		assert(data.snakeHeadTexture.loadFromFile(RESOURCES_PATH + "Snake_Head.png"));
		//assert(data.snakeHeadTexture.loadFromFile(RESOURCES_PATH + "table-sprite.png",sf::IntRect(0,0,20,20)));
		assert(data.snakeBodyTexture.loadFromFile(RESOURCES_PATH + "Snake_Body.png"));
		//assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "table-sprite.png", sf::IntRect(62 + (64 * 5), 34 + (64 * 20), 64, 64)));
		assert(data.wallTexture.loadFromFile(RESOURCES_PATH + "table-sprite.png", sf::IntRect(62 + (64 * 14), 34 + (64 * 37), 64, 64)));

		//assert(data.appleEatBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		//assert(data.deathBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));

		data.appleEatSound.setBuffer(data.appleEatBuffer);
		data.deathSound.setBuffer(data.deathBuffer);

		// Init player
		InitPlayer(data.player, data.snakeHeadTexture);

		// Init apples
		data.apples.clear();
		ClearApplesGrid(data.applesGrid);
		int numApples = MIN_APPLES + rand() % (MAX_APPLES + 1 - MIN_APPLES);
		data.apples.resize(numApples);
		for (Apple& apple : data.apples)
		{
			InitApple(apple, data.appleTexture);
			ResetAppleState(apple);
			AddAppleToGrid(data.applesGrid, apple);
		}

		// Init walls
		data.walls.clear();
		int numwalls = SCREEN_WIDTH/WALL_SIZE;
		data.walls.resize(numwalls);
		//for (Wall& wall : data.walls)
		////for (int x = 0; x < data.walls.size(); x += WALL_SIZE)
		//{
		//	InitWall(data.walls[], data.wallTexture);

		//}

		InitWalls(data.walls, data.wallTexture);

		std::cout << data.walls.size() << std::endl;

		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::White);
		data.scoreText.setString("0");
		data.scoreText.setOrigin(GetItemOrigin(data.scoreText, { 0.f, 0.f }));

		/*data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(24);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use arrow keys to move, ESC to exit");
		data.inputHintText.setOrigin(GetItemOrigin(data.inputHintText, { 0.f, 0.f }));*/

		data.playingFieldBackground.setFillColor(sf::Color(87, 137, 51));
		data.infoBackground.setFillColor(sf::Color(75, 115, 46));
		data.scoreApple.sprite.setTexture(data.appleTexture);
		data.scoreApple.sprite.setOrigin(GetItemOrigin(data.scoreApple.sprite, { 0.f, 0.f })); // We need to use texture as origin ignores scale
		data.scoreApple.sprite.setScale(GetSpriteScale(data.scoreApple.sprite, { APPLE_SIZE, APPLE_SIZE }));

		data.grassSprite.setTexture(data.grassTexture);
		data.grassSprite.setScale(GetSpriteScale(data.grassSprite, { SCREEN_WIDTH, SCREEN_HEIGHT }));
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			data.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			data.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			data.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			data.player.direction = PlayerDirection::Left;
		}

		// Update player
		UpdatePlayer(data.player, timeDelta);

		Apple* collidingApples[MAX_APPLES_IN_CELL] = { nullptr };
		int numCollidingApples = 0;

		if (FindPlayerCollisionWithApples(data.player.position, data.applesGrid, collidingApples, numCollidingApples))
		{
			for (int i = 0; i < numCollidingApples; i++)
			{
				/*if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples)
				{*/
					// Move apple to a new random position
					ResetAppleState(*collidingApples[i]);
					AddAppleToGrid(data.applesGrid, *collidingApples[i]);
				//}
				//else
				//{
				//	// Mark apple as eaten
				//	MarkAppleAsEaten(*collidingApples[i]);
				//	RemoveAppleFromGrid(data.applesGrid, *collidingApples[i]);
				//}

				// Increase eaten apples counter
				data.numEatenApples++;
				// Increase player speed
				//if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration)
				//{
					data.player.speed += ACCELERATION;
				//}
				data.appleEatSound.play();

				Grow(data.player, data.snakeBodyTexture);

				std::cout<<data.player.segments.size()<<std::endl;
			}
		}

		bool isGameFinished = (data.numEatenApples == data.apples.size());
			//&& !((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples);

		/*for (Wall& wall : data.walls)
		{
			if (FindPlayerCollisionWithWall(data.player.position, wall.position))
			{
				SetGameOverState(data, game);
			}
		}*/

		// Check collision with screen border
		if (isGameFinished || HasPlayerCollisionWithScreenBorder(data.player))
		{
			SetGameOverState(data, game);
		}

		data.scoreText.setString(std::to_string(data.numEatenApples));
	}

	void SetGameOverState(GameStatePlayingData& data, Game& game)
	{
		data.deathSound.play();
		// Find player in records table and update his score
		for (ProfileItem& item : game.recordsTable)
		{
			if (item.name == game.profile.name)
			{
				item.score = data.numEatenApples;
				game.profile.score = data.numEatenApples;
				break;
			}
		}

		// Sort records table
		std::sort(std::begin(game.recordsTable), std::end(game.recordsTable));

		PushGameState(game, GameStateType::GameOver, false);
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{

		data.playingFieldBackground.setSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
		window.draw(data.playingFieldBackground);

		window.draw(data.grassSprite);

		data.infoBackground.setSize({ SCREEN_WIDTH,INFO_HEIGHT });
		window.draw(data.infoBackground);

		// Draw player
		DrawPlayer(data.player, window);
		// Draw apples
		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}
		for (Wall& wall : data.walls)
		{
			DrawWall(wall, window);
		}
																						        
		sf::Vector2f viewSize = window.getView().getSize();
		data.scoreText.setPosition(40.f, 5.f);
		window.draw(data.scoreText);
		/*data.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(data.inputHintText);*/
		data.scoreApple.sprite.setPosition(OurVectorToSf({ 10.f,10.f }));
		window.draw(data.scoreApple.sprite);
	}
}