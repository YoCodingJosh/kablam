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
union SDL_Event;

class Gameplay
{
private:
	SDL_Texture* badGuyTexture;
	SDL_Texture* wallTexture;
public:
	Gameplay();
	~Gameplay();

	void handleInput(SDL_Event& e);
	void update(double deltaTime);
	void render(SDL_Renderer* renderer);
};
