/**
 * @file FPSLimiter.hpp
 * @brief A class that limits the frame rate of the game to a specified value.
 * @author Josh Kennedy
 * 
 * Kablam!
 * Copyright (C) 2023 Josh Kennedy.
 */

#pragma once

#include <SDL2/SDL.h>
#include <chrono>
#include <thread>

// borrowed from https://discourse.libsdl.org/t/fps-leak-while-capping-frame-rate/27601/10
// tweaked so that the frame time is calculated in nanoseconds, keeping the mantissa of the frame time
// -- and using SDL_GetTicks64() to get the current time.

class FPSLimiter
{
public:
    explicit FPSLimiter(int64_t frameTime = 60)
        : m_frameTime{ (double)(1000.0 / frameTime) }
        , m_startTime{ SDL_GetTicks64() }
        , m_sleepTime{ 0.0 }
        , m_frameTimeDebt{ 0.0 }
    {
    }

    inline void run()
    {
        m_sleepTime = (m_frameTime - m_frameTimeDebt) - (SDL_GetTicks64() - m_startTime);
        if (m_sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<unsigned long>(m_sleepTime * 1'000'000)));
        }
        m_frameTimeDebt = (SDL_GetTicks64() - m_startTime) - (m_frameTime - m_frameTimeDebt);
        m_startTime = SDL_GetTicks64();
    }

private:
    double m_frameTime;
    uint64_t m_startTime;
    double m_sleepTime;
    double m_frameTimeDebt;
};
