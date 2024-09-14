#include "Display.h"

#include "Config.h"

Display::Display()
    : width_(Config::getInstance().getBoardWidth() +
             Config::getInstance().getSatusWidth()),
      height_(Config::getInstance().getBoardHeight())
{
}

int Display::getCenterX() const { return width_ / 2; }
int Display::getCenterY() const { return height_ / 2; }

int Display::getWidth() const { return width_; }
void Display::setWidth(int width) { width_ = width; }
int Display::getHeight() const { return height_; }
void Display::setHeight(int height) { height_ = height; }