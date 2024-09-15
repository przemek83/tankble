#include "Display.h"

#include "Config.h"
#include "Utils.h"

Display::Display()
    : width_(Config::getInstance().getBoardWidth() +
             Config::getInstance().getSatusWidth()),
      height_(Config::getInstance().getBoardHeight())
{
}

int Display::getCenterX() const { return utils::getMidpoint(width_); }
int Display::getCenterY() const { return utils::getMidpoint(height_); }

int Display::getWidth() const { return width_; }
void Display::setWidth(int width) { width_ = width; }
int Display::getHeight() const { return height_; }
void Display::setHeight(int height) { height_ = height; }
