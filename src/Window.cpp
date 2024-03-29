#include "include/Window.h"

#include "include/States/WindowStates.h"
#include "include/Save.h"

#include <iostream>

SDL_Window* Window::window = nullptr;

const std::string Window::Title = "Shooter Game";
bool Window::isRunning = false;
bool Window::fullscreen = false;

SDL_Renderer* Window::renderer = nullptr;
SDL_Rect Window::screen = { 0, 0, 1280, 720 };

Manager* Window::manager = nullptr;
Event Window::event;

Window::Window() {}

Window::~Window() {}

int Window::init() {
    // init sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return -1;

    if (IMG_Init(IMG_INIT_PNG) == 0)
        return -1;

    if (TTF_Init() != 0)
        return -1;

    // init window
    window = SDL_CreateWindow(
        Title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen.w,
        screen.h,
        SDL_WINDOW_SHOWN
    );
    if (!window)
        return -2;

    // init renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        return -3;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    Manager::SetRenderDrawColor(hue::ui);

    // init components

    manager = new Manager();

    openMainMenu();
    
    isRunning = true;

    return 0;
}

void Window::update() {
    manager->updateCurrentWindowState();
}

void Window::render() {
    SDL_RenderClear(renderer);

    manager->renderCurrentWindowState();

    SDL_RenderPresent(renderer);
}

void Window::handleEvents() {
    SDL_PollEvent(&event.e);

    switch (event.e.type) {
    case SDL_QUIT:
        event.raise(Event::ID::QUIT);
        break;
    default:
        event.handleKeyboardInputs();
        break;
    }
}

void Window::kill() {
    delete manager;
    manager = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Window::openMainMenu() {
    manager->addWindowState(WindowState::ID::MAIN, new MainMenu());
    manager->setCurrentWindowState(WindowState::ID::MAIN);
}

void Window::openCredits() {
    manager->addWindowState(WindowState::ID::CREDITS, new Credits());
    manager->setCurrentWindowState(WindowState::ID::CREDITS);
}

void Window::openGame() {
    if (!fs::exists("data")) Save::Create();
    Save::Load();

    manager->removeWindowState(WindowState::ID::MAIN);
    manager->addWindowState(WindowState::ID::GAME, new Game());
    manager->setCurrentWindowState(WindowState::ID::GAME);
}

void Window::quitGame() {
    Save::Update();

    openMainMenu();
}

void Window::pauseGame() {
    manager->addWindowState(WindowState::ID::PAUSE_MENU, new PauseMenu());
    manager->setCurrentWindowState(WindowState::ID::PAUSE_MENU);
}

void Window::resumeGame() {
    manager->setCurrentWindowState(WindowState::ID::GAME);
}
