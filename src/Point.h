#pragma once

struct Point
{
    unsigned int x;
    unsigned int y;
};

inline bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
