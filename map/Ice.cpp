#include "Ice.h"

#include <iostream>

Ice::Ice()
{
    id_ = Type::ICE;
    source_ = "image/board/ice.tga";
    if (!loadBitmap())
        exit(0);
}

bool Ice::canFly() { return true; }

bool Ice::canDrive() { return true; }
