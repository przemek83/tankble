#include "Plain.h"

#include <iostream>

Plain::Plain()
{
    id_ = Type::PLAIN;
    source_ = "image/board/plain.tga";
    if (!loadBitmap())
        exit(0);
}

bool Plain::canFly() { return true; }

bool Plain::canDrive() { return true; }
