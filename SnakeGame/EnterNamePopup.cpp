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

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.noItem)
				{
					data.isNeedEnterNamePopupVisible = false;
				}
				else if(data.menu.selectedItem == &data.yesItem)
				{
					//CollapseSelectedItem(data.menu);
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

	void UpdateEnterNamePopup(EnterNamePopup& data, Game& game)
	{

	}

	void DrawEnterNamePopup(EnterNamePopup& data, float x, float y, sf::RenderWindow& window)
	{
		data.popupBackground.setPosition(x,y);
		window.draw(data.popupBackground);

		sf::Vector2f viewSize = (sf::Vector2f)data.popupBackground.getSize();
		sf::Vector2f viewPosition = (sf::Vector2f)data.popupBackground.getPosition();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewPosition.x, viewPosition.y - (viewSize.y / 2) + 50);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewPosition, { 0.5f, 0.4f });
	}
}
