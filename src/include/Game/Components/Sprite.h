#pragma once

#include <SDL2/SDL.h>

class Entity;

enum class Orientation;

class Sprite {
public:
    Orientation o;

    Sprite(Entity* o = nullptr);
    ~Sprite();

    void init();
    void linkTo(Entity* entity);
    void update();
    void draw();
    void destroy();

private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    Entity* owner;
};
