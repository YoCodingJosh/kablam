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

	// initialize the widths and heights
	this->titleTextWidth = 0;
	this->titleTextHeight = 0;
	this->copyrightTextWidth = 0;
	this->copyrightTextHeight = 0;
}

Menu::~Menu()
{
	// free the texture
	SDL_DestroyTexture(titleTextTexture);
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

		// get the width and height of the texture`
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

		// get the width and height of the texture`
		SDL_QueryTexture(this->copyrightTextTexture, NULL, NULL, &this->copyrightTextWidth, &this->copyrightTextHeight);
	}

	if (!this->titleTextTexture)
	{
		SDL_Log("Failed to create copyright text texture: %s", SDL_GetError());
		return;
	}

	// create the destination rectangle
	SDL_Rect titleDestRect = { 0, 0, this->titleTextWidth, this->titleTextHeight };
	SDL_Rect copyrightDestRect = { 0, SCREEN_HEIGHT - this->copyrightTextHeight, this->copyrightTextWidth, this->copyrightTextHeight };


	// draw the textures
	SDL_RenderCopy(renderer, this->titleTextTexture, NULL, &titleDestRect);
	SDL_RenderCopy(renderer, this->copyrightTextTexture, NULL, &copyrightDestRect);

	// present the renderer
	SDL_RenderPresent(renderer);
}
