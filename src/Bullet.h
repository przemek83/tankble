#pragma once

#include "Drawable.h"

enum class ResourceType : unsigned char;
enum class Direction : unsigned char;
enum class TankType : unsigned char;
class Tank;

class Bullet : public Drawable
{
public:
    Bullet(Point startingPoint, int speed, bool playerOrigin, int power,
           Direction direction);

    bool isPlayerOrigin() const;
    int getPower() const;

    bool move();

    void draw(const Screen& screen) const override;
    ResourceType getResourceType() const override;
    Point getCenter() const override;

private:
    int getDirectionX() const;
    int getDirectionY() const;

    const int size_;
    const bool playerOrigin_;
    const Direction direction_;
    const int speed_;
    const int power_;
};
