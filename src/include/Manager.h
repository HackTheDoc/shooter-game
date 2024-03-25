#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "hue.h"

#include "States/WindowState.h"

enum class Orientation {
    NORTH,
    WEST,
    EAST,
    SOUTH
};

class Manager {
public:
    Manager();
    ~Manager();

    static SDL_Color SetRenderDrawColor(const SDL_Color& c);

    static void SetViewport(const SDL_Rect* v);

    /* ---------- FONT MANAGER ---------- */

    TTF_Font* getFont(const std::string& id);

    void reloadFonts();

    /* ---------- TEXTURE MANAGER ----------*/

    SDL_Texture* getTexture(const std::string& id);

    static SDL_Texture* LoadTexture(const char* filepath);
    
    static SDL_Texture* GenerateText(const std::string& text, const std::string& font, const SDL_Color& color, const int length = INT16_MAX, const bool centered = false);

    static void Draw(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest);

    static void Draw(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest, const Orientation orientation);

    static void DrawRect(const SDL_Rect* rect, const SDL_Color& color);

    static void DrawFilledRect(const SDL_Rect* rect, const SDL_Color& color);

    static void DrawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Color& color);

    /* ----- WINDOW STATES ----- */

    void addWindowState(const WindowState::ID id, WindowState* ws);

    void removeWindowState(const WindowState::ID id);

    void setCurrentWindowState(const WindowState::ID id);
    
    void updateCurrentWindowState();
    
    void renderCurrentWindowState();

    WindowState::ID getCurrentWindowStateID();

private:
    /* ----- FONTS ----- */

    std::map<std::string, TTF_Font*> fonts;

    void loadFonts();
    void clearFonts();

    /* ----- TEXTURES ----- */

    std::map<std::string, SDL_Texture*> textures;

    static SDL_Texture* GenerateLeftAnchoredText(const std::string& text, const std::string& font, const SDL_Color& color, const int length);
    static SDL_Texture* GenerateCenterAnchoredText(const std::string& text, const std::string& font, const SDL_Color& color, const int length);

    /* ----- WINDOW STATES ----- */

    std::map<WindowState::ID, WindowState*> windowStates;
    WindowState::ID currentWindowState, previousWindowState;
        
    void clearWindowStates();
};
