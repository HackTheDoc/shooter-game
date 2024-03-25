#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class Credits : public WindowState {
private:
    enum links {
        DISCORD,
        TWITTER,
        GITHUB,
        NUMBER_OF_LINKS
    };
    UIHyperlink* link[NUMBER_OF_LINKS];

    enum labels {
        TITLE,
        AUTHOR,
        SOCIALS,
        EMAIL,
        NUMBER_OF_LABELS
    };
    UILabel *label[NUMBER_OF_LABELS];

    UIButton* quitButton;

public:
    Credits();
    ~Credits();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
};
