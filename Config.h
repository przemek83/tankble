#pragma once

#include <chrono>

class Config
{
public:
    Config& operator=(const Config& other) = delete;
    Config(const Config& other) = delete;

    Config& operator=(Config&& other) = delete;
    Config(Config&& other) = delete;

    static Config& getInstance();

    void screenSizeChanged(unsigned int newWidth, unsigned int newHeight);

    inline unsigned int getFps() const { return fps_; }
    inline unsigned int getTileCount() const { return tileCount_; }
    inline unsigned int getTileSize() const { return tileSize_; }
    inline unsigned int getBulletSize() const { return bulletSize_; }
    inline unsigned int getBoardWidth() const { return boardWidth_; }
    inline unsigned int getBoardHeight() const { return boardHeight_; }
    inline unsigned int getSatusWidth() const { return statusWidth_; }

    static unsigned int getRandomSeed();

    inline std::chrono::seconds getFireDelay() const { return fireDelay; }

private:
    Config() = default;
    ~Config() = default;

    const unsigned int fps_{30};
    const unsigned int tileCount_{20};
    unsigned int tileSize_{30};
    unsigned int bulletSize_{tileSize_ / 5};
    unsigned int boardWidth_{tileCount_ * tileSize_};
    unsigned int boardHeight_{boardWidth_};
    unsigned int statusWidth_{boardWidth_ / 3};
    const std::chrono::seconds fireDelay{2};
};
