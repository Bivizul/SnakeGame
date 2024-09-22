#pragma once
#include "Apple.h"
#include "GameSettings.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	/*enum class GameOptions : std::uint8_t
	{
		VeryEasy = 1 << 0,
		Easy = 1 << 1,
		Normal = 1 << 2,
		Hard = 1 << 3,
		VeryHard = 1 << 4,

		Default = Normal,
		Empty = 0
	};*/

	enum class GameOptions 
	{
		VeryEasy = 0,
		Easy,
		Normal,
		Hard,
		VeryHard
	};

	enum class GameSettings : std::uint8_t
	{
		SoundEnabled = 1 << 0,
		MusicEnabled = 1 << 1,

		Default = SoundEnabled | MusicEnabled,
		Empty = 0
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	struct Game
	{
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::VeryEasy;
		GameSettings settings = GameSettings::Default;
		ProfileItem recordsTable[MAX_RECORDS_TABLE_SIZE];
		ProfileItem profile;
	};


	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game, float timeDelta);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	// Add new game state on top of the stack
	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);

	// Remove current game state from the stack
	void PopGameState(Game& game);

	// Remove all game states from the stack and add new one
	void SwitchGameState(Game& game, GameStateType newState);

	void InitGameState(Game& game, GameState& state);
	void ShutdownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state, float timeDelta);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);
}