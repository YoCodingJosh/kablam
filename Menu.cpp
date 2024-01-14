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
#include <SDL2/SDL_ttf.h>

#include "Assets.hpp"

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

	// get the font
	TTF_Font* font = Assets::getDefaultFont();

	// create the text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Kablam!", { 255, 255, 255, 255 });

	// create the texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	// get the width and height of the texture
	int width = 0;
	int height = 0;
	SDL_QueryTexture(textTexture, NULL, NULL, &width, &height);

	// create the destination rectangle
	SDL_Rect destRect = { 0, 0, width, height };

	// draw the texture
	SDL_RenderCopy(renderer, textTexture, NULL, &destRect);

	// free the surface
	SDL_FreeSurface(textSurface);

	// free the texture
	SDL_DestroyTexture(textTexture);

	// present the renderer
	SDL_RenderPresent(renderer);
}
