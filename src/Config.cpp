#include "Config.h"

#include <random>

Config& Config::getInstance()
{
    static Config instance;
    return instance;
}

void Config::screenSizeChanged(unsigned int newWidth, unsigned int newHeight)
{
    tileSize_ = newHeight / tileCount_;
    bulletSize_ = tileSize_ / 5;
    boardWidth_ = tileCount_ * tileSize_;
    boardHeight_ = boardWidth_;
    statusWidth_ = newWidth - boardWidth_;
    speedFactor_ =
        1.F * sqrt(static_cast<float>(defaultFps_) / static_cast<float>(fps_)) *
        (static_cast<float>(tileSize_) / defaultTileSize_);
}

unsigned int Config::getRandomSeed()
{
    std::random_device rd;
    return rd();
}

Config::Config()
{
    const unsigned int initialBoardSize{tileCount_ * tileSize_};
    screenSizeChanged(initialBoardSize + initialBoardSize / 3,
                      initialBoardSize);
}
