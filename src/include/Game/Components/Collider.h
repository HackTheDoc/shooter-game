#pragma once

#include <SDL2/SDL.h>

#include "Vector2D.h"

class Collider {
public:
    Vector2D position;
    SDL_Rect rect;

    Collider();
    Collider(const int w, const int h);
    ~Collider();

    void update();
    void draw(); // TODO remove collider rendering

    void place(const int x, const int y);
    void place(const Vector2D& pos);
};

class Entity;

class EntityCollider : public Collider {
public:
    EntityCollider(Entity* o = nullptr);
    ~EntityCollider();

    void update();

    void setOwner(Entity* o);

protected:
    Entity* owner;
};

