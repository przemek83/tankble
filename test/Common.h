#pragma once

#include <string>

#include <src/Config.h>
#include <src/Point.h>

namespace common
{
const int tileCount{5};

inline std::string getTestMap()
{
    return {
        "E01TA\n"
        "01SL1\n"
        "E6010\n"
        "0213M\n"
        "50401\n"};
}

inline Point tileToPoint(int tileX, int tileY)
{
    static const int tileSize{Config::getInstance().getTileSize()};
    return {tileX * tileSize, tileY * tileSize};
}

const int testHitStrength{10};
};  // namespace common
