#pragma once

#include <filesystem>
#include <SDL2/SDL.h>

namespace fs = std::filesystem;

class Save {
public:
    static void Create();
    static void Update();
    static void Load();
};
