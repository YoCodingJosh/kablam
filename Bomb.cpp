/**
 * @file Bomb.cpp
 * @brief explosive device
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#include "Bomb.hpp"

#include "Assets.hpp"
#include "Constants.hpp"

#include <SDL2/SDL.h>

Bomb::Bomb(float x, float y, float velocity)
	: velocity(velocity), x(x), y(y)
{
	this->active = true;

	this->animation = Assets::getAnimation(BOMB);
	this->animation.setX(x);
	this->animation.setY(y);
	this->animation.play();
}

void Bomb::update(double deltaTime)
{
	if (this->active)
	{
		this->animation.update(deltaTime);

		this->y += this->velocity * deltaTime;

		// TODO: Do we really need to check this here?
		// Also, this should be if it goes past the player, not the screen
		if (this->y > SCREEN_HEIGHT)
		{
			this->active = false;
		}

		this->animation.setX(this->x); // TODO: do we really need to update the x position every frame?
		this->animation.setY(this->y);
	}
}

void Bomb::render(SDL_Renderer* renderer)
{
	if (this->active)
	{
		this->animation.render(renderer);
	}
}
