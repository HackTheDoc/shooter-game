#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class PauseMenu : public WindowState {
public:
    PauseMenu();
    ~PauseMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    SDL_Rect container;

    enum buttons {
        RESUME,
        QUIT,
        NUMBER_OF_BUTTONS
    };
    UIButton* button[NUMBER_OF_BUTTONS];

    UILabel* title;
    
};
