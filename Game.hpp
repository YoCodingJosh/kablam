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

#include "Constants.hpp"

#include "Menu.hpp"
#include "Gameplay.hpp"

#include "Assets.hpp"

#include <chrono>

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

class Game
{
	friend class Assets;
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
	void update(double deltaTime);
	void render();

	Menu* menu;
	Gameplay* gameplay;

	bool __isTouchAvailable;

	std::chrono::high_resolution_clock::time_point timePrev;

	inline double calculateDeltaTime() noexcept
	{
		// Get current time as a std::chrono::time_point
		// which basically contains info about the current point in time.
		auto timeCurrent = std::chrono::high_resolution_clock::now();

		// Compare the two to create time_point containing delta time in nanoseconds.
		auto timeDiff = std::chrono::duration_cast<std::chrono::nanoseconds>(timeCurrent - timePrev);

		// Get the ticks as a variable.
		double delta = static_cast<double>(timeDiff.count());

		// Turn nanoseconds into seconds.
		delta /= 1'000'000'000.00;

		// Swap the times.
		this->timePrev = timeCurrent;

		// Clamp the delta
		if (delta > TARGET_FRAME_TIME)
		{
			delta = TARGET_FRAME_TIME;
		}

		return delta;
	}

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
	inline void setState(GameState state) noexcept { this->currentState = state; }

	inline bool isTouchAvailable() const noexcept { return this->__isTouchAvailable; }
};
