#include "Config.h"

Config& Config::getInstance()
{
    static Config instance;
    return instance;
}
