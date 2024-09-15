#include "Button.h"
#include "Game.h"
#include "GameStateGameOver.h"
#include <assert.h>

namespace SnakeGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/RobotoMono-Regular.ttf"));

		data.background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black

		data.popup.setSize({ 400,650 });
		//data.shape.setFillColor(sf::Color(128, 128, 128));
		data.popup.setFillColor(sf::Color::Black);
		data.popup.setOutlineThickness(6);
		data.popup.setOutlineColor(sf::Color::White);
		//data.shape.setOrigin(1.5f,0.5f);
		data.popup.setOrigin(data.popup.getSize().x / 2, data.popup.getSize().y / 2);

		//--------------------------------------------------

		data.titleScreenText.setString(L"Количество очков");
		data.titleScreenText.setFont(data.font);
		data.titleScreenText.setCharacterSize(32);
		data.titleScreenText.setFillColor(sf::Color::White);
		data.titleScreenText.setOrigin(GetItemOrigin(data.titleScreenText, { 0.5f, 0.f }));
		data.titleScreenText.setStyle(sf::Text::Bold);

		data.playerScoreText.setString(std::to_string(game.profile.score));
		data.playerScoreText.setFont(data.font);
		data.playerScoreText.setCharacterSize(32);
		data.playerScoreText.setFillColor(sf::Color::White);
		data.playerScoreText.setOrigin(GetItemOrigin(data.playerScoreText, { 0.5f, 0.f }));
		data.playerScoreText.setStyle(sf::Text::Bold);

		data.titleTableText.setString(L"Рекорды");
		data.titleTableText.setFont(data.font);
		data.titleTableText.setCharacterSize(24);
		data.titleTableText.setFillColor(sf::Color::White);
		data.titleTableText.setOrigin(GetItemOrigin(data.titleTableText, { 0.5f, 0.f }));

		for (size_t i = 0; i < 6; i++)
		{
			data.recordsText.setString(data.recordsText.getString() + "\n" + game.recordsTable[i].name + ": " + std::to_string(game.recordsTable[i].score));

		}
		data.recordsText.setFont(data.font);
		data.recordsText.setCharacterSize(24);
		data.recordsText.setFillColor(sf::Color::White);
		data.recordsText.setOrigin(GetItemOrigin(data.recordsText, { 0.5f, 0.f }));

		//--------------------------------------------------

		//std::string s = "Stasfasfasrt\ngamesfd";
		//std::string s = "Начать\nигру";
		std::string s = "Start\ngame";
		//std::wstring s = L"Начать\nигру";
		//std::wstring s = L"Русский\ngamesfd";

		//InitButton(data.startGameButton, data.font, L"Начать\nигру");
		InitButton(data.startGameButton, data.font, s);
		//InitButton(data.mainMenuButton, data.font, L"В главное\nменю");
		InitButton(data.mainMenuButton, data.font, s);
	}

	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{


			if (event.key.code == sf::Keyboard::Space)
			{
				SwitchGameState(game, GameStateType::Playing);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}

	//void SelectMenuItem(Menu& menu, MenuItem* item)
	//{
	//	// It is definitely error to select root item
	//	assert(item != &menu.rootItem);

	//	if (menu.selectedItem == item)
	//	{
	//		return;
	//	}

	//	if (item && !item->isEnabled)
	//	{
	//		// Don't allow to select disabled item
	//		return;
	//	}

	//	if (menu.selectedItem)
	//	{
	//		menu.selectedItem->text.setFillColor(menu.selectedItem->deselectedColor);
	//	}

	//	menu.selectedItem = item;

	//	if (menu.selectedItem)
	//	{
	//		menu.selectedItem->text.setFillColor(menu.selectedItem->selectedColor);
	//	}
	//}

	//bool SelectPreviousMenuItem(Menu& menu)
	//{
	//	if (menu.selectedItem)
	//	{
	//		MenuItem* parent = menu.selectedItem->parent;
	//		assert(parent); // There always should be parent

	//		auto it = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
	//		if (it != parent->children.begin())
	//		{
	//			SelectMenuItem(menu, *(--it));
	//			return true;
	//		}
	//	}

	//	return false;
	//}

	//bool SelectNextMenuItem(Menu& menu)
	//{
	//	if (menu.selectedItem)
	//	{
	//		MenuItem* parent = menu.selectedItem->parent;
	//		assert(parent); // There always should be parent
	//		auto it = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
	//		if (it != parent->children.end() - 1)
	//		{
	//			SelectMenuItem(menu, *(++it));
	//			return true;
	//		}
	//	}
	//	return false;
	//}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta)
	{
		//data.timeSinceGameOver += timeDelta;

		/*sf::Color gameOverTextColor = (int)data.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		data.gameOverText.setFillColor(gameOverTextColor);*/

		/*data.recordsTableText.setString("Records:");
		for (const ProfileItem& item : game.recordsTable)
		{
			data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + item.name + ": " + std::to_string(item.score));
		}
		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));*/



		data.recordsText.setString("");
		for (int i = 0; i < 6; ++i)
		{
			data.recordsText.setString(data.recordsText.getString() + "\n" + FormatTableScore(i, game.recordsTable[i].score));
		}
		data.recordsText.setOrigin(GetItemOrigin(data.recordsText, { 0.5f, 0.f }));

		//-----------------------------------------------------

		data.startGameButton.shape.setOutlineColor(data.selectButton == GameOverButton::StartGameButton ? sf::Color::Green : sf::Color::White);
		data.mainMenuButton.shape.setOutlineColor(data.selectButton == GameOverButton::MainMenuButton ? sf::Color::Green : sf::Color::White);
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f parentViewSize = (sf::Vector2f)window.getSize();

		data.background.setSize(parentViewSize);
		window.draw(data.background);

		data.popup.setPosition(parentViewSize / 2.f);
		window.draw(data.popup);

		sf::Vector2f viewSize = (sf::Vector2f)data.popup.getSize();
		sf::Vector2f viewPosition = (sf::Vector2f)data.popup.getPosition();

		/*data.gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
		window.draw(data.gameOverText);

		data.recordsTableText.setPosition(viewSize.x / 2.f, 30.f);
		window.draw(data.recordsTableText);

		data.hintText.setPosition(viewSize.x / 2.f, viewSize.y - 10.f);
		window.draw(data.hintText);*/

		data.titleScreenText.setPosition(viewPosition.x, viewPosition.y - (viewSize.y / 2) + 50);
		window.draw(data.titleScreenText);

		data.playerScoreText.setPosition(viewPosition.x, data.titleScreenText.getPosition().y + 40);
		window.draw(data.playerScoreText);

		data.titleTableText.setPosition(viewPosition.x, data.playerScoreText.getPosition().y + 50);
		window.draw(data.titleTableText);

		data.recordsText.setPosition(viewPosition.x, data.titleTableText.getPosition().y + 24);
		window.draw(data.recordsText);

		DrawButton(data.startGameButton, viewPosition.x, data.recordsText.getPosition().y + data.recordsText.getLocalBounds().height + 100, window);
		DrawButton(data.mainMenuButton, viewPosition.x, data.startGameButton.shape.getPosition().y + 100, window);
	}
}