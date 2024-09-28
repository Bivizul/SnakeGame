#include "Button.h"
#include "EnterNamePopup.h"
#include "Game.h"
#include "GameStateGameOver.h"
#include <assert.h>

namespace SnakeGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		data.enterNamePopup.isNeedEnterNamePopupVisible = game.profile.name == PROFILE_NAME_DEFAULT;

		InitTableRecordsPopup(data.tableRecordsPopup, game);
		InitEnterNamePopup(data.enterNamePopup, game);
		InitNumberOfPointsPopup(data.numberOfPointsPopup, game);
	}

	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (data.enterNamePopup.isNeedEnterNamePopupVisible)
		{
			HandleEnterNamePopupWindowEvent(data.enterNamePopup, game, event);
		}
		else
		{
			HandleNumberOfPointsPopupWindowEvent(data.numberOfPointsPopup, game, event);
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta)
	{
		UpdateTableRecordsPopup(data.tableRecordsPopup, game);
		UpdateNumberOfPointsPopup(data.numberOfPointsPopup, game);
		UpdateEnterNamePopup(data.enterNamePopup, game);
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f parentViewSize = (sf::Vector2f)window.getSize();

		DrawTableRecordsPopup(data.tableRecordsPopup, parentViewSize.x / 4.f * 1.4f, parentViewSize.y / 2.f, window);

		if (data.enterNamePopup.isNeedEnterNamePopupVisible)
		{
			DrawEnterNamePopup(data.enterNamePopup, parentViewSize.x / 4.f * 2.6f, parentViewSize.y / 2.f, window);
		}
		else
		{
			DrawNumberOfPointsPopup(data.numberOfPointsPopup, parentViewSize.x / 4.f * 2.6f, parentViewSize.y / 2.f, window);
		}
	}
}