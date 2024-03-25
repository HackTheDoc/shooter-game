#pragma once

#define DEV_MOD

#include "Manager.h"
#include "Event.h"

class Window {
public:
    static const std::string Title;
    static bool isRunning;
    static bool fullscreen;

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

    void openMainMenu();
    
    void openGame();
    void quitGame();

    void pauseGame();
    void resumeGame();

private:
    /// @brief the actual window
    static SDL_Window* window;
};
