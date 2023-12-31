/**
 * @file Menu.cpp
 * @brief The main menu of the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#include "Menu.hpp"

#include <SDL2/SDL.h>

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::handleInput()
{
}

void Menu::update()
{
}

void Menu::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderClear(renderer);
}
