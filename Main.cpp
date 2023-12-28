/**
 * @file Main.cpp
 * @brief The main entry point for the application.
 * @author Josh Kennedy
 * 
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#include "Game.hpp"

int main(int argc, char* argv[])
{
    return Game::get()->run();
}
