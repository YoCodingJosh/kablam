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

#include "Animation.hpp"
#include "Constants.hpp"

class Bomb
{
private:
	float x;
	float y;
	float velocity;
	bool active;
	Animation animation;
public:
	Bomb(float x, float y, float velocity = BOMB_FALL_SPEED);

	void update(double deltaTime);
	void render(SDL_Renderer* renderer);

	inline bool isActive() const { return active; }
	inline void setActive(bool active) { this->active = active; }

	inline float getX() const { return x; }
	inline float getY() const { return y; }
};
