/**
 * @file Assets.hpp
 * @brief Loads and stores game assets such as textures, sounds, and music.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#pragma once

struct SDL_Texture;
struct _TTF_Font;
typedef _TTF_Font TTF_Font;

#include <string>
#include <map>

class Assets
{
private:
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;

public:
	Assets();
	~Assets();

	SDL_Texture* loadTexture(const std::string& path);
	TTF_Font* loadFont(const std::string& path, int size);

	SDL_Texture* getTexture(const std::string& name);
	TTF_Font* getFont(const std::string& name);

	void destroyTexture(const std::string& name);
	void destroyFont(const std::string& name);
};
