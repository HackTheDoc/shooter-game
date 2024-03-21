#include "include/Event.h"

#include "include/Game/Game.h"

#include "include/Window.h"

#include "include/Save.h"
#include "include/KeyMap.h"

#include <iostream>

Event::Event() {}

Event::~Event() {}

void Event::linkTo(Window* w) {
    window = w;
}

void Event::handleKeyboardInputs() {
    SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);

    if (e.type == SDL_KEYDOWN) {
        switch (KeyMap::Key[k]) {
        case Event::ID::MOVE_UP:
            Game::player->velocity.y = -1;
            Game::player->orientate(Orientation::NORTH);
            break;
        case Event::ID::MOVE_DOWN:
            Game::player->velocity.y = 1;
            Game::player->orientate(Orientation::SOUTH);
            break;
        case Event::ID::MOVE_LEFT:
            Game::player->velocity.x = -1;
            Game::player->orientate(Orientation::WEST);
            break;
        case Event::ID::MOVE_RIGHT:
            Game::player->velocity.x = 1;
            Game::player->orientate(Orientation::EAST);
            break;
        case Event::ID::SHOOT:
            Game::player->shoot();
        case Event::ID::UNKNOWN:
        default:
            break;
        }
    }

    if (e.type == SDL_KEYUP) {
        switch (KeyMap::Key[k]) {
        case Event::ID::MOVE_UP:
        case Event::ID::MOVE_DOWN:
            Game::player->velocity.y = 0;
            break;
        case Event::ID::MOVE_LEFT:
        case Event::ID::MOVE_RIGHT:
            Game::player->velocity.x = 0;
            break;
        case Event::ID::UNKNOWN:
        default:
            break;
        }
    }
}

bool Event::mouseClickLeft() {
    return e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT;
}

bool Event::mouseClickRight() {
    return e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT;
}

void Event::raise(const Event::ID id) {
    switch (id) {
    case ID::QUIT:
        Window::isRunning = false;
        break;
    case ID::OPEN_GAME:
        window->openGame();
        break;
        
    default:
        break;
    }
}
