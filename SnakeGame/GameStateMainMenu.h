#pragma once
#include "Menu.h"
#include "SFML/Graphics.hpp"
#include "CheckBox.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;
		sf::RectangleShape popupBackground;

		MenuItem startGameItem;

		MenuItem optionsItem;
		MenuItem optionsVeryEasyItem;
		MenuItem optionsEasyItem;
		MenuItem optionsNormalItem;
		MenuItem optionsHardItem;
		MenuItem optionsVeryHardItem;

		MenuItem tableRecordsItem;
		MenuItem recordsItem;

		MenuItem settingsItem;
		MenuItem settingsSoundItem;
		MenuItem settingsMusicItem;

		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
}