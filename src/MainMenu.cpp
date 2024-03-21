#include "include/States/MainMenu.h"

#include "include/Window.h"

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::init() {
    title = new UILabel(Window::Title, "h1", hue::font);
    title->place(8*(Window::fullscreen+1), 0);

    /* ----- BUTTONS ----- */
    int offsetY = (Window::screen.h + title->height()) / 2;

    button[OPTIONS] = new UIButton("Options", Event::ID::OPEN_OPTIONS, "h3", hue::font, UIButton::Type::RIGHT_CURSOR);
    button[OPTIONS]->place(
        16*(Window::fullscreen+1),
        offsetY - button[OPTIONS]->height() - 8*(Window::fullscreen+1)
    );

    button[PLAY] = new UIButton("Play", Event::ID::OPEN_GAME, "h3", hue::font, UIButton::Type::RIGHT_CURSOR);
    button[PLAY]->place(
        16*(Window::fullscreen+1),
        offsetY - button[OPTIONS]->height() - button[PLAY]->height() - 24*(Window::fullscreen+1)
    );

    button[CREDITS] = new UIButton("Credits", Event::ID::OPEN_CREDITS, "h3", hue::font, UIButton::Type::RIGHT_CURSOR);
    button[CREDITS]->place(
        16*(Window::fullscreen+1),
        offsetY + 8*(Window::fullscreen+1)
    );

    button[QUIT] = new UIButton("Quit", Event::ID::QUIT, "h3", hue::font, UIButton::Type::RIGHT_CURSOR);
    button[QUIT]->place(
        16*(Window::fullscreen+1),
        offsetY + button[CREDITS]->height() + 24*(Window::fullscreen+1)
    );
}

void MainMenu::update() {
    button[PLAY]->update();
    button[OPTIONS]->update();
    button[CREDITS]->update();
    button[QUIT]->update();
}

void MainMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::ui);
    
    title->draw();

    button[PLAY]->draw();
    button[OPTIONS]->draw();
    button[CREDITS]->draw();
    button[QUIT]->draw();
}

void MainMenu::clean() {
    title->destroy();

    button[PLAY]->destroy();
    button[OPTIONS]->destroy();
    button[CREDITS]->destroy();
    button[QUIT]->destroy();
}
