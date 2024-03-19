#include "include/Manager.h"

#include "include/Window.h"
#include <iostream>

Manager::Manager() {
    // Tiles
    textures["tileset"] = LoadTexture("./assets/tileset.png");

    // Entities 
    textures["soldiers"] = LoadTexture("./assets/soldiers.png");
}

Manager::~Manager() {
    for (auto t : textures)
        SDL_DestroyTexture(t.second);
    textures.clear();
}

SDL_Color Manager::SetRenderDrawColor(const SDL_Color& c) {
    SDL_Color temp;
    SDL_GetRenderDrawColor(Window::renderer, &temp.r, &temp.g, &temp.b, &temp.a);

    SDL_SetRenderDrawColor(Window::renderer, c.r, c.g, c.b, c.a);

    return temp;
}

void Manager::SetViewport(const SDL_Rect* v) {
    SDL_RenderSetViewport(Window::renderer, v);
}

/* ---------- TEXTURE MANAGER ---------- */

SDL_Texture* Manager::getTexture(const std::string& id) {
    if (textures.count(id) == 0)
        return nullptr;
    return textures[id];
}

SDL_Texture* Manager::LoadTexture(const char* filepath) {
    SDL_Surface* tmpSurface = IMG_Load(filepath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    if (texture == nullptr) std::cout << SDL_GetError() << std::endl;

    return texture;
}

void Manager::Draw(SDL_Texture* text, const SDL_Rect* src, const SDL_Rect* dest, const Orientation orientation) {
    if (text == nullptr) return;

    double angle = 0.;

    switch (orientation) {
    case Orientation::WEST:
        angle = 90.;
        break;
    case Orientation::EAST:
        angle = -90.;
        break;
    case Orientation::SOUTH:
        angle = 0.;
        break;
    case Orientation::NORTH:
        angle = 180.;
        break;
    }

    SDL_RenderCopyEx(Window::renderer, text, src, dest, angle, NULL, SDL_FLIP_NONE);
}

void Manager::DrawRect(const SDL_Rect* rect, const SDL_Color& color) {
    SDL_Color temp = SetRenderDrawColor(color);

    SDL_RenderDrawRect(Window::renderer, rect);

    SetRenderDrawColor(temp);
}

void Manager::DrawFilledRect(const SDL_Rect* rect, const SDL_Color& color) {
    SDL_Color temp = SetRenderDrawColor(color);

    SDL_RenderFillRect(Window::renderer, rect);

    SetRenderDrawColor(temp);
}

void Manager::DrawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Color& color) {
    SDL_Color temp = SetRenderDrawColor(color);

    SDL_RenderDrawLine(Window::renderer, x1, y1, x2, y2);

    SetRenderDrawColor(temp);
}
