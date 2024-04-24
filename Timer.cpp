/**
 * @file Timer.cpp
 * @brief Simple timer class for timing events in the game.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#include "Timer.hpp"

#include <SDL2/SDL.h>

Timer::Timer(uint64_t time)
{
    this->time = time;
    this->ticks = 0;
    this->endTicks = 0;
    this->paused = false;
    this->started = false;
    this->loop = false;
}

Timer::~Timer()
{
    this->stop();
}

void Timer::start()
{
    this->ticks = SDL_GetTicks64();
    this->endTicks = this->ticks + this->time;

    this->started = true;
    this->paused = false;
}

void Timer::stop()
{
    this->started = false;
    this->paused = false;
}

void Timer::pause()
{
    if (this->started && !this->paused)
    {
        this->pausedTicks = SDL_GetTicks64();
        this->paused = true;
    }
}

void Timer::unpause()
{
    if (this->started && this->paused)
    {
        this->ticks += SDL_GetTicks64() - this->pausedTicks;
        this->paused = false;
    }
}

void Timer::setLoop(bool loop)
{
    this->loop = loop;
}

bool Timer::isLooping() const
{
    return this->loop;
}

void Timer::tick()
{
    if (this->started && !this->paused)
    {
        if (this->tickCallback)
        {
            this->tickCallback();
        }

        if (this->getTicks() >= this->time)
        {
            if (this->timeUpCallback)
            {
                this->timeUpCallback();
            }

            if (this->loop)
            {
                this->reset();
            }
            else
            {
                this->stop();
            }
        }
    }
}

uint64_t Timer::getTicks()
{
    if (this->started)
    {
        if (this->paused)
        {
            return this->ticks;
        }
        else
        {
            return SDL_GetTicks64() - this->ticks;
        }
    }

    return 0;
}

bool Timer::isPaused()
{
    return this->paused;
}

bool Timer::isStarted()
{
    return this->started;
}

void Timer::setTickCallback(std::function<void()> tickCallback)
{
    this->tickCallback = tickCallback;
}

void Timer::removeTickCallback()
{
    this->tickCallback = nullptr;
}

void Timer::setTimeUpCallback(std::function<void()> timeUpCallback)
{
    this->timeUpCallback = timeUpCallback;
}

void Timer::removeTimeUpCallback()
{
    this->timeUpCallback = nullptr;
}

void Timer::reset()
{
    this->ticks = SDL_GetTicks64();
    this->endTicks = this->ticks + this->time;
}

double Timer::getSecondsRemaining() const noexcept
{
    return (this->endTicks - SDL_GetTicks64()) / 1000.0;
}
