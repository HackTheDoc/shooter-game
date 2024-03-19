#pragma once

#define DEV_MOD

#include "Manager.h"
#include "Event.h"

#include "Game/Game.h"

class Window {
public:
    static const std::string Title;
    static bool isRunning;

    static SDL_Renderer* renderer;
    static SDL_Rect screen;

    static Manager* manager;
    static Event event;

    Window();
    ~Window();

    int init();
    void update();
    void render();
    void handleEvents();
    void kill();

    /* ----- GAME ----- */

    void openGame();

    /// @brief quit the world and save playtime
    void quitGame();

private:
    /// @brief the actual window
    static SDL_Window* window;

    Game* game;
};
