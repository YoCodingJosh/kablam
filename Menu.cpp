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
}

Menu::~Menu()
{
	// free the textures
	SDL_DestroyTexture(titleTextTexture);
	SDL_DestroyTexture(copyrightTextTexture);
	SDL_DestroyTexture(wallTexture);
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

	if (!this->wallTexture)
	{
		// get the wall texture
		SDL_Texture* wallPiece = Assets::getTexture(BRICK_WALL);

		int wallPieceWidth = 0;
		int wallPieceHeight = 0;

		// get the width and height of the wall piece
		SDL_QueryTexture(wallPiece, NULL, NULL, &wallPieceWidth, &wallPieceHeight);

		int skyboxHeight = titleTextHeight + 75;

		// tile the wall piece across the screen to create a wall
		for (int x = 0; x < SCREEN_WIDTH; x += wallPieceWidth)
		{
			for (int y = skyboxHeight; y < SCREEN_HEIGHT; y += wallPieceHeight)
			{
				SDL_Rect destRect = { x, y, wallPieceWidth, wallPieceHeight };
				SDL_RenderCopy(renderer, wallPiece, NULL, &destRect);
			}
		}
	}

	// create the destination rectangle
	SDL_Rect titleDestRect = { 10, 5, this->titleTextWidth, this->titleTextHeight };
	SDL_Rect copyrightDestRect = { SCREEN_WIDTH - this->copyrightTextWidth - 10, 5, this->copyrightTextWidth, this->copyrightTextHeight };
	SDL_Rect wallDestRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// draw the textures
	SDL_RenderCopy(renderer, this->titleTextTexture, NULL, &titleDestRect);
	SDL_RenderCopy(renderer, this->copyrightTextTexture, NULL, &copyrightDestRect);
	SDL_RenderCopy(renderer, this->wallTexture, NULL, &wallDestRect);
}
