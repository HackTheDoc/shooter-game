#include "include/Game/Game.h"

#include "include/Window.h"

SDL_Rect Game::camera = {0, 0, 0, 0};
Player* Game::player = nullptr;
Map* Game::map = nullptr;

Game::Game() {}

Game::~Game() {}

void Game::init() {
    camera = Window::screen;

    map = new Map();
    map->init();

    player = new Player();
    player->init();
}

void Game::update() {
    map->update();

    // camera
    camera.x = player->position.x - Window::screen.w / 2;
    camera.y = player->position.y - Window::screen.h / 2;
}

void Game::render() {
    map->render();
}

void Game::clean() {
    player->kill();
    
    map->destroy();
    delete map;
    map = nullptr;
}
