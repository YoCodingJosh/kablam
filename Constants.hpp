/**
 * @file Constants.hpp
 * @brief Global constants for the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

constexpr auto GAME_TITLE = "Kablam!";
constexpr auto GAME_COPYRIGHT = "Copyright � 2024 Josh Kennedy";

constexpr auto SCREEN_WIDTH = 1280;
constexpr auto SCREEN_HEIGHT = 960;

#define CAN_QUIT_GAME = !__EMSCRIPTEN__

constexpr auto BRICK_WALL = "BRICK_WALL";
constexpr auto BRICK_WALL_SPRITE_FILE = "assets/wall128x128.png";
