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

#include "FPSLimiter.hpp"

Game* Game::__instance = nullptr;

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->isRunning = false;
	this->currentState = GameState::INIT;
	this->menu = nullptr;
}

int Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Failed to initialize SDL! SDL says: " << SDL_GetError() << "\n";

		return -1;
	}

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

	SDL_Quit();
}

int Game::run()
{
	if (this->isRunning)
	{
		return 69;
	}

	auto exitCode = this->init();

	if (exitCode != 0)
	{
		this->quit();
		return exitCode;
	}

	this->isRunning = true;

#if __EMSCRIPTEN__
	emscripten_set_main_loop([this]() { this->thunk(); }, 0, 1);
#else
	FPSLimiter limiter(60); // TODO: automatically detect the refresh rate of the monitor.
	while (this->isRunning)
	{
		this->thunk();

		limiter.run();
	}
#endif

	this->quit();

	return 0;
}

inline void Game::thunk()
{
	if (!this->isRunning)
	{
#ifdef __EMSCRIPTEN__
		emscripten_cancel_main_loop();
#endif
		return;
}

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

		switch (this->currentState)
		{
		case GameState::INIT:
			break;
		case GameState::MENU:
			if (this->menu != nullptr)
			{
				this->menu->handleInput();
			}
			break;
		}
	}
}

inline void Game::update()
{
	switch (this->currentState)
	{
	case GameState::INIT:
		this->currentState = GameState::MENU;
		break;
	case GameState::MENU:
		if (this->menu == nullptr)
		{
			this->menu = new Menu();
		}

		this->menu->update();
		break;
	}
}

inline void Game::render()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);

	switch (this->currentState)
	{
	case GameState::INIT:
		break;
	case GameState::MENU:
		if (this->menu != nullptr)
		{
			this->menu->render(this->renderer);
		}
		break;
	}

	SDL_RenderPresent(this->renderer);
}
