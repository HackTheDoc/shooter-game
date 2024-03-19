#include "include/Game/Entities/Player.h"

#include "include/Window.h"

Player::Player() {}

Player::~Player() {}

void Player::init() {
    Entity::init();

    color = Color::YELLOW;

    sprite = new Sprite(this);
    sprite->init();

    collider = new EntityCollider(this);

    position.x = Window::screen.w / 2;
    position.y = Window::screen.h / 2;
}

void Player::update() {
    Entity::update();
}

void Player::draw() {
    Entity::draw();
}

void Player::kill() {
    sprite->destroy();
    delete sprite;
    sprite = nullptr;

    delete collider;
    collider = nullptr;
}

void Player::shoot() {
    Game::map->addBullet(position, sprite->o);
}
