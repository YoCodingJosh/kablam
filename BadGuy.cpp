/**
 * @file BadGuy.cpp
 * @brief the guy who's bad, like really bad
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#include "BadGuy.hpp"

#include "Timer.hpp"
#include "Constants.hpp"

#include <SDL2/SDL.h>

#include <random>

BadGuy::BadGuy() :
	movementTimer(nullptr),
	bombTimer(nullptr),
	position(SCREEN_WIDTH / 2 - BAD_GUY_SPRITE_WIDTH / 2),
	velocity(0),
	velocityMultiplier(1),
	shouldDropBomb(false),
	isPaused(false),
	bombDropCallback(nullptr),
	currentLevel(0)
{
	movementTimer = new Timer(1250);
	movementTimer->setLoop(true);

	bombTimer = new Timer(500);
	bombTimer->setLoop(true);
}

BadGuy::~BadGuy()
{
	if (movementTimer != nullptr)
	{
		delete movementTimer;

		movementTimer = nullptr;
	}

	if (bombTimer != nullptr)
	{
		delete bombTimer;

		bombTimer = nullptr;
	}
}

void BadGuy::start(int level)
{
	currentLevel = level;

	// TODO: Implement this

	velocity = 0;
	velocityMultiplier = 1;

	/*movementTimer->setInterval(1000 - (level * 100));
	bombTimer->setInterval(2000 - (level * 200));*/

	movementTimer->start();
	bombTimer->start();
}

void BadGuy::update(double delta)
{
	if (isPaused)
	{
		return;
	}

	movementTimer->tick();
	bombTimer->tick();
}

void BadGuy::render(SDL_Renderer* renderer)
{

}
