#pragma once
#include <string>

namespace SnakeGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	const float PLAYER_SIZE = 40.f;
	const float APPLE_SIZE = 40.f;
	const float WALL_SIZE = 40.f;

	const float INITIAL_SPEED = 0.2f;
	const float ACCELERATION = 0.f; // For each eaten apple player speed will be increased by this value

	const int MIN_APPLES = 1;
	const int MAX_APPLES = 2;
	const int MIN_walls = 5;
	const int MAX_walls = 20;

	const unsigned int SCREEN_WIDTH = 1600;
	const unsigned int SCREEN_HEIGHT = 1200;
	const unsigned int INFO_HEIGHT = 80;

	const unsigned int PLAYING_FIELD_WIDTH = unsigned(SCREEN_WIDTH - (WALL_SIZE * 2));
	const unsigned int PLAYING_FIELD_HEIGHT = unsigned(SCREEN_HEIGHT - (WALL_SIZE * 2) - INFO_HEIGHT);

	const unsigned int APPLES_GRID_CELLS_HORIZONTAL = unsigned(SCREEN_WIDTH / (APPLE_SIZE * 4));
	const unsigned int APPLES_GRID_CELLS_VERTICAL = unsigned(SCREEN_HEIGHT / (APPLE_SIZE * 4));
	//const unsigned int MAX_APPLES_IN_CELL = MAX_APPLES / 4; // We don't expect too much apples in one cell
	const unsigned int MAX_APPLES_IN_CELL = MAX_APPLES; // We don't expect too much apples in one cell

	const int MAX_RECORDS_TABLE_SIZE = 10;
}