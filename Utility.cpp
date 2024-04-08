/**
 * @file Utility.cpp
 * @brief Common utility functions and classes for the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#include "Utility.hpp"

#include "Assets.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* renderTextWithOutline(SDL_Renderer* renderer, const char* text, int outlineSize, SDL_Color textColor, SDL_Color outlineColor)
{
	TTF_Font* outlineFont = Assets::getMenuFontCopy();
	if (!outlineFont)
	{
		SDL_Log("Failed to create outline font: %s", TTF_GetError());

		return nullptr;
	}

	TTF_SetFontHinting(outlineFont, TTF_HINTING_NORMAL);
	TTF_SetFontOutline(outlineFont, outlineSize);

	/* render text and text outline */
	SDL_Surface* bg_surface = TTF_RenderText_Blended(outlineFont, text, outlineColor);
	SDL_Surface* fg_surface = TTF_RenderText_Blended(Assets::getMenuFont(), text, textColor);
	SDL_Rect rect = { outlineSize, outlineSize, fg_surface->w, fg_surface->h };

	/* blit text onto its outline */
	SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
	SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);
	SDL_FreeSurface(fg_surface);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bg_surface);

	if (!texture)
	{
		SDL_Log("Failed to create texture from surface: %s", SDL_GetError());

		SDL_FreeSurface(bg_surface);
		TTF_CloseFont(outlineFont);

		return nullptr;
	}

	SDL_FreeSurface(bg_surface);

	TTF_CloseFont(outlineFont);

	return texture;
}

SDL_Texture* renderTextWithOutlineCoolEffect(SDL_Renderer* renderer, const char* text, SDL_Color textColor, SDL_Color outlineColor)
{
	const int outlineSize = 7;

	TTF_Font* outlineFont = Assets::getMenuFontCopy();
	if (!outlineFont)
	{
		SDL_Log("Failed to create outline font: %s", TTF_GetError());

		return nullptr;
	}

	TTF_SetFontHinting(outlineFont, TTF_HINTING_NORMAL);
	TTF_SetFontOutline(outlineFont, 10);

	/* render text and text outline */
	SDL_Surface* bg_surface = TTF_RenderText_Blended(outlineFont, text, outlineColor);
	SDL_Surface* fg_surface = TTF_RenderText_Blended(Assets::getMenuFont(), text, textColor);
	SDL_Rect rect = { outlineSize, outlineSize, fg_surface->w, fg_surface->h };

	/* blit text onto its outline */
	SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
	SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);
	SDL_FreeSurface(fg_surface);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bg_surface);

	if (!texture)
	{
		SDL_Log("Failed to create texture from surface: %s", SDL_GetError());

		SDL_FreeSurface(bg_surface);
		TTF_CloseFont(outlineFont);

		return nullptr;
	}

	SDL_FreeSurface(bg_surface);

	TTF_CloseFont(outlineFont);

	return texture;
}
