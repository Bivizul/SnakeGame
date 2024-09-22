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
		assert(data.snakeBodyTexture.loadFromFile(RESOURCES_PATH + "Snake_Body.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "table-sprite.png", sf::IntRect(62 + (64 * 20), 34 + (64 * 19), 64, 64)));
		assert(data.wallTexture.loadFromFile(RESOURCES_PATH + "table-sprite.png", sf::IntRect(62 + (64 * 14), 34 + (64 * 37), 64, 64)));
		assert(data.cupTexture.loadFromFile(RESOURCES_PATH + "table-sprite.png", sf::IntRect(62 + (64 * 4), 34 + (64 * 23), 64, 64)));

		//assert(data.appleEatBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		//assert(data.deathBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));

		data.appleEatSound.setBuffer(data.appleEatBuffer);
		data.deathSound.setBuffer(data.deathBuffer);

		// Init player
		InitPlayer(data.player, data.snakeHeadTexture);

		switch (game.options)
		{
		case GameOptions::VeryEasy:
		{
			data.player.speed = INITIAL_SPEED_VERY_EASY;
			break;
		}
		case GameOptions::Easy:
		{
			data.player.speed = INITIAL_SPEED_EASY;
			break;
		}
		case GameOptions::Normal:
		{
			data.player.speed = INITIAL_SPEED_NORMAL;
			break;
		}
		case GameOptions::Hard:
		{
			data.player.speed = INITIAL_SPEED_HARD;
			break;
		}
		case GameOptions::VeryHard:
		{
			data.player.speed = INITIAL_SPEED_VERY_HARD;
			break;
		}
		default:
			break;
		}

		data.grassSprite.setTexture(data.grassTexture);
		data.grassSprite.setScale(GetSpriteScale(data.grassSprite, { SCREEN_WIDTH, SCREEN_HEIGHT }));

		// Init apples
		data.apples.clear();
		ClearApplesGrid(data.applesGrid);
		int numApples = MIN_APPLES + rand() % (MAX_APPLES + 1 - MIN_APPLES);
		data.apples.resize(numApples);
		for (Apple& apple : data.apples)
		{
			InitApple(apple, data.appleTexture);
			//ResetAppleState(apple, data.player.segments);
			ResetAppleState(apple, {});
			AddAppleToGrid(data.applesGrid, apple);
		}

		// Init walls
		data.walls.clear();
		int numwalls = SCREEN_WIDTH / WALL_SIZE;
		data.walls.resize(numwalls);
		//for (Wall& wall : data.walls)
		////for (int x = 0; x < data.walls.size(); x += WALL_SIZE)
		//{
		//	InitWall(data.walls[], data.wallTexture);

		//}

		InitWalls(data.walls, data.wallTexture);

		//std::cout << data.walls.size() << std::endl;

		data.numEatenApples = 0;
		data.playerScore = 0;


		/*data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(24);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use arrow keys to move, ESC to exit");
		data.inputHintText.setOrigin(GetItemOrigin(data.inputHintText, { 0.f, 0.f }));*/

		data.infoBackground.setFillColor(sf::Color(75, 115, 46));

		data.scoreApple.sprite.setTexture(data.appleTexture);
		data.scoreApple.sprite.setOrigin(GetItemOrigin(data.scoreApple.sprite, { 0.5f, 0.5f }));
		data.scoreApple.sprite.setScale(GetSpriteScale(data.scoreApple.sprite, { APPLE_SIZE, APPLE_SIZE }));

		data.currentScoreText.setFont(data.font);
		data.currentScoreText.setCharacterSize(24);
		data.currentScoreText.setFillColor(sf::Color::White);
		data.currentScoreText.setString("0");
		data.currentScoreText.setOrigin(GetItemOrigin(data.currentScoreText, { 0.5f, 0.5f }));

		data.cupSprite.setTexture(data.cupTexture);
		data.cupSprite.setOrigin(GetItemOrigin(data.cupSprite, { 0.5f, 0.5f }));
		data.cupSprite.setScale(GetSpriteScale(data.cupSprite, { CUP_SIZE, CUP_SIZE }));

		data.maxScoreText.setFont(data.font);
		data.maxScoreText.setCharacterSize(24);
		data.maxScoreText.setFillColor(sf::Color::White);
		data.maxScoreText.setString(std::to_string(game.profile.maxScore));
		data.maxScoreText.setOrigin(GetItemOrigin(data.maxScoreText, { 0.5f, 0.5f }));


		std::cout << "game.profile.maxScore " << game.profile.maxScore << std::endl;
		for (ProfileItem& item : game.recordsTable)
		{
			std::cout << item.name << " item.maxScore " << item.maxScore << std::endl;
		}
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
				ResetAppleState(*collidingApples[i], data.player.segmentsPositions);
				AddAppleToGrid(data.applesGrid, *collidingApples[i]);

				data.numEatenApples++;

				switch (game.options)
				{
				case GameOptions::VeryEasy:
				{
					data.playerScore = data.numEatenApples * 2;
					break;
				}
				case GameOptions::Easy:
				{
					data.playerScore = data.numEatenApples * 4;
					break;
				}
				case GameOptions::Normal:
				{
					data.playerScore = data.numEatenApples * 6;
					break;
				}
				case GameOptions::Hard:
				{
					data.playerScore = data.numEatenApples * 8;
					break;
				}
				case GameOptions::VeryHard:
				{
					data.playerScore = data.numEatenApples * 10;
					break;
				}
				default:
					break;
				}
				data.appleEatSound.play();

				Grow(data.player, data.snakeBodyTexture);

				std::cout << data.player.segments.size() << std::endl;
			}
		}

		//&& !((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples);

	/*for (Wall& wall : data.walls)
	{
		if (FindPlayerCollisionWithWall(data.player.position, wall.position))
		{
			SetGameOverState(data, game);
		}
	}*/

		if (HasPlayerCollisionWithScreenBorder(data.player) || HasPlayerCollisionWithBody(data.player))
		{
			SetGameOverState(data, game);
		}

		data.currentScoreText.setString(std::to_string(data.playerScore));
	}

	void SetGameOverState(GameStatePlayingData& data, Game& game)
	{
		data.deathSound.play();
		for (ProfileItem& item : game.recordsTable)
		{
			if (item.name == game.profile.name)
			{
				item.currentScore = data.playerScore;
				game.profile.currentScore = data.playerScore;
				if (data.playerScore > game.profile.maxScore)
				{
					item.maxScore = data.playerScore;
					game.profile.maxScore = data.playerScore;
				}
				break;
			}
		}

		std::sort(std::begin(game.recordsTable), std::end(game.recordsTable));

		PushGameState(game, GameStateType::GameOver, false);
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.grassSprite);

		data.infoBackground.setSize({ SCREEN_WIDTH,INFO_HEIGHT });
		window.draw(data.infoBackground);

		DrawPlayer(data.player, window);

		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}
		for (Wall& wall : data.walls)
		{
			DrawWall(wall, window);
		}

		sf::Vector2f viewSize = window.getView().getSize();

		data.scoreApple.sprite.setPosition(OurVectorToSf({ 40.f,  40.f }));
		window.draw(data.scoreApple.sprite);

		data.currentScoreText.setPosition(data.scoreApple.sprite.getPosition().x + 40.f, data.scoreApple.sprite.getPosition().y);
		window.draw(data.currentScoreText);

		data.cupSprite.setPosition(OurVectorToSf({ data.currentScoreText.getPosition().x + 100.f, data.currentScoreText.getPosition().y}));
		window.draw(data.cupSprite);

		data.maxScoreText.setPosition(data.cupSprite.getPosition().x + 40.f, data.cupSprite.getPosition().y);
		window.draw(data.maxScoreText);
	}
}