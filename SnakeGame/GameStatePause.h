#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	struct Game;

	struct GameStateExitDialogData
	{
		sf::Font font;

		sf::RectangleShape background;
		sf::Text hintText;

		float pauseTimeLeft;
		bool countdownStarted;
	};

	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void ShutdownGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event);
	void UpdatePause(GameStateExitDialogData& data, Game& game, float timeDelta);
	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float timeDelta);
	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window);
}