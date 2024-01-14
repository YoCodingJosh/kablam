/**
 * @file Assets.hpp
 * @brief Loads and stores game assets such as textures, sounds, and music.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;
typedef _TTF_Font TTF_Font;

#include <string>
#include <map>

class Assets final
{
	friend class Game;
private:
	static TTF_Font* defaultFont;
	static std::map<std::string, SDL_Texture*> textures;

	static void destroyTexture(const std::string& name);
	static void destroyFont(const std::string& name);

	static bool loadAssets(SDL_Renderer* renderer);
	static void unloadAssets();

public:
	inline static TTF_Font* getDefaultFont() noexcept { return defaultFont; }

	static SDL_Texture* getTexture(const std::string& name);
};
