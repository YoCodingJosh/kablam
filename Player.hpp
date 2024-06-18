/**
 * @file Player.hpp
 * @brief The player duh
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

struct SDL_Renderer;
struct SDL_Texture;
union SDL_Event;

class Player
{
private:
	int lives;
	int y;

public:
	Player();

	void update(double deltaTime);
	void handleInput(SDL_Event& e);
	void render(SDL_Renderer* renderer);
};
