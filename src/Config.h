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

    unsigned int getFps() const;
    unsigned int getTileCount() const { return tileCount_; }
    int getTileSize() const { return tileSize_; }
    unsigned int getBulletSize() const { return bulletSize_; }
    int getBoardWidth() const { return boardWidth_; }
    int getBoardHeight() const { return boardHeight_; }
    int getSatusWidth() const { return statusWidth_; }
    float getSpeedFactor() const { return speedFactor_; }

    static unsigned int getRandomSeed();

    std::chrono::seconds getFireDelay() const { return fireDelay_; }

    enum class FPS : char
    {
        FPS_30 = 30,
        FPS_60 = 60,
        FPS_120 = 120
    };

    void setFPS(FPS fps);

private:
    Config();
    ~Config() = default;

    float calculateSpeedFactor() const;

    FPS fps_{FPS::FPS_60};
    const unsigned int defaultFps_{static_cast<unsigned int>(FPS::FPS_30)};
    const unsigned int tileCount_{20};
    static constexpr unsigned int defaultTileSize_{30};
    int tileSize_{defaultTileSize_};
    unsigned int bulletSize_{};
    int boardWidth_{};
    int boardHeight_{};
    int statusWidth_{};
    float speedFactor_{};
    const std::chrono::seconds fireDelay_{2};
};
