#pragma once
#include <string>

namespace SnakeGame
{
	const std::string RESOURCES_PATH = "Resources/";

	const float PLAYER_SIZE = 40.f;
	const float APPLE_SIZE = 40.f;
	const float WALL_SIZE = 40.f;
	const float CUP_SIZE = 40.f;

	const float INITIAL_SPEED_VERY_EASY = 0.16f;
	const float INITIAL_SPEED_EASY = 0.14f;
	const float INITIAL_SPEED_NORMAL = 0.12f;
	const float INITIAL_SPEED_HARD = 0.1f;
	const float INITIAL_SPEED_VERY_HARD = 0.08f;

	const int MIN_APPLES = 1;
	const int MAX_APPLES = 3;
	const int MIN_walls = 5;
	const int MAX_walls = 20;

	const unsigned int SCREEN_WIDTH = 1280;
	const unsigned int SCREEN_HEIGHT = 720;
	const unsigned int INFO_HEIGHT = 80;    

	const unsigned int PLAYING_FIELD_WIDTH = unsigned(SCREEN_WIDTH - (WALL_SIZE * 2));
	const unsigned int PLAYING_FIELD_HEIGHT = unsigned(SCREEN_HEIGHT - (WALL_SIZE * 2) - INFO_HEIGHT);

	const unsigned int APPLES_GRID_CELLS_HORIZONTAL = unsigned(SCREEN_WIDTH / (APPLE_SIZE * 4));
	const unsigned int APPLES_GRID_CELLS_VERTICAL = unsigned(SCREEN_HEIGHT / (APPLE_SIZE * 4));
	const unsigned int MAX_APPLES_IN_CELL = MAX_APPLES;

	const int MAX_RECORDS_TABLE_SIZE = 10;

	const std::string PROFILE_NAME_DEFAULT = "XYZ";

	const std::string TABLE_RECORDS_NAME_FILE = "TableRecords.txt";
}