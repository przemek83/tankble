#pragma once

#include <chrono>

class Config
{
public:
    Config(const Config& other) = delete;
    Config(Config&& other) = delete;

    Config& operator=(const Config& other) = delete;
    Config& operator=(Config&& other) = delete;

    static Config& getInstance();

    void screenSizeChanged(int newWidth, int newHeight);

    int getFps() const;
    int getTileCount() const { return tileCount_; }
    int getTileSize() const { return tileSize_; }
    int getBulletSize() const { return bulletSize_; }
    int getBoardWidth() const { return boardWidth_; }
    int getBoardHeight() const { return boardHeight_; }
    int getSatusWidth() const { return statusWidth_; }
    float getSpeedFactor() const { return speedFactor_; }

    static unsigned long getRandomSeed();

    std::chrono::seconds getFireDelay() const { return fireDelay_; }

    enum class FPS : int
    {
        FPS_30 = 30,
        FPS_60 = 60,
        FPS_120 = 120
    };

    void setFPS(FPS fps);

    int getDefaultSleepTimeInSeconds() const
    {
        return defaultSleepTimeInSeconds_;
    }

    void setDefaultSleepTimeInSeconds(int seconds)
    {
        defaultSleepTimeInSeconds_ = seconds;
    }

private:
    Config();
    ~Config() = default;

    float calculateSpeedFactor() const;

    FPS fps_{FPS::FPS_60};
    const int defaultFps_{static_cast<int>(FPS::FPS_30)};
    const int tileCount_{20};
    static constexpr int defaultTileSize_{30};
    int tileSize_{defaultTileSize_};
    int bulletSize_{0};
    int boardWidth_{0};
    int boardHeight_{0};
    int statusWidth_{0};
    float speedFactor_{0};
    const std::chrono::seconds fireDelay_{2};

    int defaultSleepTimeInSeconds_{2};
};
