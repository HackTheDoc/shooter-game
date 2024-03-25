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
    switch (Window::manager->getCurrentWindowStateID()) {
    case WindowState::ID::GAME:
        handleGameEvents();
        break;
    case WindowState::ID::PAUSE_MENU:
        handlePauseMenuEvents();
        break;
    default:
        break;
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
    case ID::OPEN_CREDITS:
        window->openCredits();
        break;
    case ID::QUIT_CREDITS:
        window->openMainMenu();
        break;
    case ID::OPEN_GAME:
        window->openGame();
        break;
    case ID::QUIT_GAME:
        window->quitGame();
        break;
    case ID::OPEN_PAUSE_MENU:
        window->pauseGame();
        break;
    case ID::CLOSE_PAUSE_MENU:
        window->resumeGame();
        break;
    default:
        break;
    }
}

void Event::handleGameEvents() {
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
        case ID::MOVE_UP:
        case ID::MOVE_DOWN:
            Game::player->velocity.y = 0;
            break;
        case ID::MOVE_LEFT:
        case ID::MOVE_RIGHT:
            Game::player->velocity.x = 0;
            break;
        case ID::OPEN_PAUSE_MENU:
            raise(ID::OPEN_PAUSE_MENU);
            break;
        case ID::UNKNOWN:
        default:
            break;
        }
    }
}

void Event::handlePauseMenuEvents() {
    if (e.type != SDL_KEYUP)
        return;

    const SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    if (KeyMap::Key[k] == Event::ID::OPEN_PAUSE_MENU) {
        raise(ID::CLOSE_PAUSE_MENU);
        return;
    }

    switch (k) {
    case SDLK_q:
        if (SDL_GetModState() & KMOD_CTRL)
            raise(ID::QUIT_GAME);
        break;
    case SDLK_r:
        if (SDL_GetModState() & KMOD_CTRL)
            raise(ID::CLOSE_PAUSE_MENU);
        break;
    default:
        break;
    }
}
