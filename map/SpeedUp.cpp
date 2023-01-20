#include "SpeedUp.h"

SpeedUp::SpeedUp(unsigned int x, unsigned int y) : PowerUp(NO_ARMOR, x, y) {}

ResourceType SpeedUp::getResourceType() const { return ResourceType::SPEED_UP; }
