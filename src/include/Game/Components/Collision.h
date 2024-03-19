#pragma once

#include <SDL2/SDL.h>

#include "Collider.h"
class Tile;

namespace Collision {
    bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
    bool AABB(const Collider* colA, const Collider* colB);
};
