#include "CheckBox.h"
#include "Game.h"
#include "GameStateMainMenu.h"
#include <assert.h>
#include <iostream>

namespace SnakeGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/RobotoMono-Regular.ttf"));

		data.popupBackground.setSize({ 400,600 });
		data.popupBackground.setFillColor(sf::Color::Black);
		data.popupBackground.setOutlineThickness(6);
		data.popupBackground.setOutlineColor(sf::Color::White);
		data.popupBackground.setOrigin(data.popupBackground.getSize().x / 2, data.popupBackground.getSize().y / 2);

		//--------------------------------------------------

		data.menu.rootItem.hintText.setString(L"Змейка");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Green);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.tableRecordsItem);
		data.menu.rootItem.children.push_back(&data.settingsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		data.startGameItem.text.setString(L"Начать игру");
		data.startGameItem.text.setFont(data.font);
		data.startGameItem.text.setCharacterSize(24);

		//--------------------------------------------------

		data.optionsItem.text.setString(L"Уровень сложности");
		data.optionsItem.text.setFont(data.font);
		data.optionsItem.text.setCharacterSize(24);
		data.optionsItem.hintText.setString(L"Уровень\nсложности");
		data.optionsItem.hintText.setFont(data.font);
		data.optionsItem.hintText.setCharacterSize(48);
		data.optionsItem.hintText.setFillColor(sf::Color::White);
		data.optionsItem.childrenOrientation = Orientation::Vertical;
		data.optionsItem.childrenAlignment = Alignment::Middle;
		data.optionsItem.childrenSpacing = 10.f;
		data.optionsItem.children.push_back(&data.optionsVeryEasyItem);
		data.optionsItem.children.push_back(&data.optionsEasyItem);
		data.optionsItem.children.push_back(&data.optionsNormalItem);
		data.optionsItem.children.push_back(&data.optionsHardItem);
		data.optionsItem.children.push_back(&data.optionsVeryHardItem);

		data.optionsVeryEasyItem.text.setString(L"Простой");
		data.optionsVeryEasyItem.text.setFont(data.font);
		data.optionsVeryEasyItem.text.setCharacterSize(24);

		data.optionsEasyItem.text.setString(L"Тяжелее простого");
		data.optionsEasyItem.text.setFont(data.font);
		data.optionsEasyItem.text.setCharacterSize(24);

		data.optionsNormalItem.text.setString(L"Средний");
		data.optionsNormalItem.text.setFont(data.font);
		data.optionsNormalItem.text.setCharacterSize(24);

		data.optionsHardItem.text.setString(L"Легче тяжелого");
		data.optionsHardItem.text.setFont(data.font);
		data.optionsHardItem.text.setCharacterSize(24);

		data.optionsVeryHardItem.text.setString(L"Тяжелый");
		data.optionsVeryHardItem.text.setFont(data.font);
		data.optionsVeryHardItem.text.setCharacterSize(24);

		//--------------------------------------------------

		data.tableRecordsItem.text.setString(L"Таблица рекордов");
		data.tableRecordsItem.text.setFont(data.font);
		data.tableRecordsItem.text.setCharacterSize(24);
		data.tableRecordsItem.hintText.setString(L"Таблица\nрекордов");

		sf::FloatRect textBounds = data.tableRecordsItem.hintText.getLocalBounds();

		float x = (data.popupBackground.getSize().x - textBounds.width) / 2.0f;
		float y = (data.popupBackground.getSize().y - textBounds.height) / 2.0f;

		data.tableRecordsItem.hintText.setPosition(x - textBounds.left, y - textBounds.top);

		data.tableRecordsItem.hintText.setFont(data.font);
		data.tableRecordsItem.hintText.setCharacterSize(48);
		data.tableRecordsItem.hintText.setFillColor(sf::Color::White);
		data.tableRecordsItem.childrenOrientation = Orientation::Vertical;
		data.tableRecordsItem.childrenAlignment = Alignment::Middle;
		data.tableRecordsItem.childrenSpacing = 10.f;
		data.tableRecordsItem.children.push_back(&data.recordsItem);

		for (const ProfileItem& item : game.recordsTable)
		{
			data.recordsItem.text.setString(data.recordsItem.text.getString() + "\n" + FormatTableProfile(item.name, item.maxScore));
		}
		data.recordsItem.text.setFont(data.font);
		data.recordsItem.text.setCharacterSize(24);

		//--------------------------------------------------

		data.settingsItem.text.setString(L"Настройки");
		data.settingsItem.text.setFont(data.font);
		data.settingsItem.text.setCharacterSize(24);
		data.settingsItem.hintText.setString(L"Настройки");
		data.settingsItem.hintText.setFont(data.font);
		data.settingsItem.hintText.setCharacterSize(48);
		data.settingsItem.hintText.setFillColor(sf::Color::White);
		data.settingsItem.childrenOrientation = Orientation::Vertical;
		data.settingsItem.childrenAlignment = Alignment::Min;
		data.settingsItem.childrenSpacing = 10.f;
		data.settingsItem.children.push_back(&data.settingsSoundItem);
		data.settingsItem.children.push_back(&data.settingsMusicItem);

		data.settingsSoundItem.text.setString(L"Звук          ");
		data.settingsSoundItem.text.setFont(data.font);
		data.settingsSoundItem.text.setCharacterSize(24);

		InitCheckBox(data.settingsSoundItem.checkBox, 100, 100, 24, data.font, "Sound");
		InitCheckBox(data.settingsMusicItem.checkBox, 100, 150, 24, data.font, "Music");

		data.settingsMusicItem.text.setString(L"Музыка");
		data.settingsMusicItem.text.setFont(data.font);
		data.settingsMusicItem.text.setCharacterSize(24);

		//--------------------------------------------------

		data.exitGameItem.text.setString(L"Выход");
		data.exitGameItem.text.setFont(data.font);
		data.exitGameItem.text.setCharacterSize(24);
		data.exitGameItem.hintText.setString(L"Вы уверены?");
		data.exitGameItem.hintText.setFont(data.font);
		data.exitGameItem.hintText.setCharacterSize(48);
		data.exitGameItem.hintText.setFillColor(sf::Color::White);
		data.exitGameItem.childrenOrientation = Orientation::Horizontal;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 10.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		data.yesItem.text.setString(L"Да");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);

		data.noItem.text.setString(L"Нет");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		//--------------------------------------------------

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		// No need to do anything here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.optionsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.optionsVeryEasyItem)
				{
					game.options = GameOptions::VeryEasy;
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.optionsEasyItem)
				{
					game.options = GameOptions::Easy;
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.optionsNormalItem)
				{
					game.options = GameOptions::Normal;
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.optionsHardItem)
				{
					game.options = GameOptions::Hard;
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.optionsVeryHardItem)
				{
					game.options = GameOptions::VeryHard;
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.tableRecordsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.settingsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.settingsSoundItem)
				{
					game.settings = (GameSettings)((std::uint8_t)game.settings ^ (std::uint8_t)GameSettings::SoundEnabled);
				}
				else if (data.menu.selectedItem == &data.settingsMusicItem)
				{
					game.settings = (GameSettings)((std::uint8_t)game.settings ^ (std::uint8_t)GameSettings::MusicEnabled);
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::A)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::D)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta)
	{
		bool isSoundEnabled = ((std::uint8_t)game.settings & (std::uint8_t)GameSettings::SoundEnabled) != (std::uint8_t)GameSettings::Empty;
		bool isMusicEnabled = ((std::uint8_t)game.settings & (std::uint8_t)GameSettings::MusicEnabled) != (std::uint8_t)GameSettings::Empty;

		HandleChecked(data.settingsSoundItem.checkBox,isSoundEnabled);
		HandleChecked(data.settingsMusicItem.checkBox,isMusicEnabled);
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f parentViewSize = (sf::Vector2f)window.getSize();

		data.popupBackground.setPosition(parentViewSize / 2.f);
		window.draw(data.popupBackground);

		sf::Vector2f viewSize = (sf::Vector2f)data.popupBackground.getSize();
		sf::Vector2f viewPosition = (sf::Vector2f)data.popupBackground.getPosition();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewPosition.x, viewPosition.y - (viewSize.y / 2) + 50);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewPosition, { 0.5f, 0.4f });

		if (data.menu.selectedItem->parent == &data.settingsItem)
		{
			UpdateCheckBoxPosition(data.settingsSoundItem.checkBox, data.settingsSoundItem.text);
			UpdateCheckBoxPosition(data.settingsMusicItem.checkBox, data.settingsMusicItem.text);

			DrawCheckBox(data.settingsSoundItem.checkBox, window);
			DrawCheckBox(data.settingsMusicItem.checkBox, window);
		}
	}
}