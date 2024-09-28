#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
//#pragma execution_character_set("utf-8")

using namespace SnakeGame;

static void AttachConsole()
{
	if (AllocConsole())
	{
		FILE* newStdout;
		FILE* newStderr;
		FILE* newStdin;

		// Redirect stdout to console
		freopen_s(&newStdout, "CONOUT$", "w", stdout);
		// Redirect stderr to console
		freopen_s(&newStderr, "CONOUT$", "w", stderr);
		// Redirect stdin to console
		freopen_s(&newStdin, "CONIN$", "r", stdin);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	//std::setlocale(LC_ALL, "ru_RU.UTF-8");	// попытки включить русский язык для форматированных кнопок
	//SetConsoleOutputCP(CP_UTF8);
	//SetConsoleOutputCP(1251);

	AttachConsole();

	unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SnakeGame::SCREEN_WIDTH, SnakeGame::SCREEN_HEIGHT), "Snake Game");

	// We now use too much memory for stack, so we need to allocate it on heap
	SnakeGame::Game* game = new SnakeGame::Game();
	InitGame(*game);

	sf::Clock game_clock;
	sf::Time lastTime = game_clock.getElapsedTime();

	std::cout << " Русский язык " << std::endl;

	while (window.isOpen())
	{
		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		sf::Time currentTime = game_clock.getElapsedTime();
		float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
		lastTime = currentTime;
		if (UpdateGame(*game, timeDelta))
		{
			window.clear();

			DrawGame(*game, window);

			window.display();
		}
		else
		{
			window.close();
		}
	}

	ShutdownGame(*game);
	delete game;
	game = nullptr;

	return 0;
}