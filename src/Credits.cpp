#include "include/States/Credits.h"

#include "include/Window.h"

Credits::Credits() {}

Credits::~Credits() {}

void Credits::init() {
    // title + author

    label[TITLE] = new UILabel("Developped By", "h4", hue::font);
    label[TITLE]->place(
        16 * (Window::fullscreen + 1),
        8*(Window::fullscreen+1)
    );

    label[AUTHOR] = new UILabel("HackTheDoc", "h3 bold", hue::red);
    label[AUTHOR]->place(
        1 * label[TITLE]->width() / 3 + 16 * (Window::fullscreen + 1),
        label[TITLE]->height() + 16*(Window::fullscreen+1)
    );

    const int offsetY = (Window::screen.h + label[AUTHOR]->y() + label[AUTHOR]->height()) / 2;

    // links
    link[DISCORD] = new UIHyperlink("Discord", "https://discord.gg/Ya8NWJMcqx", "big", hue::font);
    link[DISCORD]->place(
        (Window::screen.w - link[DISCORD]->width()) / 2,
        offsetY - link[DISCORD]->height() - 8*(Window::fullscreen+1)
    );

    link[GITHUB] = new UIHyperlink("Github", "https://github.com/HackTheDoc", "big", hue::font);
    link[GITHUB]->place(
        (Window::screen.w - link[GITHUB]->width()) / 2,
        offsetY - link[DISCORD]->height() - link[GITHUB]->height() - 24*(Window::fullscreen+1)
    );

    link[TWITTER] = new UIHyperlink("Twitter", "https://twitter.com/HackTheDoc", "big", hue::font);
    link[TWITTER]->place(
        (Window::screen.w - link[TWITTER]->width()) / 2,
        offsetY + 8*(Window::fullscreen+1)
    );

    // labels
    label[EMAIL] = new UILabel("hackthedoc@gmail.com", "big", hue::font);
    label[EMAIL]->place(
        (Window::screen.w - label[EMAIL]->width()) / 2,
        offsetY + label[EMAIL]->height() + 24*(Window::fullscreen+1)
    );

    label[SOCIALS] = new UILabel("Socials:", "big bold", hue::font);
    label[SOCIALS]->place(
        (Window::screen.w - label[SOCIALS]->width()) / 2,
        offsetY - link[DISCORD]->height() - link[GITHUB]->height() - label[SOCIALS]->height() - 40*(Window::fullscreen+1)
    );

    // quit button
    quitButton = new UIButton("X", Event::ID::QUIT_CREDITS, "h3", hue::white);
    quitButton->place(
        Window::screen.w - quitButton->width() - 8*(Window::fullscreen+1),
        8*(Window::fullscreen+1)
    );
}

void Credits::update() {
    link[DISCORD]->update();
    link[TWITTER]->update();
    link[GITHUB]->update();

    quitButton->update();
}

void Credits::render() {
    Manager::DrawFilledRect(&Window::screen, hue::ui);

    link[DISCORD]->draw();
    link[TWITTER]->draw();
    link[GITHUB]->draw();

    label[TITLE]->draw();
    label[AUTHOR]->draw();
    label[SOCIALS]->draw();
    label[EMAIL]->draw();

    quitButton->draw();
}

void Credits::clean() {
    link[DISCORD]->destroy();
    link[TWITTER]->destroy();
    link[GITHUB]->destroy();

    label[TITLE]->destroy();
    label[AUTHOR]->destroy();
    label[SOCIALS]->destroy();
    label[EMAIL]->destroy();

    quitButton->destroy();
}
