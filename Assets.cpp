/**
 * @file Assets.cpp
 * @brief Loads and stores game assets such as textures, sounds, and music.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#include "Assets.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <string>

#define DEFAULT_FONT_PATH "assets/DotGothic16-Regular.ttf"

TTF_Font* Assets::defaultFont = nullptr;

std::map<std::string, SDL_Texture*> Assets::textures;

bool Assets::loadAssets(SDL_Renderer* renderer)
{
	Assets::defaultFont = TTF_OpenFont(DEFAULT_FONT_PATH, 24);

	if (Assets::defaultFont == nullptr)
	{
		SDL_Log("Failed to load default font: %s", TTF_GetError());
		return false;
	}

	return true;
}

void Assets::unloadAssets()
{
	for (auto& texture : Assets::textures)
	{
		SDL_DestroyTexture(texture.second);
	}

	Assets::textures.clear();

	TTF_CloseFont(Assets::defaultFont);
	Assets::defaultFont = nullptr;
}
