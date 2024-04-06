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
#include "Constants.hpp"

Menu::Menu()
{
	// initialize the textures
	this->titleTextTexture = nullptr;
	this->copyrightTextTexture = nullptr;
	this->wallTexture = nullptr;

	// initialize the widths and heights
	this->titleTextWidth = 0;
	this->titleTextHeight = 0;
	this->copyrightTextWidth = 0;
	this->copyrightTextHeight = 0;

	// get the wall texture
	this->wallTexture = Assets::getTexture(BRICK_WALL);

	if (!this->wallTexture)
	{
		SDL_Log("Failed to get wall texture: %s", SDL_GetError());
		return;
	}
}

Menu::~Menu()
{
	// free the textures
	if (this->titleTextTexture)
	{
		SDL_DestroyTexture(titleTextTexture);

		this->titleTextTexture = nullptr;
	}

	if (this->copyrightTextTexture)
	{
		SDL_DestroyTexture(copyrightTextTexture);

		this->copyrightTextTexture = nullptr;
	}

	// don't free the wall texture, it's a shared resource
}

void Menu::handleInput()
{

}

void Menu::update()
{
}

void Menu::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
	SDL_RenderClear(renderer);

	if (!this->titleTextTexture)
	{
		// get the font
		TTF_Font* font = Assets::getDefaultFont();

		// create the text surface
		SDL_Surface* titleTextSurface = TTF_RenderText_Blended(font, GAME_TITLE, { 255, 255, 255, 255 });

		// create the texture
		this->titleTextTexture = SDL_CreateTextureFromSurface(renderer, titleTextSurface);

		// free the surface
		SDL_FreeSurface(titleTextSurface);

		// get the width and height of the texture
		SDL_QueryTexture(this->titleTextTexture, NULL, NULL, &this->titleTextWidth, &this->titleTextHeight);
	}

	if (!this->titleTextTexture)
	{
		SDL_Log("Failed to create title text texture: %s", SDL_GetError());
		return;
	}

	if (!this->copyrightTextTexture)
	{
		// get the font
		TTF_Font* font = Assets::getDefaultFont();

		// create the text surface
		SDL_Surface* copyrightTextSurface = TTF_RenderText_Blended(font, GAME_COPYRIGHT, { 255, 255, 255, 255 });

		// create the texture
		this->copyrightTextTexture = SDL_CreateTextureFromSurface(renderer, copyrightTextSurface);

		// free the surface
		SDL_FreeSurface(copyrightTextSurface);

		// get the width and height of the texture
		SDL_QueryTexture(this->copyrightTextTexture, NULL, NULL, &this->copyrightTextWidth, &this->copyrightTextHeight);
	}

	if (!this->titleTextTexture)
	{
		SDL_Log("Failed to create copyright text texture: %s", SDL_GetError());
		return;
	}

	// create the destination rectangle
	SDL_Rect titleDestRect = { 10, 5, this->titleTextWidth, this->titleTextHeight };
	SDL_Rect copyrightDestRect = { SCREEN_WIDTH - this->copyrightTextWidth - 10, 5, this->copyrightTextWidth, this->copyrightTextHeight };
	SDL_Rect wallDestRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// draw the textures
	SDL_RenderCopy(renderer, this->wallTexture, NULL, &wallDestRect);
	SDL_RenderCopy(renderer, this->titleTextTexture, NULL, &titleDestRect);
	SDL_RenderCopy(renderer, this->copyrightTextTexture, NULL, &copyrightDestRect);
}
