/**
 * @file Game.hpp
 * @brief Manages the game loop and the game state.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#pragma once

#include "GameState.hpp"

#include "Menu.hpp"

struct SDL_Window;
struct SDL_Renderer;

class Game
{
private:
	static Game* __instance;
	Game();

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isRunning;

	GameState currentState;

	int init();
	void quit();

	void thunk();

	void handleInput();
	void update();
	void render();

	Menu* menu;

	bool __isTouchAvailable;

public:
	inline static Game* get()
	{
		if (__instance == nullptr)
		{
			__instance = new Game();
		}

		return __instance;
	}

	int run();

	inline GameState getState() const noexcept { return this->currentState; }

	inline bool isTouchAvailable() const noexcept { return this->__isTouchAvailable; }
};
