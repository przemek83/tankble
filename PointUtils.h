#pragma once

#include "Point.h"

namespace PointUtils
{
Point pointFromSigned(int x, int y);

bool isValidPoint(int x, int y);

bool isValidPoint(int x, int y, unsigned int objectSize);

bool isValidPoint(Point point);
};  // namespace PointUtils
