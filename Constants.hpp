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
constexpr auto GAME_COPYRIGHT = "Copyright \xA9 2024 Josh Kennedy";
constexpr auto SCREEN_WIDTH = 1280;
constexpr auto SCREEN_HEIGHT = 960;

constexpr auto TARGET_FRAME_RATE = 60;
constexpr auto TARGET_FRAME_TIME = 1 / TARGET_FRAME_RATE;

#define CAN_QUIT_GAME = !__EMSCRIPTEN__

constexpr auto BRICK_WALL_PIECE = "BRICK_WALL_PIECE";
constexpr auto BRICK_WALL_PIECE_SPRITE_FILE = "assets/wall128x128.png";
constexpr auto BRICK_WALL_PIECE_SPRITE_WIDTH = 128;
constexpr auto BRICK_WALL_PIECE_SPRITE_HEIGHT = 128;

constexpr auto BRICK_WALL = "BRICK_WALL";
