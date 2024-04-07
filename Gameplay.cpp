/**
 * @file Gameplay.cpp
 * @brief Contains the gameplay logic and rendering for the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#include "Gameplay.hpp"

#include <SDL2/SDL.h>

#include "Assets.hpp"
#include "Constants.hpp"

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
}

Gameplay::~Gameplay()
{
	if (this->badGuyTexture)
	{
		SDL_DestroyTexture(this->badGuyTexture);
		this->badGuyTexture = nullptr;
	}

	// We don't need to destroy the wall texture because it is managed by the Assets class.
}