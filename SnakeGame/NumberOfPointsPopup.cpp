#include "NumberOfPointsPopup.h"
#include <assert.h>

namespace SnakeGame
{
	void InitNumberOfPointsPopup(NumberOfPointsPopup& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/RobotoMono-Regular.ttf"));

		data.background.setFillColor(sf::Color(0, 0, 0, 128));

		data.popupBackground.setSize({ 400,650 });
		data.popupBackground.setFillColor(sf::Color::Black);
		data.popupBackground.setOutlineThickness(6);
		data.popupBackground.setOutlineColor(sf::Color::White);
		data.popupBackground.setOrigin(data.popupBackground.getSize().x / 2, data.popupBackground.getSize().y / 2);

		data.buttonNav.rootButtons.children.push_back(&data.startGameButton);
		data.buttonNav.rootButtons.children.push_back(&data.mainMenuButton);

		//--------------------------------------------------

		data.titleScreenText.setString(L"Количество очков");
		data.titleScreenText.setFont(data.font);
		data.titleScreenText.setCharacterSize(32);
		data.titleScreenText.setFillColor(sf::Color::White);
		data.titleScreenText.setOrigin(GetItemOrigin(data.titleScreenText, { 0.5f, 0.f }));
		data.titleScreenText.setStyle(sf::Text::Bold);

		data.playerScoreText.setString(std::to_string(game.profile.currentScore));
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
			data.recordsText.setString(data.recordsText.getString() + "\n" + game.recordsTable[i].name + ": " + std::to_string(game.recordsTable[i].maxScore));

		}
		data.recordsText.setFont(data.font);
		data.recordsText.setCharacterSize(24);
		data.recordsText.setFillColor(sf::Color::White);
		data.recordsText.setOrigin(GetItemOrigin(data.recordsText, { 0.5f, 0.f }));

		//--------------------------------------------------

		std::string sg = "Start\ngame";
		std::string mm = "Main\nmenu";

		//std::string s = "Начать\nигру";	// попытки включить русский язык для форматированных кнопок
		//std::wstring s = L"Начать\nигру";
		//InitButton(data.startGameButton, data.font, L"Начать\nигру");
		//InitButton(data.startGameButton, data.font, sg);
		//InitButton(data.mainMenuButton, data.font, L"В главное\nменю");
		//InitButton(data.mainMenuButton, data.font, mm);


		data.startGameButton.shape.setSize({ 200.f, 80.f });
		data.startGameButton.shape.setFillColor(sf::Color::White);
		data.startGameButton.shape.setOrigin(data.startGameButton.shape.getSize().x / 2, data.startGameButton.shape.getSize().y / 2);
		data.startGameButton.shape.setOutlineColor(sf::Color::White);
		data.startGameButton.shape.setOutlineThickness(4.f);

		data.startGameButton.text.setFont(data.font);
		data.startGameButton.text.setCharacterSize(24);
		data.startGameButton.text.setFillColor(sf::Color::Black);
		data.startGameButton.text.setString(sg);
		data.startGameButton.text.setOrigin(GetItemOrigin(data.startGameButton.text, { 0.0f, 0.5f }));

		data.mainMenuButton.shape.setSize({ 200.f, 80.f });
		data.mainMenuButton.shape.setFillColor(sf::Color::White);
		data.mainMenuButton.shape.setOrigin(data.mainMenuButton.shape.getSize().x / 2, data.mainMenuButton.shape.getSize().y / 2);
		data.mainMenuButton.shape.setOutlineColor(sf::Color::White);
		data.mainMenuButton.shape.setOutlineThickness(4.f);

		data.mainMenuButton.text.setFont(data.font);
		data.mainMenuButton.text.setCharacterSize(24);
		data.mainMenuButton.text.setFillColor(sf::Color::Black);
		data.mainMenuButton.text.setString(mm);
		data.mainMenuButton.text.setOrigin(GetItemOrigin(data.mainMenuButton.text, { 0.0f, 0.5f }));

		InitButtonItem(data.buttonNav.rootButtons);
		SelectButtonNavItem(data.buttonNav, &data.startGameButton);
	}

	void ShutdownNumberOfPointsPopup(NumberOfPointsPopup& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleNumberOfPointsPopupWindowEvent(NumberOfPointsPopup& data, Game& game, const sf::Event& event)
	{
		if (!data.buttonNav.selectedButton)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.buttonNav.selectedButton == &data.startGameButton)
				{
					game.keyPressedSound.play();
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.buttonNav.selectedButton == &data.mainMenuButton)
				{
					game.keyPressedSound.play();
					SwitchGameState(game, GameStateType::MainMenu);
				}
				else
				{
					//	nothing
				}
			}

			Orientation orientation = data.buttonNav.selectedButton->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::A)
			{
				game.keyPressedSound.play();
				SelectPreviousButtonNavItem(data.buttonNav);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::D)
			{
				game.keyPressedSound.play();
				SelectNextButtonNavItem(data.buttonNav);
			}
		}
	}

	void UpdateNumberOfPointsPopup(NumberOfPointsPopup& data, Game& game)
	{
		data.recordsText.setString("");
		for (int i = 0; i < 6; ++i)
		{
			data.recordsText.setString(data.recordsText.getString() + "\n" + FormatTableScore(i, game.recordsTable[i].maxScore));
		}
		data.recordsText.setOrigin(GetItemOrigin(data.recordsText, { 0.5f, 0.f }));
	}

	void DrawNumberOfPointsPopup(NumberOfPointsPopup& data, float x, float y, sf::RenderWindow& window)
	{
		data.popupBackground.setPosition(x, y);
		window.draw(data.popupBackground);

		sf::Vector2f viewSize = (sf::Vector2f)data.popupBackground.getSize();
		sf::Vector2f viewPosition = (sf::Vector2f)data.popupBackground.getPosition();

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