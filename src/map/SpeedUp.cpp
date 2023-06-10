#include "SpeedUp.h"

SpeedUp::SpeedUp(Point point) : PowerUp(NO_ARMOR, point) {}

ResourceType SpeedUp::getResourceType() const { return ResourceType::SPEED_UP; }
