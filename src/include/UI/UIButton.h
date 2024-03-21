#pragma once

#include <string>

#include "UIElement.h"

#include "../hue.h"
#include "../Event.h"

class UIButton : public UIElement {
public:
    enum Type {
        DEFAULT,
        LEFT_CURSOR,
        RIGHT_CURSOR,
        DOUBLE_CURSOR
    };

    UIButton();
    UIButton(const std::string& text, const Event::ID eid, const std::string& font, const SDL_Color& color, const Type type = Type::DEFAULT);

    ~UIButton();

    void draw() override;
    void update() override;
    void destroy() override;

    void setText(const std::string& text, const std::string& font, const SDL_Color& color);

    void setID(const Event::ID eid);

    void place(const int x, const int y);

protected:
    Event::ID eid;
    Type type;

    SDL_Texture* texture;

    bool hovered;
    SDL_Texture* hoveredTexture;
    SDL_Rect hoveredTextureRect;
};
