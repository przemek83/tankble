#include "Config.h"

#include <iostream>
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
    speedFactor_ = calculateSpeedFactor();
}

unsigned int Config::getFps() const
{
    switch (fps_)
    {
        case FPS::FPS_30:
            return static_cast<unsigned int>(FPS::FPS_30);

        case FPS::FPS_60:
            return static_cast<unsigned int>(FPS::FPS_60);

        case FPS::FPS_120:
            return static_cast<unsigned int>(FPS::FPS_120);
    }

    return defaultFps_;
}

unsigned int Config::getRandomSeed()
{
    std::random_device rd;
    return rd();
}

void Config::setFPS(FPS fps)
{
    fps_ = fps;
    speedFactor_ = calculateSpeedFactor();
}

Config::Config()
{
    const unsigned int initialBoardSize{tileCount_ * tileSize_};
    screenSizeChanged(initialBoardSize + initialBoardSize / 3,
                      initialBoardSize);
}

float Config::calculateSpeedFactor() const
{
    const float tileSizeFactor{static_cast<float>(tileSize_) /
                               defaultTileSize_};
    const float fpsFactor{static_cast<float>(getFps()) / defaultFps_};
    return 1.F * tileSizeFactor / fpsFactor;
}
