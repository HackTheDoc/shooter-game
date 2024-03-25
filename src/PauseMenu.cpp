#include "include/States/PauseMenu.h"

#include "include/Window.h"

PauseMenu::PauseMenu() {}

PauseMenu::~PauseMenu() {}

void PauseMenu::init() {
    // create elements
    title = new UILabel("PAUSE", "h1", hue::font);

    button[RESUME] = new UIButton("RESUME", Event::ID::CLOSE_PAUSE_MENU, "h3", hue::font, UIButton::Type::DOUBLE_CURSOR);
    button[QUIT] = new UIButton("QUIT", Event::ID::QUIT_GAME, "h3", hue::font, UIButton::Type::DOUBLE_CURSOR);
    
    // create container
    int mw = std::max(title->width(), std::max(button[RESUME]->width(), button[QUIT]->width()));
    container.w = std::min(Window::screen.w, mw + 128*(Window::fullscreen+1));
    container.h = Window::screen.h * 0.75;
    container.x = (Window::screen.w - container.w) / 2;
    container.y = (Window::screen.h - container.h) / 2;
    
    // place title
    title->place(
        container.x + (container.w - title->width()) / 2 + 8*(Window::fullscreen+1), 
        container.y    
    );

    // place buttons
    int offsetY = container.y + (container.h + title->height()) / 2;

    button[RESUME]->place(
        container.x + (container.w - button[RESUME]->width()) / 2,
        offsetY - button[RESUME]->height() - 8*(Window::fullscreen+1)
    );

    button[QUIT]->place(
        container.x + (container.w - button[QUIT]->width()) / 2,
        offsetY + 8*(Window::fullscreen+1)
    );
}

void PauseMenu::update() {
    button[RESUME]->update();
    button[QUIT]->update();
}

void PauseMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui);

    title->draw();

    button[RESUME]->draw();
    button[QUIT]->draw();

    Manager::DrawRect(&container, hue::border); 
}

void PauseMenu::clean() {
    title->destroy();

    button[RESUME]->destroy();
    button[QUIT]->destroy();
}
