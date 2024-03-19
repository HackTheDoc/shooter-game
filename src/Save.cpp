#include "include/Save.h"

#include "include/KeyMap.h"

#include <fstream>
#include <iostream>

void Save::Create() {
    const std::map<SDL_KeyCode, Event::ID> controls{
        {SDLK_z     , Event::ID::MOVE_UP    },
        {SDLK_s     , Event::ID::MOVE_DOWN  },
        {SDLK_q     , Event::ID::MOVE_LEFT  },
        {SDLK_d     , Event::ID::MOVE_RIGHT },

        {SDLK_SPACE , Event::ID::SHOOT      },
    };

    std::ofstream outfile("data", std::ios::binary);

    const size_t msize = controls.size();
        outfile.write(reinterpret_cast<const char*>(&msize), sizeof(size_t));

    for (const auto& [key, value] : controls) {
        outfile.write(reinterpret_cast<const char*>(&key), sizeof(SDL_KeyCode));
        outfile.write(reinterpret_cast<const char*>(&value), sizeof(Event::ID));
    }
   
    outfile.close();
}

void Save::Update() {
    // nothing to save
}

void Save::Load() {
    std::ifstream infile("data", std::ios::binary);

    size_t msize;
    infile.read(reinterpret_cast<char*>(&msize), sizeof(size_t));

    for (size_t i = 0; i < msize; ++i) {
        SDL_KeyCode key;
        infile.read(reinterpret_cast<char*>(&key), sizeof(SDL_KeyCode));
        Event::ID value;
        infile.read(reinterpret_cast<char*>(&value), sizeof(Event::ID));

        KeyMap::Key[key] = value;
    }

    infile.close();
}
