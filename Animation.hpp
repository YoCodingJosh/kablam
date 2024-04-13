/**
 * @file Animation.hpp
 * @brief Plays animations on the screen.
 * @author Josh Kennedy
 *
 * Kablam!
 * Copyright (C) 2024 Josh Kennedy.
 */

#pragma once

enum class AnimationType : char
{
    HORIZONTAL_SPRITE_STRIP = 0,
};

struct SDL_Texture;
struct SDL_Renderer;

class Animation
{
private:
    SDL_Texture* texture; // don't free this
    int numFrames;
    int currentFrame;
    int frameWidth;
    int frameHeight;
    int framesPerSecond;
    AnimationType type;
    int x;
    int y;
    bool loop;
    bool isActive;
    double timeSinceLastFrame;
    int xOffSet;
    int yOffSet;
public:
    Animation();
    Animation(SDL_Texture* texture, int numFrames, int frameWidth, int frameHeight, int framesPerSecond, bool loop = true, int xOffSet = 0, int yOffSet = 0);
    void update(double delta);
    void render(SDL_Renderer* renderer);
    inline int getX() const { return x; }
    inline void setX(int x) { this->x = x; }
    inline int getY() const { return y; }
    inline void setY(int y) { this->y = y; }
    int getCurrentFrame() const;
    int getNumFrames() const;
    int getFrameWidth() const;
    int getFrameHeight() const;
    void play();
    void pause();
    void stop();
    bool isPlaying() const;
    void setLoop(bool loop);
    bool isLooping() const;
};
