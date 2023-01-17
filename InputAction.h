#pragma once

enum class InputAction : unsigned char
{
    EMPTY = 0,
    TIMER,
    UP_RELEASED,
    DOWN_RELEASED,
    LEFT,
    RIGHT,
    ACCEPT,
    FIRE,
    CLICK,
    MOUSE_MOVE,
    BACK,
    QUIT
};
