/**
 * @file Menu.hpp
 * @brief The main menu of the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#pragma once

struct SDL_Renderer;
struct SDL_Texture;
union SDL_Event;

#include "Animation.hpp"

class Menu
{
private:
	SDL_Texture* titleTextTexture;
	int titleTextWidth;
	int titleTextHeight;

	SDL_Texture* copyrightTextTexture;
	int copyrightTextWidth;
	int copyrightTextHeight;

	SDL_Texture* wallTexture;

	SDL_Texture* promptTextTexture;
	int promptTextWidth;
	int promptTextHeight;
	double promptBlinkTime;
	bool blinkPrompt;
public:
	Menu();
	~Menu();

	void handleInput(SDL_Event& e);
	void update(double deltaTime);
	void render(SDL_Renderer* renderer);
};
