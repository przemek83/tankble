#pragma once

#include <string>

#include "Resources.h"

struct ALLEGRO_FONT;
struct ALLEGRO_BITMAP;
struct ALLEGRO_COLOR;

class Screen final
{
public:
    explicit Screen(Resources resources);
    ~Screen();

    Screen& operator=(const Screen& other) = delete;
    Screen(const Screen& other) = delete;

    Screen& operator=(Screen&& other) = delete;
    Screen(Screen&& other) = delete;

    void drawText(unsigned int x, unsigned y, const std::string& text);

    void drawBackground(ResourceType resourceType) const;

    void drawBitmap(ResourceType resourceType, unsigned int x,
                    unsigned int y) const;

    static void clearScreenWithColor(ALLEGRO_COLOR color);

    unsigned int getCenterX() const;

    unsigned int getCenterY() const;

    unsigned int getBitmapWidth(ResourceType resourceType) const;

    unsigned int getBitmapHeight(ResourceType resourceType) const;

    static void refresh() ;

    static void showMouse() ;

    static void hideMouse() ;

    void useFullScreenMode();

    void useWindowedMode();

    const Resources& getResources() const;

private:
    void updateSize();

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    std::pair<unsigned int, unsigned int> getCenter() const;

    Resources resources_;

    unsigned int width_;
    unsigned int height_;
    ALLEGRO_FONT* font_;
};
