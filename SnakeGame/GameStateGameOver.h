#pragma once
#include "EnterNamePopup.h"
#include "NumberOfPointsPopup.h"
#include "SFML/Graphics.hpp"
#include "TableRecordsPopup.h"

namespace SnakeGame
{
	struct Game;

	enum GameOverButton
	{
		StartGameButton = 0,
		MainMenuButton
	};

	struct GameStateGameOverData
	{
		TableRecordsPopup tableRecordsPopup;
		NumberOfPointsPopup numberOfPointsPopup;
		EnterNamePopup enterNamePopup;
	};

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
}