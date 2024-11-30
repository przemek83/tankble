#pragma once

#include <string>

#include <src/Config.h>
#include <src/Point.h>

namespace common
{
const int tileCount{5};

// 0 - plain
// 1 - brick
// 2 - water
// 3 - plant
// 4 - ice
// 5 - steel
// 6 - HQ
// M - my/player tank
// E - enemy tank
// S - speed up
// L - tier up
// A - shield up
// T - life up

inline std::string getTestMap()
{
    return {
        "E01TA\n"
        "01SL1\n"
        "E6010\n"
        "02M31\n"
        "50401\n"};
}

inline Point tileToPoint(int tileX, int tileY)
{
    static const int tileSize{Config::getInstance().getTileSize()};
    return {tileX * tileSize, tileY * tileSize};
}

const int testHitStrength{10};
};  // namespace common
