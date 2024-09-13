#include "PowerUp.h"

PowerUp::PowerUp(int armor, Point point) : Tile(armor, point) {}

bool PowerUp::canFly() { return true; }

bool PowerUp::canDrive() { return true; }
