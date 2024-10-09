#pragma once

struct Point
{
    int x_;
    int y_;

    friend bool operator==(const Point& lhs, const Point& rhs)
    {
        return (lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_);
    }
};
