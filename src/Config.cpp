#include "Config.h"

#include <random>

Config& Config::getInstance()
{
    static Config instance;
    return instance;
}

void Config::screenSizeChanged(int newWidth, int newHeight)
{
    tileSize_ = newHeight / tileCount_;
    const int tileToBulletRatio{5};
    bulletSize_ = tileSize_ / tileToBulletRatio;
    boardWidth_ = tileCount_ * tileSize_;
    boardHeight_ = boardWidth_;
    statusWidth_ = newWidth - boardWidth_;
    speedFactor_ = calculateSpeedFactor();
}

int Config::getFps() const
{
    switch (fps_)
    {
        case FPS::FPS_30:
            return static_cast<int>(FPS::FPS_30);

        case FPS::FPS_60:
            return static_cast<int>(FPS::FPS_60);

        case FPS::FPS_120:
            return static_cast<int>(FPS::FPS_120);
    }

    return defaultFps_;
}

unsigned long Config::getRandomSeed()
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
    const int initialBoardSize{tileCount_ * tileSize_};
    screenSizeChanged(initialBoardSize + (initialBoardSize / 3),
                      initialBoardSize);
}

float Config::calculateSpeedFactor() const
{
    const float tileSizeFactor{static_cast<float>(tileSize_) /
                               defaultTileSize_};
    const float fpsFactor{static_cast<float>(getFps()) /
                          static_cast<float>(defaultFps_)};
    return tileSizeFactor / fpsFactor;
}
