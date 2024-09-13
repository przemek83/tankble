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

    void drawText(int x, int y, const std::string& text) const;

    void drawTextWithBackground(int x, int y, const std::string& text) const;

    void drawBackground(ResourceType resourceType) const;

    void drawScaledSquareBitmap(ResourceType resourceType, int x, int y,
                                int size) const;

    void drawScaledBitmap(ResourceType resourceType, int x, int y, int width,
                          int height) const;

    void drawScaledBitmapWithRotation(ResourceType resourceType, int x, int y,
                                      int size, int degrees) const;

    static void clearScreenWithBlack();

    int getCenterX() const;

    int getCenterY() const;

    int getResourceWidth(ResourceType resourceType) const;

    int getResourceHeight(ResourceType resourceType) const;

    static void refresh();

    static void showMouse();

    static void hideMouse();

    void useFullScreenMode();

    void useWindowedMode();

    int getWidth() const;

    int getHeight() const;

private:
    void updateSize();

    float getBitmapWidth(ALLEGRO_BITMAP* bitmap) const;
    float getBitmapHeight(ALLEGRO_BITMAP* bitmap) const;

    Resources resources_;

    int width_;
    int height_;
    ALLEGRO_FONT* font_;
};
