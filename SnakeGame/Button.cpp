#include "Button.h"
#include "Math.h"
#include <cassert>

namespace SnakeGame
{
	void InitButtonItem(ButtonItem& button)
	{
		for (auto& child : button.children)
		{
			child->parent = &button;
			InitButtonItem(*child);
		}
	}

	void SelectButtonNavItem(ButtonNav& buttonNav, ButtonItem* item)
	{
		assert(item != &buttonNav.rootButtons);

		if (buttonNav.selectedButton == item)
		{
			return;
		}

		if (item && !item->isEnabled)
		{
			return;
		}

		if (buttonNav.selectedButton)
		{
			buttonNav.selectedButton->shape.setOutlineColor(buttonNav.selectedButton->deselectedColor);
		}

		buttonNav.selectedButton = item;

		if (buttonNav.selectedButton)
		{
			buttonNav.selectedButton->shape.setOutlineColor(buttonNav.selectedButton->selectedColor);
		}
	}

	bool SelectPreviousButtonNavItem(ButtonNav& buttonNav)
	{
		if (buttonNav.selectedButton)
		{
			ButtonItem* parent = buttonNav.selectedButton->parent;
			assert(parent);

			auto it = std::find(parent->children.begin(), parent->children.end(), buttonNav.selectedButton);
			if (it != parent->children.begin())
			{
				SelectButtonNavItem(buttonNav, *(--it));
				return true;
			}
		}

		return false;
	}

	bool SelectNextButtonNavItem(ButtonNav& buttonNav)
	{
		if (buttonNav.selectedButton)
		{
			ButtonItem* parent = buttonNav.selectedButton->parent;
			assert(parent);
			auto it = std::find(parent->children.begin(), parent->children.end(), buttonNav.selectedButton);
			if (it != parent->children.end() - 1)
			{
				SelectButtonNavItem(buttonNav, *(++it));
				return true;
			}
		}
		return false;
	}

	void DrawButton(ButtonItem& button, float x, float y, sf::RenderWindow& window)
	{
		button.shape.setPosition(x, y);
		window.draw(button.shape);

		button.text.setPosition(x, y);
		CenterText(button.text, window);
	}
}