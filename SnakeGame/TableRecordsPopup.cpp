#include "TableRecordsPopup.h"
#include <assert.h>
#include "GameSettings.h"
#include "Game.h"

namespace SnakeGame
{
	void InitTableRecordsPopup(TableRecordsPopup& data, Game& game)
	{

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/RobotoMono-Regular.ttf"));

		data.popupBackground.setSize({ 400,650 });
		data.popupBackground.setFillColor(sf::Color::Black);
		data.popupBackground.setOutlineThickness(6);
		data.popupBackground.setOutlineColor(sf::Color::White);
		data.popupBackground.setOrigin(data.popupBackground.getSize().x / 2, data.popupBackground.getSize().y / 2);

		data.titleText.setFont(data.font);
		data.titleText.setCharacterSize(32);
		data.titleText.setString(L"Таблица рекордов");
		data.titleText.setOrigin(GetItemOrigin(data.titleText, { 0.5f, 0.f }));

		data.recordsText.setFont(data.font);
		data.recordsText.setCharacterSize(24);
		for (const ProfileItem& item : game.recordsTable)
		{
			data.recordsText.setString(data.recordsText.getString() + "\n" + FormatTableProfile(item.name, item.maxScore));
		}
		data.recordsText.setOrigin(GetItemOrigin(data.recordsText, { 0.5f, 0.5f }));

	}

	void DrawTableRecordsPopup(TableRecordsPopup& data, float x, float y, sf::RenderWindow& window)
	{
		data.popupBackground.setPosition(x, y);

		sf::Vector2f viewSize = (sf::Vector2f)data.popupBackground.getSize();
		sf::Vector2f viewPosition = (sf::Vector2f)data.popupBackground.getPosition();

		data.titleText.setPosition(viewPosition.x, viewPosition.y - (viewSize.y / 2) + 50);
		data.recordsText.setPosition(viewPosition.x, viewPosition.y);


		window.draw(data.popupBackground);
		window.draw(data.titleText);
		window.draw(data.recordsText);
	}
}
