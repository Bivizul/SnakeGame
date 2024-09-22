#include "Game.h"
#include "GameStatePause.h"
#include <assert.h>

namespace SnakeGame
{
	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.hintText.setString("PAUSE");
		data.hintText.setFont(data.font);
		data.hintText.setCharacterSize(24);
		data.hintText.setFillColor(sf::Color::White);
		data.hintText.setOrigin(GetItemOrigin(data.hintText, { 0.5f, 0.5f }));

		data.background.setFillColor(sf::Color(0, 0, 0, 128));

		data.pauseTimeLeft = 0.f;
		data.countdownStarted = false;
	}

	void ShutdownGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape && !data.countdownStarted)
			{
				data.pauseTimeLeft = 3.f;
				data.countdownStarted = true;
				data.hintText.setString("PAUSE\n3 seconds left");
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}

	void UpdatePause(GameStateExitDialogData& data, Game& game, float timeDelta)
	{
		if (data.countdownStarted && data.pauseTimeLeft > 0)
		{
			data.pauseTimeLeft -= timeDelta;

			int timeLeft = static_cast<int>(std::ceil(data.pauseTimeLeft));
			data.hintText.setString("PAUSE\n" + std::to_string(timeLeft) + " seconds left");

			if (data.pauseTimeLeft <= 0)
			{
				PopGameState(game);
			}
		}
	}

	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float timeDelta)
	{
		UpdatePause(data, game, timeDelta);
		
	}

	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

		data.background.setSize(windowSize);
		window.draw(data.background);

		data.hintText.setPosition(windowSize / 2.f);
		window.draw(data.hintText);
	}
}