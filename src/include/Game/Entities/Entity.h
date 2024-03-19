#pragma once

#include "../Components/Vector2D.h"
#include "../Components/Sprite.h"
#include "../Components/Collision.h"

class Entity {
public:
    static const int MAX_HP;
    static const int SIZE;

    enum Color {
        YELLOW,

        UNKNOWN // literrally unknown
    };
    Color color;

    Sprite* sprite;
    EntityCollider* collider;

    int hp;

    Vector2D position, velocity;
    int speed;

    bool immortal;

    Entity();
    ~Entity();

    virtual void init();
    virtual void update();
    virtual void draw();
    virtual void kill();

    void setPosition(const int x, const int y);
    void setPosition(const Vector2D& pos);
    void orientate(const Orientation o);

    void resetMovement();
    void reverseMovement();

    bool has_died();
};
