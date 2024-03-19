#pragma once

#include <map>
#include <string>
#include <chrono>

#include "Entities/Entities.h"
#include "Map.h"

class Game {
public:
    static Map* map;
    static SDL_Rect camera;
    static Player* player;

    Game();
    ~Game();

    void init();
    void update();
    void render();
    void clean();

private:
    // nothing for now
};
