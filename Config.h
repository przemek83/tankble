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
    inline unsigned int getMapSize() const { return mapSize_; }
    inline unsigned int getElementSize() const { return elementSize_; }
    inline unsigned int getBulletSize() const { return bulletSize_; }
    inline unsigned int getBoardWidth() const { return boardWidth_; }
    inline unsigned int getBoardHeight() const { return boardHeight_; }
    inline unsigned int getSatusWidth() const { return statusWidth_; }

private:
    Config() = default;
    ~Config() = default;

    const unsigned int fps_{30};
    const unsigned int mapSize_{20};
    const unsigned int elementSize_{30};
    const unsigned int bulletSize_{elementSize_ / 5};
    const unsigned int boardWidth_{800};
    const unsigned int boardHeight_{600};
    const unsigned int statusWidth_{200};
};
