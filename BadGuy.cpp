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
#include "Utility.hpp"

#include <SDL2/SDL.h>

#include <random>

BadGuy::BadGuy() :
	movementTimer(nullptr),
	bombTimer(nullptr),
	position(SCREEN_WIDTH / 2 - BAD_GUY_SPRITE_WIDTH / 2),
	newPosition(position),
	velocity(0),
	velocityMultiplier(1),
	shouldDropBomb(false),
	isPaused(false),
	bombDropCallback(nullptr),
	currentLevel(0),
	texture(nullptr)
{
	// nothing to do here
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

	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);

		texture = nullptr;
	}
}

void BadGuy::start(int level)
{
	currentLevel = level;

	// TODO: Implement this

	velocity = 0;
	velocityMultiplier = 1;

	movementTimer = new Timer(1500); // arbitrary value for now
	movementTimer->setLoop(true);

	this->movementTimer->setTimeUpCallback([this]() {
		// move the bad guy to a random position on the screen
		// between BAD_GUY_MIN_X_POS and BAD_GUY_MAX_X_POS
		this->newPosition = rand() % (BAD_GUY_MAX_X_POS - BAD_GUY_MIN_X_POS) + BAD_GUY_MIN_X_POS;
	});

	bombTimer = new Timer(1000); // arbitrary value for now
	bombTimer->setLoop(true);
	bombTimer->setTimeUpCallback([this]() {
		// drop a bomb
		this->shouldDropBomb = true;

		if (this->bombDropCallback)
		{
			this->bombDropCallback(this->getX(), this->getY());
		}

		// reset the flag
		this->shouldDropBomb = false;
	});

	movementTimer->start();
	bombTimer->start();
}

void BadGuy::stop()
{
	movementTimer->stop();
	bombTimer->stop();

	// TODO: should we delete the timers here?
}

void BadGuy::update(double delta)
{
	if (isPaused)
	{
		return;
	}

	movementTimer->tick();
	bombTimer->tick();

	// lerp the bad guy to the new position
	this->position = lerp(this->position, this->newPosition, delta * BAD_GUY_SPEED);

	// check if the bad guy is close to the new position
	if (abs(this->position - this->newPosition) < 1)
	{
		this->position = this->newPosition;
	}
}

void BadGuy::render(SDL_Renderer* renderer)
{
	if (!this->texture)
	{
		// just create a black square for the bad guy at 100x100
		SDL_Surface* badGuySurface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
		SDL_FillRect(badGuySurface, nullptr, SDL_MapRGB(badGuySurface->format, 0, 0, 0));
		this->texture = SDL_CreateTextureFromSurface(renderer, badGuySurface);

		if (!this->texture)
		{
			SDL_Log("Failed to create bad guy texture: %s", SDL_GetError());
			return;
		}
	}

	SDL_Rect badGuyRect = { static_cast<int>(this->position), BAD_GUY_Y_POS, BAD_GUY_SPRITE_WIDTH, BAD_GUY_SPRITE_HEIGHT};

	SDL_RenderCopy(renderer, this->texture, nullptr, &badGuyRect);
}
