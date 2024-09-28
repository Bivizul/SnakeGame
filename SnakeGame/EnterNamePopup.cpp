#include "EnterNamePopup.h"
#include <assert.h>

namespace SnakeGame
{
	void InitEnterNamePopup(EnterNamePopup& data, Game& game)
	{

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/RobotoMono-Regular.ttf"));

		data.popupBackground.setSize({ 400, 300 });
		data.popupBackground.setFillColor(sf::Color::Black);
		data.popupBackground.setOutlineThickness(6);
		data.popupBackground.setOutlineColor(sf::Color::White);
		data.popupBackground.setOrigin(data.popupBackground.getSize().x / 2, data.popupBackground.getSize().y / 2);

		//--------------------------------------------------

		data.menu.rootItem.hintText.setString(L"Ввести имя");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setStyle(sf::Text::Style::Bold);
		data.menu.rootItem.hintText.setFillColor(sf::Color::White);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.noItem);
		data.menu.rootItem.children.push_back(&data.yesItem);

		data.noItem.text.setString(L"Нет");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		data.yesItem.text.setString(L"Да");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);

		//--------------------------------------------------

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.noItem);
	}

	void ShutdownEnterNamePopup(EnterNamePopup& data, Game& game)
	{
		// No need to do anything here
	}

	void HandleEnterNamePopupWindowEvent(EnterNamePopup& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (data.isEnteringName)
		{
			if (event.type == sf::Event::TextEntered)
			{
				game.keyPressedSound.play();
				if (event.text.unicode == 8 && !data.playerName.empty())
				{
					data.playerName.pop_back();
				}
				else if (event.text.unicode >= 32 && event.text.unicode <= 126 && data.playerName.length() <= 15)
				{
					data.playerName += static_cast<wchar_t>(event.text.unicode);
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
			{
				game.keyPressedSound.play();
				data.isNeedEnterNamePopupVisible = false;
				game.profile.name = data.playerName;
			}
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				game.keyPressedSound.play();
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.noItem)
				{
					game.keyPressedSound.play();
					data.isNeedEnterNamePopupVisible = false;
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					game.keyPressedSound.play();
					data.isEnteringName = true;
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::A)
			{
				game.keyPressedSound.play();
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::D)
			{
				game.keyPressedSound.play();
				SelectNextMenuItem(data.menu);
			}
		}
	}

	void UpdateEnterNamePopup(EnterNamePopup& data, Game& game)
	{
		if (data.isEnteringName) 
		{
			if (data.caretClock.getElapsedTime().asMilliseconds() > 500) 
			{
				data.isCaretVisible = !data.isCaretVisible;
				data.caretClock.restart();
			}
		}
	}

	void DrawEnterNamePopup(EnterNamePopup& data, float x, float y, sf::RenderWindow& window)
	{
		data.popupBackground.setPosition(x, y);
		window.draw(data.popupBackground);

		sf::Vector2f viewSize = (sf::Vector2f)data.popupBackground.getSize();
		sf::Vector2f viewPosition = (sf::Vector2f)data.popupBackground.getPosition();

		if (data.isEnteringName) 
		{
			sf::Text nameText;
			nameText.setFont(data.font);
			nameText.setString(data.playerName);
			nameText.setCharacterSize(30);
			nameText.setFillColor(sf::Color::White);
			nameText.setPosition(viewPosition.x - viewSize.x / 2 + 50, viewPosition.y);
			window.draw(nameText);

			if (data.isCaretVisible) 
			{
				sf::RectangleShape caret(sf::Vector2f(2, nameText.getCharacterSize()));
				caret.setFillColor(sf::Color::White);
				caret.setPosition(nameText.getPosition().x + nameText.getGlobalBounds().width, nameText.getPosition().y);
				window.draw(caret);
			}
		}
		else
		{
			sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
			hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
			hintText->setPosition(viewPosition.x, viewPosition.y - (viewSize.y / 2) + 50);
			window.draw(*hintText);

			DrawMenu(data.menu, window, viewPosition, { 0.5f, 0.4f });
		}
	}
}
