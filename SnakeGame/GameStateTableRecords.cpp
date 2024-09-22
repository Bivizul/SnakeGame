#include "GameStateTableRecords.h"
#include <assert.h>
#include "GameSettings.h"
#include "Game.h"

namespace SnakeGame
{
	void InitGameStateTableRecords(GameStateTableRecordsData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Thin.ttf"));

		data.titleScreen.setString("Количество очков");
		data.titleScreen.setFont(data.font);
		data.titleScreen.setCharacterSize(48);
		data.titleScreen.setFillColor(sf::Color::White);

		data.playerScore.setString(std::to_string(game.profile.maxScore));
		data.playerScore.setFont(data.font);
		data.playerScore.setCharacterSize(48);
		data.playerScore.setFillColor(sf::Color::White);

		data.titleTable.setString("Рекорды");
		data.titleTable.setFont(data.font);
		data.titleTable.setCharacterSize(48);
		data.titleTable.setFillColor(sf::Color::White);

		for (size_t i = 0; i < 6; i++)
		{
			data.recordsText.setString(data.recordsText.getString() + "\n" + game.recordsTable[i].name + ": " + std::to_string(game.recordsTable[i].maxScore));
			
		}
		data.recordsText.setFont(data.font);
		data.recordsText.setCharacterSize(24);
		data.titleScreen.setFillColor(sf::Color::White);

	}

	void DrawGameStateTableRecords(GameStateTableRecordsData& data, sf::RenderWindow& window)
	{
		window.draw(data.titleScreen);
		window.draw(data.playerScore);
		window.draw(data.titleTable);
		window.draw(data.recordsText);
	}
}
