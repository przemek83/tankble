#pragma once

class Config
{
public:
    Config& operator=(const Config& other) = delete;
    Config(const Config& other) = delete;

    Config& operator=(Config&& other) = delete;
    Config(Config&& other) = delete;

    static Config& getInstance();

    inline unsigned int getFps() const { return fps_; }
    inline unsigned int getTileCount() const { return tileCount_; }
    inline unsigned int getTileSize() const { return tileSize_; }
    inline unsigned int getBulletSize() const { return bulletSize_; }
    inline unsigned int getBoardWidth() const { return boardWidth_; }
    inline unsigned int getBoardHeight() const { return boardHeight_; }
    inline unsigned int getSatusWidth() const { return statusWidth_; }

    static unsigned int getRandomSeed();

private:
    Config() = default;
    ~Config() = default;

    const unsigned int fps_{30};
    const unsigned int tileCount_{20};
    const unsigned int tileSize_{30};
    const unsigned int bulletSize_{tileSize_ / 5};
    const unsigned int boardWidth_{tileCount_ * tileSize_};
    const unsigned int boardHeight_{boardWidth_};
    const unsigned int statusWidth_{boardWidth_ / 3};
};
