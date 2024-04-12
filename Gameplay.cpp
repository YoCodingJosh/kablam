/**
 * @file Gameplay.cpp
 * @brief Contains the gameplay logic and rendering for the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#include "Gameplay.hpp"

#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "Assets.hpp"
#include "Constants.hpp"
#include "Timer.hpp"
#include "Utility.hpp"

Gameplay::Gameplay()
{
	this->badGuyTexture = nullptr;
	this->wallTexture = nullptr;

	this->wallTexture = Assets::getTexture(BRICK_WALL);

	if (!this->wallTexture)
	{
		SDL_Log("Failed to get wall texture: %s", SDL_GetError());
		return;
	}

	srand(time(nullptr));

	this->score = 0;
	this->badGuyPosition = SCREEN_WIDTH / 2 - 50;
	this->newBadGuyPosition = this->badGuyPosition;

	this->badGuyPositionTimer = new Timer(1250);
	this->badGuyPositionTimer->setLoop(true);
	this->badGuyPositionTimer->setTimeUpCallback([this]() {
		// move the bad guy to a random position on the screen
		// between BAD_GUY_MIN_X_POS and BAD_GUY_MAX_X_POS
		this->newBadGuyPosition = rand() % (BAD_GUY_MAX_X_POS - BAD_GUY_MIN_X_POS) + BAD_GUY_MIN_X_POS;
	});
	this->badGuyPositionTimer->start();
}

Gameplay::~Gameplay()
{
	if (this->badGuyTexture)
	{
		SDL_DestroyTexture(this->badGuyTexture);
		this->badGuyTexture = nullptr;
	}

	if (this->badGuyPositionTimer)
	{
		delete this->badGuyPositionTimer;
		this->badGuyPositionTimer = nullptr;
	}

	// We don't need to destroy the wall texture because it is managed by the Assets class.
}

void Gameplay::handleInput(SDL_Event& e)
{
	// Handle input here.
}

void Gameplay::update(double deltaTime)
{
	// Update the game logic here.
	this->badGuyPositionTimer->tick();

	// lerp the bad guy to the new position
	this->badGuyPosition = lerp(this->badGuyPosition, this->newBadGuyPosition, deltaTime * 10);

	// check if the bad guy is close to the new position
	if (abs(this->badGuyPosition - this->newBadGuyPosition) < 1)
	{
		this->badGuyPosition = this->newBadGuyPosition;
	}
}

void Gameplay::render(SDL_Renderer* renderer)
{
	if (this->wallTexture)
	{
		SDL_Rect wallRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		SDL_RenderCopy(renderer, this->wallTexture, nullptr, &wallRect);
	}

	if (!this->badGuyTexture)
	{
		// just create a black square for the bad guy at 100x100
		SDL_Surface* badGuySurface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
		SDL_FillRect(badGuySurface, nullptr, SDL_MapRGB(badGuySurface->format, 0, 0, 0));
		this->badGuyTexture = SDL_CreateTextureFromSurface(renderer, badGuySurface);

		if (!this->badGuyTexture)
		{
			SDL_Log("Failed to create bad guy texture: %s", SDL_GetError());
			return;
		}
	}

	// put the bad guy in the middle of the screen at SKYBOX_HEIGHT
	SDL_Rect badGuyRect = { badGuyPosition, SKYBOX_HEIGHT - 100, 100, 100 };

	SDL_RenderCopy(renderer, this->badGuyTexture, nullptr, &badGuyRect);
}
