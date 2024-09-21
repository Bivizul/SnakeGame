#include "Button.h"
#include "Math.h"
#include <cassert>
#include <iostream>

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
		// It is definitely error to select root item
		assert(item != &buttonNav.rootButtons);

		if (buttonNav.selectedButton == item)
		{
			return;
		}

		if (item && !item->isEnabled)
		{
			// Don't allow to select disabled item
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
			assert(parent); // There always should be parent

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
			assert(parent); // There always should be parent
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