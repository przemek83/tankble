#pragma once

#include "Point.h"

namespace point_utils
{
Point pointFromSigned(int x, int y);

bool isValidPoint(int x, int y, unsigned int objectSize);

bool isValidPoint(Point point);
};  // namespace point_utils
