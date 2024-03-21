#include "include/Manager.h"

#include "include/Window.h"

#include <sstream>

Manager::Manager() {
    // Tiles
    textures["tileset"] = LoadTexture("./assets/tileset.png");

    // Entities 
    textures["soldiers"] = LoadTexture("./assets/soldiers.png");

    // Fonts
    loadFonts();

    // WindowStates
    currentWindowState = WindowState::ID::UNKNOWN;
    previousWindowState = WindowState::ID::UNKNOWN;
}

Manager::~Manager() {
    for (auto t : textures)
        SDL_DestroyTexture(t.second);
    textures.clear();

    clearFonts();

    clearWindowStates();
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


/* ---------- FONTS ---------- */

TTF_Font* Manager::getFont(const std::string& id) {
    if (fonts.count(id) == 0)
        return fonts["default"];
    return fonts[id];
}

void Manager::loadFonts() {
    if (Window::fullscreen) {
        float sc = (float)Window::screen.w / 1280.0;

        fonts["h1"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 160 * sc);
        fonts["h2"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 120 * sc);
        fonts["h2 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 120 * sc);
        fonts["h3"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 76 * sc);
        fonts["h3 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 76 * sc);
        fonts["h4"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 64 * sc);
        fonts["h4 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 64 * sc);

        fonts["big"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 48 * sc);
        fonts["big bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 48 * sc);
        fonts["default"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 32 * sc);
        fonts["default bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 32 * sc);
        fonts["small"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 16 * sc);
    }
    else {
        fonts["h1"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 160);
        fonts["h2"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 120);
        fonts["h2 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 120);
        fonts["h3"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 76);
        fonts["h3 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 76);
        fonts["h4"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 64);
        fonts["h4 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 64);

        fonts["big"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 48);
        fonts["big bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 48);
        fonts["default"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 32);
        fonts["default bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 32);
        fonts["small"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 16);
    }
}

void Manager::clearFonts() {
    for (auto f : fonts)
        TTF_CloseFont(f.second);
    fonts.clear();
}

void Manager::reloadFonts() {
    clearFonts();
    loadFonts();
}

/* ---------- TEXTURES ---------- */

SDL_Texture* Manager::getTexture(const std::string& id) {
    if (textures.count(id) == 0)
        return nullptr;
    return textures[id];
}

SDL_Texture* Manager::LoadTexture(const char* filepath) {
    SDL_Surface* tmpSurface = IMG_Load(filepath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}

SDL_Texture* Manager::GenerateText(const std::string& text, const std::string& font, const SDL_Color& color, const int length, const bool centered) {
    if (text.empty())
        return nullptr;

    if (centered)
        return GenerateCenterAnchoredText(text, font, color, length);

    return GenerateLeftAnchoredText(text, font, color, length);
}

SDL_Texture* Manager::GenerateLeftAnchoredText(const std::string& text, const std::string& font, const SDL_Color& color, const int length) {
    SDL_Surface* tmpSurface = TTF_RenderUTF8_Blended_Wrapped(Window::manager->getFont(font), text.c_str(), color, length);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}

SDL_Texture* Manager::GenerateCenterAnchoredText(const std::string& text, const std::string& font, const SDL_Color& color, const int length) {
    TTF_Font* ffont = Window::manager->getFont(font);

    // add new line where needed
    const int fontHeight = TTF_FontHeight(ffont);
    int spaceWidth;
    TTF_GlyphMetrics(ffont, ' ', nullptr, nullptr, nullptr, nullptr, &spaceWidth);

    int totalWidth = 0;
    int totalHeight = 0;
    int currWidth = 0;
    std::stringstream ss;

    std::stringstream rawss(text);
    std::string l;
    while (std::getline(rawss, l, '\n')) {
        std::stringstream lss(l);
        std::string w;
        while (std::getline(lss, w, ' ')) {
            currWidth += spaceWidth;

            int wordWidth;
            TTF_SizeText(ffont, w.c_str(), &wordWidth, nullptr);

            if (currWidth + wordWidth > length) {
                totalWidth = std::max(totalWidth, currWidth);
                totalHeight += fontHeight;
                ss << '\n';
                currWidth = 0;
            }

            ss << w << ' ';
            currWidth += wordWidth;
        }
        ss << '\n';
    }

    if (currWidth > 0) totalHeight += fontHeight;

    // generate the actual surface
    SDL_Surface* tmpSurface = SDL_CreateRGBSurfaceWithFormat(0, totalWidth, totalHeight, 32, SDL_PIXELFORMAT_RGBA8888);
    if (tmpSurface == nullptr) return nullptr;
    SDL_SetSurfaceBlendMode(tmpSurface, SDL_BLENDMODE_BLEND);

    int currY = 0;
    ss.clear();
    ss.seekg(0);

    while (std::getline(ss, l, '\n')) {
        SDL_Surface* lSurface = TTF_RenderUTF8_Blended(ffont, l.c_str(), color);
        if (lSurface == nullptr) continue;

        SDL_Rect r = { (tmpSurface->w - lSurface->w) / 2, currY, lSurface->w, lSurface->h };
        SDL_UpperBlitScaled(lSurface, nullptr, tmpSurface, &r);

        SDL_FreeSurface(lSurface);

        currY += lSurface->h;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}

void Manager::Draw(SDL_Texture* text, const SDL_Rect* src, const SDL_Rect* dest) {
    if (text == nullptr) return;

    SDL_RenderCopy(Window::renderer, text, src, dest);
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

/* ---------- WINDOW STATES ---------- */

void Manager::addWindowState(const WindowState::ID id, WindowState* ws) {
    if (id == WindowState::ID::MAIN) clearWindowStates();

    windowStates.emplace(id, ws);
    windowStates[id]->init();
}

void Manager::removeWindowState(const WindowState::ID id) {
    if (windowStates.count(id) == 0)
        return

        windowStates[id]->clean();
    windowStates.erase(id);
    currentWindowState = previousWindowState;
}

void Manager::setCurrentWindowState(const WindowState::ID id) {
    previousWindowState = currentWindowState;
    currentWindowState = id;
}

void Manager::updateCurrentWindowState() {
    windowStates[currentWindowState]->update();
}

void Manager::renderCurrentWindowState() {
    if (currentWindowState > WindowState::ID::GAME)
        windowStates[WindowState::ID::GAME]->render();
    windowStates[currentWindowState]->render();
}

void Manager::clearWindowStates() {
    for (auto ws : windowStates) {
        ws.second->clean();
    }
    windowStates.clear();

    previousWindowState = WindowState::ID::UNKNOWN;
    currentWindowState = WindowState::ID::UNKNOWN;
}
