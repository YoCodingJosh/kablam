/**
 * @file Init.cpp
 * @brief Handles the initialization of the application and it's subsystems.
 * @author Josh Kennedy
 * 
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#include "Init.hpp"

#include <iostream>

#include <SDL2/SDL.h>

bool hypeInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Failed to initialize SDL! SDL says: " << SDL_GetError() << "\n";

		return false;
	}

	return true;
}

void hypeShutdown()
{
	SDL_Quit();
}
