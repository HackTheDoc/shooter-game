#pragma once

#include "Entity.h"

class Player : public Entity {
public:
    Player();
    ~Player();

    void init() override;
    void update() override;
    void draw() override;
    void kill() override;

    void shoot();
};
