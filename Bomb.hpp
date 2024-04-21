/**
 * @file Bomb.hpp
 * @brief explosive device
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

struct SDL_Renderer;

class Bomb
{
private:
	float x;
	float y;
	float velocity;
public:
	Bomb();
	~Bomb();

	void update(double deltaTime);
	void render(SDL_Renderer* renderer);
};
