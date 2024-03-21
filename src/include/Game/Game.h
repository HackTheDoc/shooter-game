#pragma once

#include <map>
#include <string>
#include <chrono>

#include "Entities/Entities.h"
#include "Map.h"

#include "../States/WindowState.h"

class Game : public WindowState {
public:
    static Map* map;
    static SDL_Rect camera;
    static Player* player;

    Game();
    ~Game();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    // nothing for now
};
