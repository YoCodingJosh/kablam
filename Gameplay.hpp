/**
 * @file Gameplay.hpp
 * @brief Contains the gameplay logic and rendering for the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

#include "Timer.hpp"

#include "BadGuy.hpp"
#include "Bomb.hpp"
#include "PauseScreen.hpp"

#include <vector>

struct SDL_Renderer;
struct SDL_Texture;
union SDL_Event;

class Gameplay
{
private:
	bool isPaused;
	BadGuy* badGuy;
	SDL_Texture* wallTexture;
	unsigned int score;
	unsigned int highScore;
	std::vector<Bomb*> bombs;
	PauseScreen* pauseScreen;
	SDL_Texture* scoreTexture;
	SDL_Texture* highScoreTexture;
	bool needsToUpdateScoreTexture;
	int scoreTextureWidth;
	int scoreTextureHeight;
	int highScoreTextureWidth;
	int highScoreTextureHeight;
public:
	Gameplay();
	~Gameplay();

	void dropBomb(float x, float y);

	void handleInput(SDL_Event& e);
	void update(double deltaTime);
	void render(SDL_Renderer* renderer);
};
