#pragma once

#include <string>

#include "Display.h"
#include "Resources.h"

struct ALLEGRO_FONT;
struct ALLEGRO_BITMAP;
struct ALLEGRO_COLOR;

class Screen : public Display
{
public:
    explicit Screen(Resources resources);
    ~Screen() override;

    static void init();

    void drawText(int x, int y, const std::string& text) const override;

    void drawTextWithBackground(int x, int y,
                                const std::string& text) const override;

    void drawBackground(ResourceType resourceType) const override;

    void drawScaledBitmap(ResourceType resourceType, int x, int y, int width,
                          int height) const override;

    void drawScaledBitmapWithRotation(ResourceType resourceType, int x, int y,
                                      int size, int degrees) const override;

    static void clearScreenWithBlack();

    int getResourceWidth(ResourceType resourceType) const override;

    int getResourceHeight(ResourceType resourceType) const override;

    static void refresh();

    static void showMouse();

    static void hideMouse();

    void useFullScreenMode() override;

    void useWindowedMode() override;

private:
    void updateSize();

    float getBitmapWidth(ALLEGRO_BITMAP* bitmap) const;
    float getBitmapHeight(ALLEGRO_BITMAP* bitmap) const;

    Resources resources_;
    ALLEGRO_FONT* font_;
};
