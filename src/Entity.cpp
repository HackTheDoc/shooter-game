#include "include/Game/Entities/Entity.h"

#include "include/Window.h"

const int Entity::MAX_HP = 100;
const int Entity::SIZE = 512;

Entity::Entity() {}

Entity::~Entity() {}

void Entity::init() {
    immortal = false;

    sprite = nullptr;
    collider = nullptr;

    position.Zero();
    velocity.Zero();

    speed = 6;

    hp = MAX_HP;

    color = Color::UNKNOWN;
}

void Entity::update() {
    if (sprite)
        sprite->update();
    if (collider)
        collider->update();

    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
}

void Entity::draw() {
    if (sprite)
        sprite->draw();
#ifdef DEV_MOD
    if (collider)
        collider->draw();
#endif
}

void Entity::kill() {
    if (sprite) {
        sprite->destroy();
        delete sprite;
        sprite = nullptr;
    }
    if (collider) {
        delete collider;
        collider = nullptr;
    }
}

void Entity::setPosition(const int x, const int y) {
    position.x = x;
    position.y = y;
}

void Entity::setPosition(const Vector2D& pos) {
    setPosition(pos.x, pos.y);
}

void Entity::orientate(const Orientation o) {
    sprite->o = o;
}

void Entity::resetMovement() {
    velocity.Zero();
}

void Entity::reverseMovement() {
    position.x -= 2 * velocity.x * speed;
    position.y -= 2 * velocity.y * speed;
}

bool Entity::has_died() {
    return hp == 0;
}
