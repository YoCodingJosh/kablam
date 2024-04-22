/**
 * @file BadGuy.hpp
 * @brief the guy who's bad, like really bad
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

#include "Timer.hpp"

#include "Constants.hpp"

#include <functional>

struct SDL_Texture;
struct SDL_Renderer;

class BadGuy
{
private:
	bool isPaused; // is the bad guy paused?

	float position; // only position that matters is x, since he moves left to right
	float newPosition; // where he's moving to
	float velocity; // how fast he moves
	float velocityMultiplier; // sometimes he speeds up

	Timer* movementTimer; // how often he moves
	Timer* bombTimer; // how often he drops a bomb

	bool shouldDropBomb; // should he drop a bomb?
	std::function<void(float, float)> bombDropCallback; // callback for when he drops a bomb

	int currentLevel; // the current level the player is on

	// TODO: make this an animation and more than one kind of animation
	SDL_Texture* texture; // the bad guy's texture
public:
	BadGuy();
	~BadGuy();

	/**
	 * Register a callback to be called when the bad guy drops a bomb.
	 * @param callback The function to call when the bad guy drops a bomb.
	 * @note The callback should take two float parameters, the x and y position of the bomb.
	 */
	inline void registerBombDropCallback(std::function<void(float, float)> callback)
	{
		bombDropCallback = callback;
	}

	/**
	 * Start the bad guy at the specified level.
	 * @param level The level to start the bad guy at.
	 * @note The level is used to determine how fast the bad guy moves and how many and often he drops bombs.
	 */
	void start(int level);

	/**
	 * Stop the bad guy.
	 * 
	 * This should be called when the game is over.
	 */
	void stop();

	/**
	 * Stop the bad guy from moving.
	 * 
	 * This should be called when the game is paused.
	 */
	inline void pause()
	{
		isPaused = true;

		if (movementTimer)
		{
			movementTimer->pause();
		}

		if (bombTimer)
		{
			bombTimer->pause();
		}
	}

	/**
	 * Resume the bad guy's movement.
	 * 
	 * This should be called when the game is unpaused.
	 */
	inline void resume()
	{
		isPaused = false;

		if (movementTimer)
		{
			movementTimer->unpause();
		}

		if (bombTimer)
		{
			bombTimer->unpause();
		}
	}

	void update(double delta);
	void render(SDL_Renderer* renderer);

	inline float getX() const
	{
		return position;
	}

	inline float getY() const
	{
		return BAD_GUY_Y_POS;
	}
};
