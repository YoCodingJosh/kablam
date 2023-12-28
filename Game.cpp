/**
 * @file Game.cpp
 * @brief Manages the game loop and the game state.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#include "Game.hpp"

#include <iostream>

#include <SDL2/SDL.h>

Game* Game::__instance = nullptr;

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;
}

int Game::init()
{
	this->window = SDL_CreateWindow("Kablam!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_SHOWN);

	if (this->window == nullptr)
	{
		std::cerr << "Failed to create the window! SDL says: " << SDL_GetError() << "\n";

		return -2;
	}

	auto renderFlags = SDL_RendererFlags::SDL_RENDERER_ACCELERATED | SDL_RendererFlags::SDL_RENDERER_TARGETTEXTURE;

#if __EMSCRIPTEN__
	renderFlags |= SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC;
#endif

	this->renderer = SDL_CreateRenderer(this->window, -1, renderFlags);

	if (this->renderer == nullptr)
	{
		std::cerr << "Failed to create the renderer! SDL says: " << SDL_GetError() << "\n";

		return -3;
	}

	return 0;
}

void Game::quit()
{
	if (this->renderer != nullptr)
	{
		SDL_DestroyRenderer(this->renderer);
	}

	if (this->window != nullptr)
	{
		SDL_DestroyWindow(this->window);
	}
}

int Game::run()
{
	auto exitCode = this->init();

	if (exitCode != 0)
	{
		this->quit();
		return exitCode;
	}

	this->isRunning = true;

#if __EMSCRIPTEN__
	emscripten_set_main_loop(Game::thunk, 0, 1);
#else
	while (this->isRunning)
	{
		Game::thunk();
	}
#endif

	this->quit();

	return 0;
}

inline void Game::thunk()
{
	this->handleInput();
	this->update();
	this->render();
}

inline void Game::handleInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			this->isRunning = false;
			break;
		}
	}
}

inline void Game::update()
{

}

inline void Game::render()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);

	SDL_RenderPresent(this->renderer);
}
