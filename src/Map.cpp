#include "include/Game/Map.h"

#include "include/Window.h"
#include "include/Game/Game.h"

Map::Map() {}

Map::~Map() {}

void Map::init() {
    // nothing for now
}

void Map::update() {
    for (auto b : bullets)
        b->update();

    Game::player->update();
}

void Map::render() {
    Manager::DrawFilledRect(&Window::screen, hue::map);

    Game::player->draw();

    for (auto b : bullets)
        b->draw();
}

void Map::destroy() {
    for (auto b : bullets)
        delete b;
    bullets.clear();
}

void Map::addBullet(const Vector2D& pos, const Orientation o) {
    bullets.push_back(new Bullet(pos, o));
}

void Map::removeBullet() {
    delete bullets[0];
    bullets.erase(bullets.begin());
}
