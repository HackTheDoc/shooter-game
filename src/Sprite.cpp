#include "include/Game/Components/Sprite.h"

#include "include/Window.h"

Sprite::Sprite(Entity* o) {
    linkTo(o);
    texture = nullptr;
    srcRect = destRect = { 0, 0, Entity::SIZE, Entity::SIZE };
}

Sprite::~Sprite() {}

void Sprite::init() {
    switch (owner->color) {
    case Entity::Color::YELLOW:
    default:
        srcRect.x = 0 * Entity::SIZE;
        srcRect.y = 0 * Entity::SIZE;
        break;
    }

    texture = Window::manager->getTexture("soldiers");
}

void Sprite::update() {
    destRect.x = owner->position.x - (destRect.w - destRect.w / 4) / 2 - Game::camera.x;
    destRect.y = owner->position.y - (destRect.h - destRect.h / 2) * 0.75 - Game::camera.y;
}

void Sprite::draw() {
    Manager::Draw(texture, &srcRect, &destRect, o);
}

void Sprite::destroy() {
    texture = nullptr;
}

void Sprite::linkTo(Entity* o) {
    owner = o;
}
