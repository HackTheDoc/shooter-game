#pragma once

#include "Vector2D.h"
#include "Collider.h"

enum class Orientation;

class Bullet {
public:
    Collider* collider;

    Bullet(const Vector2D& pos, const Orientation o);
    ~Bullet();

    void update();
    void draw();
    
private:
    static constexpr int speed = 12;
    static constexpr int fulltime = 180; // 3s = 3*60 frames = 180 frames

    Vector2D velocity;
    Vector2D position;

    int timeLeft;
};
