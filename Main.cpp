/**
 * @file Main.cpp
 * @brief The main entry point for the application.
 * @author Josh Kennedy
 * 
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#include "Init.hpp"
#include "Game.hpp"

int main(int argc, char* argv[])
{
    if (!hypeInit())
    {
		return -1;
    }

    auto exitCode = Game::get()->run();

    hypeShutdown();

    return exitCode;
}
