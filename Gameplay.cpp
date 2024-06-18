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
	, isPaused(false)
	, pauseScreen(nullptr)
	, highScore(0)
	, scoreTexture(nullptr)
	, highScoreTexture(nullptr)
	, needsToUpdateScoreTexture(false)
	, scoreTextureWidth(0), scoreTextureHeight(0)
	, highScoreTextureWidth(0), highScoreTextureHeight(0)
{
	this->wallTexture = Assets::getTexture(BRICK_WALL);

	if (!this->wallTexture)
	{
		SDL_Log("Failed to get wall texture: %s", SDL_GetError());
		return;
	}

	srand(time(nullptr));

	this->pauseScreen = new PauseScreen();

	this->highScore = 0; // TODO: fetch

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

	this->bombs.clear();

	if (this->pauseScreen)
	{
		delete this->pauseScreen;
		this->pauseScreen = nullptr;
	}

	if (this->highScoreTexture)
	{
		SDL_DestroyTexture(this->highScoreTexture);
		this->highScoreTexture = nullptr;
	}

	if (this->scoreTexture)
	{
		SDL_DestroyTexture(this->scoreTexture);
		this->scoreTexture = nullptr;
	}

	// We don't need to destroy the wall texture because it is managed by the Assets class.
}

void Gameplay::dropBomb(float x, float y)
{
	Bomb* bomb = new Bomb(x, y);

	this->bombs.push_back(bomb);
}

void Gameplay::handleInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
	{
		this->isPaused = !this->isPaused;

		if (this->isPaused)
		{
			this->badGuy->pause();
		}
		else
		{
			this->badGuy->resume();
		}
	}

	if (this->isPaused)
	{
		this->pauseScreen->handleEvent(e);
	}
	else
	{
		// do something else
	}
}

void Gameplay::update(double deltaTime)
{
	if (this->isPaused)
	{
		this->pauseScreen->update(deltaTime);

		return;
	}

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

	if (!this->scoreTexture || this->needsToUpdateScoreTexture)
	{
		// get the font
		TTF_Font* font = Assets::getDefaultFont();

		std::string scoreText = SCORE_TEXT + std::to_string(this->score);

		// create the text surface
		SDL_Surface* scoreTextSurface = TTF_RenderText_Blended(font, scoreText.c_str(), {255, 255, 255, 255});

		// create the texture
		this->scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreTextSurface);

		// free the surface
		SDL_FreeSurface(scoreTextSurface);

		// get the width and height of the texture
		SDL_QueryTexture(this->scoreTexture, NULL, NULL, &this->scoreTextureWidth, &this->scoreTextureHeight);
	}

	SDL_Rect scoreTextRect = { 10, 5, this->scoreTextureWidth, this->scoreTextureHeight };

	SDL_RenderCopy(renderer, this->scoreTexture, NULL, &scoreTextRect);

	if (!this->highScoreTexture)
	{
	}

	// TODO: Render high score texture

	if (this->badGuy)
	{
		this->badGuy->render(renderer);
	}

	for (auto bomb : this->bombs)
	{
		bomb->render(renderer);
	}

	if (this->isPaused)
	{
		this->pauseScreen->render(renderer);
	}
}
