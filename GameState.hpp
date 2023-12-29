/**
 * @file GameState.hpp
 * @brief the game state enum class
 * @author Josh Kennedy
 * 
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#pragma once

enum class GameState : unsigned char
{
	/// <summary>
	/// The state of game initialization.
	/// </summary>
	INIT = 0,

	/// <summary>
	/// At the main menu.
	/// </summary>
	MENU,

	/// <summary>
	/// The state of the game playing.
	/// </summary>
	GAMEPLAY,

	/// <summary>
	/// Paused game.
	/// </summary>
	PAUSE,

	/// <summary>
	/// The state of the game over screen.
	/// </summary>
	GAME_OVER,

	/// <summary>
	/// The state of the game quitting and deinitialization.
	/// </summary>
	QUIT,
};
