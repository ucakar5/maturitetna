#include <iostream>
#include <SDL2/SDL.h>

class Mouse {
    int lastX, lastY;
    Uint32 lastButtons = 0;
    bool zabelezi(bool r);

public:
    int x, y;
    bool left = false, right = false;
    Uint32 buttons = 0;

    bool update(bool &but);
};

#include <mouse.cpp>