#include "SpeedUp.h"

SpeedUp::SpeedUp(Coordinates coordinates) : PowerUp(NO_ARMOR, coordinates) {}

ResourceType SpeedUp::getResourceType() const { return ResourceType::SPEED_UP; }
