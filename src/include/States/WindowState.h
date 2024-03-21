#pragma once

class WindowState {
public:
    enum ID {
        UNKNOWN,
        MAIN,

        OPTIONS_MENU,
        
        CREDITS,
        
        GAME,
        PAUSE_MENU,
        DEATH_MENU
    };

    WindowState() {}
    ~WindowState() {}

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}
    virtual void clean() {}

    virtual void reload() {}

};
