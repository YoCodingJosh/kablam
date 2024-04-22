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
#include <math.h>

#include <SDL2/SDL.h>

#include "Assets.hpp"
#include "Constants.hpp"
#include "Timer.hpp"
#include "Utility.hpp"

Gameplay::Gameplay()
	: wallTexture(nullptr)
	, score(0)
	, badGuy(nullptr)
{
	this->wallTexture = nullptr;

	this->wallTexture = Assets::getTexture(BRICK_WALL);

	if (!this->wallTexture)
	{
		SDL_Log("Failed to get wall texture: %s", SDL_GetError());
		return;
	}

	srand(time(nullptr));

	this->score = 0;

	this->badGuy = new BadGuy();

	this->badGuy->registerBombDropCallback([this](float x, float y) {
		this->dropBomb(x, y + BOMB_SPRITE_HEIGHT);
	});

	this->badGuy->start(1);
}

Gameplay::~Gameplay()
{
	if (this->badGuy)
	{
		delete this->badGuy;
		this->badGuy = nullptr;
	}

	for (auto bomb : this->bombs)
	{
		delete bomb;
	}

	// We don't need to destroy the wall texture because it is managed by the Assets class.
}

void Gameplay::dropBomb(float x, float y)
{
	// Create a new bomb.
	Bomb* bomb = new Bomb(x, y);

	this->bombs.push_back(bomb);
}

void Gameplay::handleInput(SDL_Event& e)
{
	// Handle input here.
}

void Gameplay::update(double deltaTime)
{
	if (this->badGuy)
	{
		this->badGuy->update(deltaTime);
	}

	for (auto it = this->bombs.begin(); it != this->bombs.end();)
	{
		Bomb* bomb = *it;

		bomb->update(deltaTime);

		if (!bomb->isActive())
		{
			delete bomb;
			it = this->bombs.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Gameplay::render(SDL_Renderer* renderer)
{
	if (this->wallTexture)
	{
		SDL_Rect wallRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		SDL_RenderCopy(renderer, this->wallTexture, nullptr, &wallRect);
	}

	if (this->badGuy)
	{
		this->badGuy->render(renderer);
	}

	for (auto bomb : this->bombs)
	{
		bomb->render(renderer);
	}
}
