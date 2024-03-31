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

#include "Game.hpp"
#include "Constants.hpp"

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

	Assets::loadTexture(renderer, BRICK_WALL, BRICK_WALL_SPRITE_FILE);

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

bool Assets::loadTexture(SDL_Renderer* renderer, const std::string& name, const std::string& path)
{
	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == nullptr)
	{
		SDL_Log("Failed to load texture: %s", IMG_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == nullptr)
	{
		SDL_Log("Failed to create texture: %s", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surface);

	Assets::textures.emplace(name, texture);

	return true;
}

SDL_Texture* Assets::getTexture(const std::string& name)
{
	if (Assets::textures.find(name) == Assets::textures.end())
	{
		SDL_Log("Failed to find texture: %s", name.c_str());
		return nullptr;
	}

	return Assets::textures[name];
}
