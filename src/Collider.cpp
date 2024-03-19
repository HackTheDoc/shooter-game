#include "include/Game/Components/Collider.h"

#include "include/Manager.h"

#include "include/Game/Game.h"

/* ----- COLLIDER ----- */

Collider::Collider() {
    rect = {0, 0, 0, 0};
}

Collider::Collider(const int w, const int h) {
    rect = {0, 0, w, h};
}

Collider::~Collider() {}

void Collider::update() {
    rect.x = position.x - Game::camera.x;
    rect.y = position.y - Game::camera.y;
}

void Collider::draw() {
    Manager::DrawRect(&rect, hue::red);
}

void Collider::place(const int x, const int y) {
    position.x = x;
    position.y = y;
}

void Collider::place(const Vector2D& pos) {
    place(pos.x, pos.y);
}

/* ----- ENTITY COLLIDER ----- */

EntityCollider::EntityCollider(Entity* o) {
    rect = {0,0,0,0};
    setOwner(o);
    rect.w = Entity::SIZE / 4;
    rect.h = Entity::SIZE / 2;
}

EntityCollider::~EntityCollider() {}

void EntityCollider::update() {
    position = owner->position;

    Collider::update();
}

void EntityCollider::setOwner(Entity* o) {
    owner = o;
}
