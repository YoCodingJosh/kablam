/**
 * @file PauseScreen.cpp
 * @brief Displays when the player pauses the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#include "PauseScreen.hpp"

#include "Constants.hpp"
#include "Assets.hpp"
#include "Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>

PauseScreen::PauseScreen()
	: textWidth(0), textHeight(0), time(0.0), textTexture(nullptr)
{
	auto textSurface = TTF_RenderText_Blended(Assets::getDefaultFont(), PAUSED_SCREEN_TEXT, { 255, 255, 255 });

	if (!textSurface)
	{
		SDL_Log("Failed to create text surface: %s", SDL_GetError());
		return;
	}

	this->textTexture = SDL_CreateTextureFromSurface(Game::get()->getRenderer(), textSurface);

	if (!this->textTexture)
	{
		SDL_Log("Failed to create text texture: %s", SDL_GetError());
		return;
	}

	SDL_QueryTexture(this->textTexture, nullptr, nullptr, &this->textWidth, &this->textHeight);

	SDL_FreeSurface(textSurface);
}

PauseScreen::~PauseScreen()
{
	if (this->textTexture)
	{
		SDL_DestroyTexture(this->textTexture);
		this->textTexture = nullptr;
	}
}

void PauseScreen::update(double deltaTime)
{
	this->time += deltaTime * 10;
}

void PauseScreen::handleEvent(const SDL_Event& event)
{
	// stub
}

void PauseScreen::render(SDL_Renderer* renderer)
{
	// render a semi-transparent black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderFillRect(renderer, nullptr);

    SDL_SetTextureColorMod(this->textTexture, 255, 255, 255);

    // Calculate the position to center the text horizontally
    int xPos = (SCREEN_WIDTH - textWidth) / 2;
    int yPos = (SCREEN_HEIGHT - textHeight) / 2;

    // TODO: Handle non-monospaced fonts

    // Render each character with an individual vertical offset
    for (size_t i = 0; i < PAUSED_SCREEN_TEXT_LENGTH; ++i)
    {
        // Calculate the vertical offset based on the sine wave
        int yOffset = static_cast<int>(this->amplitude * sin(2.0 * M_PI * this->frequency * (this->time + i)));

        // Get the character width
        int characterWidth = 0;
        TTF_SizeUTF8(Assets::getMenuFont(), &PAUSED_SCREEN_TEXT[i], &characterWidth, nullptr);

        // Calculate the position of the character
        int charXPos = xPos + (textWidth / PAUSED_SCREEN_TEXT_LENGTH - characterWidth) / 2 + i * textWidth / PAUSED_SCREEN_TEXT_LENGTH;
        int charYPos = yPos + yOffset;

        // Render the character at the calculated position
        SDL_Rect srcRect = { static_cast<int>(i * textWidth / PAUSED_SCREEN_TEXT_LENGTH), 0, static_cast<int>(textWidth / PAUSED_SCREEN_TEXT_LENGTH), textHeight };
        SDL_Rect dstRect = { charXPos, charYPos, static_cast<int>(textWidth / PAUSED_SCREEN_TEXT_LENGTH), textHeight };
        SDL_RenderCopy(renderer, textTexture, &srcRect, &dstRect);
    }
}
