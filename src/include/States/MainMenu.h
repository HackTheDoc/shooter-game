#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class MainMenu : public WindowState {
private:
    enum buttons {
        PLAY,
        OPTIONS,
        CREDITS,
        QUIT,
        NUMBER_OF_BUTTONS
    };
    UIButton* button[NUMBER_OF_BUTTONS];

    UILabel* title;

public:
    MainMenu();
    ~MainMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
};
