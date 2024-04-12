/**
 * @file Utility.hpp
 * @brief Common utility functions and classes for the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* renderTextWithOutline(SDL_Renderer* renderer, const char* text, int outlineSize = 2, SDL_Color textColor = { 0xFF, 0xFF, 0xFF }, SDL_Color outlineColor = { 0x00, 0x00, 0x00 });
SDL_Texture* renderTextWithOutlineCoolEffect(SDL_Renderer* renderer, const char* text, SDL_Color textColor = { 0xFF, 0xFF, 0xFF }, SDL_Color outlineColor = { 0x00, 0x00, 0x00 });

inline int lerp(int a, int b, float t)
{
	return a + (b - a) * t;
}
