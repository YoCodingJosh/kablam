/**
 * @file Gameplay.hpp
 * @brief Contains the gameplay logic and rendering for the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

struct SDL_Renderer;
struct SDL_Texture;

class Gameplay
{
private:
	SDL_Texture* badGuyTexture;
	SDL_Texture* wallTexture;
public:
	Gameplay();
	~Gameplay();

	void handleInput();
	void update();
	void render(SDL_Renderer* renderer);
};
