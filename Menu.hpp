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

class Menu
{
private:
public:
	Menu();
	~Menu();

	void handleInput();
	void update();
	void render(SDL_Renderer* renderer);
};