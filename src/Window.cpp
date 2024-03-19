#include "include/Window.h"

#include "include/Save.h"

#include <iostream>

SDL_Window* Window::window = nullptr;

const std::string Window::Title = "Shooter Game";
bool Window::isRunning = false;

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

    openGame();
    
    isRunning = true;

    return 0;
}

void Window::update() {
    game->update();
}

void Window::render() {
    SDL_RenderClear(renderer);

    game->render();

    SDL_RenderPresent(renderer);
}

void Window::handleEvents() {
    SDL_PollEvent(&event.e);

    switch (event.e.type) {
    case SDL_QUIT:
        isRunning = false;
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

void Window::openGame() {
    if (!fs::exists("data")) Save::Create();
    Save::Load();

    if (game) delete game;
    
    game = new Game();
    game->init();
}

void Window::quitGame() {
    Save::Update();

    game->clean();
    delete game;
    game = nullptr;
}
