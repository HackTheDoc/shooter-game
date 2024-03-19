#pragma once

#include <SDL2/SDL.h>

class Window;

class Event {
private:
    Window* window; // owner window

public:
    enum ID {
        UNKNOWN,

        // MOVEMENT
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,

        // OTHER
        SHOOT
    };

    /// @brief classic SDL_Event object
    SDL_Event e;

    Event();
    ~Event();

    /// @brief set the owner window pointer
    /// @param w pointer to the new owner
    void linkTo(Window* w);

    /// @brief handle user's keyboard inputs
    void handleKeyboardInputs();

    /// @brief check for a mouse left click
    /// @return true when mouse click left else false
    bool mouseClickLeft();

    /// @brief check for a mouse right click
    /// @return true when mouse click right else false
    bool mouseClickRight();

    void raise(const Event::ID id);
};
