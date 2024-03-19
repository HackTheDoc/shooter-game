#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "hue.h"

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

    /* ---------- TEXTURE MANAGER ----------*/

    /// @brief parse a loaded texture
    /// @param id id of the texture
    /// @return nullptr if texture not founded
    SDL_Texture* getTexture(const std::string& id);

    /// @brief Load an existing texture
    /// @param filepath path to the texture to load
    /// @return the loaded texture or a null pointer
    static SDL_Texture* LoadTexture(const char* filepath);
    
    /// @brief Draw a texture on the window
    /// @param texture texture to draw
    /// @param src source rectangle on the texture
    /// @param dest destination rectangle on the window
    /// @param flip flip mode (default: none)
    static void Draw(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest, const Orientation orientation = Orientation::SOUTH);

    /// @brief Draw a rectangle on the window
    /// @param rect rectangle to draw
    /// @param color color of the rectangle
    static void DrawRect(const SDL_Rect* rect, const SDL_Color& color);

    /// @brief Draw a filled rectangle on the window
    /// @param rect rectangle to draw
    /// @param color color of the rectangle
    static void DrawFilledRect(const SDL_Rect* rect, const SDL_Color& color);

    /// @brief Draw a line on the window
    /// @param x1 pos in pixel
    /// @param y1 pos in pixel
    /// @param x2 pos in pixel
    /// @param y2 pos in pixel
    /// @param color color of the rectangle
    static void DrawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Color& color);

private:
    std::map<std::string, SDL_Texture*> textures;
};
