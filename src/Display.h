#pragma once

class Display
{
public:
    Display();

    virtual ~Display() = default;

    int getCenterX() const;
    int getCenterY() const;

    int getWidth() const;
    void setWidth(int width);
    int getHeight() const;
    void setHeight(int height);

private:
    int width_;
    int height_;
};