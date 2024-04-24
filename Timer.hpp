/**
 * @file Timer.hpp
 * @brief Simple timer class for timing events in the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

#include <stdint.h>
#include <functional>

class Timer
{
private:
    uint64_t time;
    uint64_t ticks;
    uint64_t endTicks;
    uint64_t pausedTicks;
    bool paused;
    bool started;
    std::function<void()> tickCallback;
    std::function<void()> timeUpCallback;
    bool loop;
public:
    Timer(uint64_t time);
    ~Timer();

    void start();
    void stop();
    void pause();
    void unpause();
    void reset();
    void setLoop(bool loop);
    bool isLooping() const;

    void tick();

    uint64_t getTicks();

    bool isPaused();
    bool isStarted();

    void setTickCallback(std::function<void()> tickCallback);
    void removeTickCallback();

    void setTimeUpCallback(std::function<void()> timeUpCallback);
    void removeTimeUpCallback();

    double getSecondsRemaining() const noexcept;
};
