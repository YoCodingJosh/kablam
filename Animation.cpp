/**
 * @file Animation.cpp
 * @brief Plays animations on the screen.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#include "Animation.hpp"

#include "Animation.hpp"

#include <SDL2/SDL.h>

#include "Utility.hpp"

Animation::Animation()
{
    // should never call this directly lmao
}

Animation::Animation(SDL_Texture* texture, int numFrames, int frameWidth, int frameHeight, int framesPerSecond, bool loop, int xOffSet, int yOffSet)
{
    this->texture = texture;
    this->numFrames = numFrames;
    this->currentFrame = 0;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->framesPerSecond = framesPerSecond;
    this->type = AnimationType::HORIZONTAL_SPRITE_STRIP; // TODO: support other types
    this->x = 0;
    this->y = 0;
    this->loop = loop;
    this->isActive = false;
    this->timeSinceLastFrame = 0.0;
    this->xOffSet = xOffSet;
    this->yOffSet = yOffSet;
}

void Animation::update(double delta)
{
    if (!this->isActive) return;

    this->timeSinceLastFrame += delta;

    // int framesToUpdate = ceil(delta / (1.00 / (double)this->framesPerSecond));

    int framesToUpdate = floor(clamp(this->timeSinceLastFrame, 0, 1) * this->framesPerSecond);

    if (framesToUpdate > 0)
    {
        this->currentFrame += framesToUpdate;

        this->timeSinceLastFrame = 0.0;

        if (this->currentFrame >= this->numFrames)
        {
            if (this->loop)
            {
                this->currentFrame %= this->numFrames;
            }
            else
            {
                this->currentFrame = this->numFrames;
                this->isActive = false;
            }
        }
    }
}

void Animation::render(SDL_Renderer* renderer)
{
    int x = this->currentFrame * this->frameWidth;
    int y = 0; // TODO: support other types
    int w = this->frameWidth;
    int h = this->frameHeight;
    SDL_Rect src = { x + this->xOffSet, y + this->yOffSet, w, h };
    SDL_Rect dst = { (int)this->x, (int)this->y, w, h };
    SDL_RenderCopy(renderer, this->texture, &src, &dst);
}

int Animation::getCurrentFrame() const
{
    return this->currentFrame;
}

int Animation::getNumFrames() const
{
    return this->numFrames;
}

int Animation::getFrameWidth() const
{
    return this->frameWidth;
}

int Animation::getFrameHeight() const
{
    return this->frameHeight;
}

void Animation::play()
{
    this->isActive = true;
}

void Animation::pause()
{
    this->isActive = false;
}

void Animation::stop()
{
    this->currentFrame = 0;
    this->isActive = false;
}

bool Animation::isPlaying() const
{
    return this->isActive;
}

void Animation::setLoop(bool loop)
{
    this->loop = loop;
}

bool Animation::isLooping() const
{
    return this->loop;
}
