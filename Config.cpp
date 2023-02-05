#include "Config.h"

#include <random>

Config& Config::getInstance()
{
    static Config instance;
    return instance;
}

unsigned int Config::getRandomSeed()
{
    std::random_device rd;
    return rd();
}
