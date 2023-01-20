#include "LifeUp.h"

LifeUp::LifeUp(Coordinates coordinates) : PowerUp(NO_ARMOR, coordinates) {}

ResourceType LifeUp::getResourceType() const { return ResourceType::LIFE_UP; }
