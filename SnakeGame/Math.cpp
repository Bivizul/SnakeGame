#include "Math.h"
#include <sstream>
#include <iomanip> // ��� std::setw � std::setfill
#include <vector>
#include <iostream>

namespace SnakeGame
{
	Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		return result;
	}

	Vector2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Vector2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
		return result;
	}

	sf::Vector2f OurVectorToSf(const Vector2D& v)
	{
		return sf::Vector2f(v.x, v.y);
	}

	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2D& desiredSize)
	{
		const sf::Vector2u textureSize = sprite.getTexture()->getSize();
		const sf::Vector2f spriteScale = { desiredSize.x / textureSize.x, desiredSize.y / textureSize.y };
		return spriteScale;
	}

	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition)
	{
		const sf::Vector2u textureSize = sprite.getTexture()->getSize();
		return { relativePosition.x * textureSize.x, relativePosition.y * textureSize.y };
	}

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
	{
		sf::FloatRect totalRect;
		// Calculate total height/width of all texts
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();

			if (orientation == Orientation::Horizontal)
			{
				totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
				totalRect.height = std::max(totalRect.height, itemRect.height);
			}
			else
			{
				totalRect.width = std::max(totalRect.width, itemRect.width);
				totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
			}
		}

		totalRect.left = position.x - origin.x * totalRect.width;
		totalRect.top = position.y - origin.y * totalRect.height;
		sf::Vector2f currentPos = { totalRect.left, totalRect.top };

		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();
			sf::Vector2f itemOrigin;

			if (orientation == Orientation::Horizontal)
			{
				itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				itemOrigin.x = 0.f;
				currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
			}
			else
			{
				itemOrigin.y = 0.f;
				itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
				currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
			}

			(*it)->setOrigin(GetItemOrigin(**it, itemOrigin));
			(*it)->setPosition(currentPos);
			window.draw(**it);

			if (orientation == Orientation::Horizontal)
			{
				currentPos.x += itemRect.width + spacing;
			}
			else
			{
				currentPos.y += itemRect.height + spacing;
			}
		}
	}

	bool IsPointInRect(Vector2D point, Vector2D rectTL, Vector2D rectBR)
	{
		if (point.x < rectTL.x || point.x > rectBR.x)
		{
			return false;
		}
		if (point.y < rectTL.y || point.y > rectBR.y)
		{
			return false;
		}
		return true;
	}

	std::string FormatTableProfile(std::string name, int score)
	{
		// ������ ������ (��������, 20 ��������)
		int lineWidth = 20;

		// �������������� �����
		std::ostringstream oss;
		oss << FormatLine(name, score, lineWidth);

		return oss.str();
	}

	std::string FormatTableScore(int number, int score)
	{
		// ������ ������ (��������, 20 ��������)
		int lineWidth = 20;

		// �������������� �����
		std::ostringstream oss;
		oss << FormatLine(number, score, lineWidth);

		return oss.str();
	}


	// ������� ��� �������������� ������ � �������������
	std::string FormatLine(std::string name, int score, int maxLineWidth) {
		std::ostringstream oss;
		oss << name;

		// �������� ��������������� ����� � ��������� ������ ��� �����
		std::string formattedValue = FormatNumber(score);

		// ������������ ���������� ����������� ������������ ��� ������������
		int numLength = oss.str().length();
		int spaceForNumber = maxLineWidth - numLength - formattedValue.length();

		// ��������� ������� ��� ������������ ����� �� ������� ����
		oss << std::string(spaceForNumber, ' ') << formattedValue;

		return oss.str();
	}

	// ������� ��� �������������� ������ � �������������
	std::string FormatLine(int number, int score, int maxLineWidth) {
		std::ostringstream oss;
		oss << number << ". ";

		// �������� ��������������� ����� � ��������� ������ ��� �����
		std::string formattedValue = FormatNumber(score);

		// ������������ ���������� ����������� ������������ ��� ������������
		int numLength = oss.str().length();
		int spaceForNumber = maxLineWidth - numLength - formattedValue.length();

		// ��������� ������� ��� ������������ ����� �� ������� ����
		oss << std::string(spaceForNumber, ' ') << formattedValue;

		return oss.str();
	}

	// ������� ��� �������������� ����� � ��������� ������ ��� �����
	std::string FormatNumber(int value) {
		std::ostringstream oss;
		std::string number = std::to_string(value);
		int len = number.length();

		// ��������� ������� ������ ��� �����
		for (int i = 0; i < len; ++i) {
			oss << number[i];
			if ((len - i - 1) % 3 == 0 && i != len - 1) {
				oss << ' ';
			}
		}

		return oss.str();
	}

	// ���������� ������ �� ������
	std::vector<std::string> SplitString(const std::string& str, char delimiter) {

		//std::cout << "str " << str << std::endl;
		std::vector<std::string> lines;
		std::string line;
		std::istringstream stream(str);
		while (std::getline(stream, line, delimiter)) {
			lines.push_back(line);
		}
		return lines;
	}

	// ���������� ����� � ������ ������ ������
	void CenterText(sf::Text& text, sf::RenderWindow& window)
	{
			//// ��������� ����� �� ������ �� '\n'
			//std::vector<std::string> lines = SplitString(text.getString(), '\n');

			//text.setString("");

			//std::cout << "lines.size() " << lines.size() << std::endl;

			//// �������� ����������� ������
			//std::vector<sf::Vector2f> positions;
			//float windowWidth = window.getSize().x;
			//float yPosition = 100;  // ��������� ������� �� ��� Y
			//float totalHeight = 0;

			//for (const auto& line : lines) {
			//	// ������� ��������� ������ ������ ��� ������ ������
			//	sf::Text tempText = text;
			//	tempText.setString(line);

			//	// �������� ������� ������ ������
			//	sf::FloatRect bounds = tempText.getLocalBounds();

			//	// ���������� ������ ������ �� ��� X � ��������� �������
			//	float centeredX = (windowWidth - bounds.width) / 2;
			//	positions.push_back(sf::Vector2f(centeredX, yPosition));

			//	// ������� ������� Y ��� ��������� ������
			//	yPosition += bounds.height + 10;
			//	totalHeight += bounds.height;

			//	std::cout << line << std::endl;
			//}

			//// ������ �������������� �������� ����� � ������ ������ ������ � � �������

			//for (size_t i = 0; i < lines.size(); ++i) {
			//	// ��������� ������� ��� ������ ������ �������
			//	text.setString(text.getString() + lines[i] + '\n');
			//	text.setPosition(positions[i]);
			//	window.draw(text);
			//}

		std::cout << "text.getString().toAnsiString() " << text.getString().toAnsiString() << std::endl;

		// ��������� ����� �� ������ �� '\n'
		std::vector<std::string> lines = SplitString(text.getString(), '\n');

		// �������� ����������� ������
		//float windowWidth = window.getSize().x;
		float windowWidth = text.getPosition().x * 2;
		//float yPosition = 100;  // ��������� ������� �� ��� Y
		float yPosition = text.getPosition().y;  // ��������� ������� �� ��� Y

		for (const auto& line : lines) {
			// ������� ��������� ������ ������ ��� ������ ������
			sf::Text tempText = text;
			tempText.setString(line);
			//tempText.setOrigin(GetItemOrigin(tempText, { 0.5f, 0.5f }));

			// �������� ������� ������ ������
			sf::FloatRect bounds = tempText.getLocalBounds();

			// ���������� ������ ������ �� ��� X
			float centeredX = (windowWidth - bounds.width) /2;
			tempText.setPosition(centeredX, yPosition);

			// ������ ������ ������ ��������
			window.draw(tempText);

			// ������� ������� Y ��� ��������� ������
			yPosition += bounds.height + 10;  // 10 � ������ ����� ��������
		}
	}

	// ������� ������ �������� '\n' �� ����� "[NEWLINE]" ��� ������������
	std::string ReplaceNewlines(const std::string& input) {
		std::string result = input;
		size_t pos = 0;
		while ((pos = result.find('\n', pos)) != std::string::npos) {
			result.replace(pos, 1, "[NEWLINE]");
			pos += 9; // ����� "[NEWLINE]"
		}
		return result;
	}

}