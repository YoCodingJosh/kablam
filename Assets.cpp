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
#define MENU_FONT_PATH "assets/NotoSans-Regular.ttf"

TTF_Font* Assets::defaultFont = nullptr;
TTF_Font* Assets::menuFont = nullptr;

std::map<std::string, SDL_Texture*> Assets::textures;
std::map<std::string, Animation*> Assets::animations;

bool Assets::loadAssets(SDL_Renderer* renderer)
{
	Assets::defaultFont = TTF_OpenFont(DEFAULT_FONT_PATH, 24);

	if (Assets::defaultFont == nullptr)
	{
		SDL_Log("Failed to load default font: %s", TTF_GetError());
		return false;
	}

	Assets::menuFont = TTF_OpenFont(MENU_FONT_PATH, 24);

	if (Assets::menuFont == nullptr)
	{
		SDL_Log("Failed to load menu font: %s", TTF_GetError());
		return false;
	}

	if (!Assets::loadTexture(renderer, BRICK_WALL_PIECE, BRICK_WALL_PIECE_SPRITE_FILE))
	{
		// we already logged the error in loadTexture
		return false;
	}

	// Construct the wall used in both the menu and the game.
	SDL_Texture* wallPiece = Assets::getTexture(BRICK_WALL_PIECE);

	// create renderer for the wall texture
	SDL_Texture* wallTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_SetRenderTarget(renderer, wallTexture);

	// clear the wall texture to a solid color (cornflower blue) for the skybox
	SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
	SDL_RenderClear(renderer);

	// tile the wall piece across the screen to create a wall
	for (int x = 0; x < SCREEN_WIDTH; x += BRICK_WALL_PIECE_SPRITE_WIDTH)
	{
		for (int y = SKYBOX_HEIGHT; y < SCREEN_HEIGHT; y += BRICK_WALL_PIECE_SPRITE_HEIGHT)
		{
			SDL_Rect destRect = { x, y, BRICK_WALL_PIECE_SPRITE_WIDTH, BRICK_WALL_PIECE_SPRITE_HEIGHT };
			SDL_RenderCopy(renderer, wallPiece, NULL, &destRect);
		}
	}

	SDL_SetRenderTarget(renderer, nullptr);

	Assets::textures.emplace(BRICK_WALL, wallTexture);

	// Load the bomb texture
	if (!Assets::loadTexture(renderer, BOMB, BOMB_SPRITE_FILE))
	{
		// we already logged the error in loadTexture
		return false;
	}

	// Create a bomb animation
	Animation* bombAnimation = new Animation(Assets::textures[BOMB], 4, BOMB_SPRITE_WIDTH, BOMB_SPRITE_HEIGHT, 15);

	Assets::animations.emplace(BOMB, bombAnimation);

	return true;
}

void Assets::unloadAssets()
{
	// Free all animations
	for (auto& animation : Assets::animations)
	{
		delete animation.second;
	}

	Assets::animations.clear();

	// Free all textures
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

TTF_Font* Assets::getMenuFontCopy()
{
	return TTF_OpenFont(MENU_FONT_PATH, 24);
}

Animation Assets::getAnimation(const std::string& name)
{
	if (Assets::animations.find(name) == Assets::animations.end())
	{
		SDL_Log("Failed to find animation: %s", name.c_str());
		return Animation();
	}

	// be explicit about doing a copy here, since we have a pointer to the animation
	Animation* animation = Assets::animations[name];
	Animation copy = *animation;

	return copy;
}
