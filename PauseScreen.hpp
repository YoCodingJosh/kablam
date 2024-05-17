/**
 * @file PauseScreen.hpp
 * @brief Displays when the player pauses the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

#include <SDL2/SDL.h>

class PauseScreen
{
private:
	int textWidth;
	int textHeight;

	SDL_Texture* textTexture;
	SDL_Color textColor = { 255, 255, 255 };

	float amplitude = 20.0f;	// Controls the height of the bouncing effect
	float frequency = 0.05f;	// Controls the speed of the bouncing effect
	float time = 0.0f;			// Time elapsed

public:
	PauseScreen();
	~PauseScreen();

	void update(double deltaTime);
	void handleEvent(const SDL_Event& event);
	void render(SDL_Renderer* renderer);
};
