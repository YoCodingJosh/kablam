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
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "FPSLimiter.hpp"

#include "Assets.hpp"
#include "Constants.hpp"

#if __EMSCRIPTEN__
#include <emscripten.h>

void GameEmscriptenLoopThunk(void* game)
{
	static_cast<Game*>(game)->__loopThunk();
}
#endif

Game* Game::__instance = nullptr;

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->isRunning = false;
	this->currentState = GameState::INIT;
	this->menu = nullptr;
	this->__isTouchAvailable = false;
	this->gameplay = nullptr;
}

int Game::init()
{
	auto sdlInitFlags = SDL_INIT_EVERYTHING;

	#if __EMSCRIPTEN__
		sdlInitFlags &= ~SDL_INIT_HAPTIC;
	#endif

	if (SDL_Init(sdlInitFlags) != 0)
	{
		std::cerr << "Failed to initialize SDL! SDL says: " << SDL_GetError() << "\n";

		return -1;
	}

	this->window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

	SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

	SDL_RendererInfo rendererInfo;
	SDL_GetRendererInfo(this->renderer, &rendererInfo);

	std::cout << "Using renderer: " << rendererInfo.name << std::endl;

	if (this->renderer == nullptr)
	{
		std::cerr << "Failed to create the renderer! SDL says: " << SDL_GetError() << "\n";

		return -3;
	}

	if (TTF_Init() != 0)
	{
		std::cerr << "Failed to initialize SDL_ttf! SDL_ttf says: " << TTF_GetError() << "\n";

		return -4;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cerr << "Failed to initialize SDL_image! SDL_image says: " << IMG_GetError() << "\n";

		return -5;
	}

	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
	{
		std::cerr << "Failed to initialize SDL_mixer! SDL_mixer says: " << Mix_GetError() << "\n";

		return -6;
	}

	if (Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048) != 0)
	{
		std::cerr << "Failed to open audio device! SDL_mixer says: " << Mix_GetError() << "\n";

		return -61;
	}

	if (!Assets::loadAssets(this->renderer))
	{
		std::cerr << "Failed to load assets!\n";

		return -7;
	}

	return 0;
}

void Game::quit()
{
	if (this->menu != nullptr)
	{
		delete this->menu;
		this->menu = nullptr;
	}

	if (this->gameplay != nullptr)
	{
		delete this->gameplay;
		this->gameplay = nullptr;
	}

	Assets::unloadAssets();

	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	TTF_Quit();

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

	std::cout << GAME_TITLE << std::endl;
	std::cout << GAME_COPYRIGHT_STDOUT << "\n" << std::endl;

	auto exitCode = this->init();

	if (exitCode != 0)
	{
		this->quit();
		return exitCode;
	}

	this->isRunning = true;

	// Detect if touch input is available
	this->__isTouchAvailable = SDL_GetNumTouchDevices() > 0;

#if __EMSCRIPTEN__
	emscripten_set_main_loop_arg(GameEmscriptenLoopThunk, this, 0, 1);
#else
	// Get the current monitor's refresh rate and set the target FPS to that.
	SDL_DisplayMode dm;
	int displayIndex = SDL_GetWindowDisplayIndex(this->window);
	int numDisplayModes = SDL_GetNumDisplayModes(displayIndex);
	SDL_GetDesktopDisplayMode(displayIndex, &dm);

	auto refreshRate = dm.refresh_rate != 0 ? dm.refresh_rate : 60;

	FPSLimiter limiter(refreshRate);

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

	// TODO: Should we even call this if we're Emscripten?
	double delta = this->calculateDeltaTime();

	this->handleInput();
	this->update(delta);
	this->render();
}

inline void Game::handleInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.type == SDL_APP_TERMINATING ||
			(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE))
		{
			this->isRunning = false;
			this->currentState = GameState::QUIT;
		}

		switch (this->currentState)
		{
		case GameState::INIT:
			break;
		case GameState::MENU:
			if (this->menu != nullptr)
			{
				this->menu->handleInput(event);
			}
			break;
		case GameState::GAMEPLAY:
			if (this->gameplay != nullptr)
			{
				this->gameplay->handleInput(event);
			}
			break;
		default:
			SDL_Log("Unhandled game state in handleInput call: %d", static_cast<int>(this->currentState));
			[[fallthrough]];
		case GameState::QUIT:
			break;
		}
	}
}

inline void Game::update(double deltaTime)
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

		this->menu->update(deltaTime);
		break;
	case GameState::GAMEPLAY:
		if (this->gameplay == nullptr)
		{
			this->gameplay = new Gameplay();

			if (this->menu != nullptr)
			{
				delete this->menu;
				this->menu = nullptr;
			}
		}

		this->gameplay->update(deltaTime);
		break;
	default:
		SDL_Log("Unhandled game state in update call: %d", static_cast<int>(this->currentState));
		[[fallthrough]];
	case GameState::QUIT:
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
	case GameState::GAMEPLAY:
		if (this->gameplay != nullptr)
		{
			this->gameplay->render(this->renderer);
		}
		break;
	default:
		SDL_Log("Unhandled game state in render call: %d", static_cast<int>(this->currentState));
		[[fallthrough]];
	case GameState::QUIT:
		break;
	}

	SDL_RenderPresent(this->renderer);
}
