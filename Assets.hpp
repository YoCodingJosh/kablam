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
	static TTF_Font* menuFont;

	static std::map<std::string, SDL_Texture*> textures;

	static bool loadAssets(SDL_Renderer* renderer);
	static void unloadAssets();

	static bool loadTexture(SDL_Renderer* renderer, const std::string& name, const std::string& path);

public:
	inline static TTF_Font* getDefaultFont() noexcept { return defaultFont; }
	inline static TTF_Font* getMenuFont() noexcept { return menuFont; }
	static TTF_Font* getMenuFontCopy(); // this is for renderTextWithOutline functions to use lol

	static SDL_Texture* getTexture(const std::string& name);
};
