#pragma once

#include <string>

#include "Resources.h"

struct ALLEGRO_FONT;
struct ALLEGRO_BITMAP;
struct ALLEGRO_COLOR;

class Screen
{
public:
    explicit Screen(Resources resources);
    ~Screen();

    Screen& operator=(const Screen& other) = delete;
    Screen(const Screen& other) = delete;

    Screen& operator=(Screen&& other) = delete;
    Screen(Screen&& other) = delete;

    static void init();

    void drawText(unsigned int x, unsigned y, const std::string& text) const;

    void drawTextWithBackground(int x, int y, const std::string& text) const;

    void drawBackground(ResourceType resourceType) const;

    void drawScaledSquareBitmap(ResourceType resourceType, unsigned int x,
                                unsigned int y, unsigned int size) const;

    void drawScaledBitmap(ResourceType resourceType, unsigned int x,
                          unsigned int y, unsigned int width,
                          unsigned int height) const;

    void drawScaledBitmapWithRotation(ResourceType resourceType, int x, int y,
                                      int size, int degrees) const;

    static void clearScreenWithBlack();

    int getCenterX() const;

    int getCenterY() const;

    int getBitmapWidth(ResourceType resourceType) const;

    int getBitmapHeight(ResourceType resourceType) const;

    static void refresh();

    static void showMouse();

    static void hideMouse();

    void useFullScreenMode();

    void useWindowedMode();

    int getWidth() const;

    int getHeight() const;

private:
    void updateSize();

    Resources resources_;

    int width_;
    int height_;
    ALLEGRO_FONT* font_;
};
