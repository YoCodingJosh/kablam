/**
 * @file Main.cpp
 * @brief The main entry point for the application.
 * @author Josh Kennedy
 * 
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#if _WIN32
// not sure why visual studio suddenly broke, this fixes it.
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>

#include "Game.hpp"

int main(int argc, char* argv[])
{
#if _WIN32
    SDL_SetMainReady();
#endif
    return Game::get()->run();
}
