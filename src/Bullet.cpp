#include "include/Game/Components/Bullet.h"

#include "include/Window.h"

Bullet::Bullet(const Vector2D& pos, const Orientation o) {
    position = pos;

    int w,h;
    switch (o) {
    case Orientation::NORTH:
        velocity = {0,-1};
        w = 4;
        h = 12;
        break;
    case Orientation::SOUTH:
        velocity = {0,1};
        w = 4;
        h = 12;
        break;
    case Orientation::WEST:
        velocity = {-1,0};
        w = 12;
        h = 4;
        break;   
    case Orientation::EAST:
        velocity = {1,0};
        w = 12;
        h = 4;
        break;
    }

    collider = new Collider(w,h);

    timeLeft = fulltime;
}

Bullet::~Bullet() {}

void Bullet::update() {
    position += velocity*speed;

    collider->place(position);
    collider->update();

    timeLeft--;
    if (timeLeft < 0) Game::map->removeBullet();
}

void Bullet::draw() {
    Manager::DrawFilledRect(&collider->rect, hue::bullet);
}
