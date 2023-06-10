#include "LifeUp.h"

LifeUp::LifeUp(Point point) : PowerUp(NO_ARMOR, point) {}

ResourceType LifeUp::getResourceType() const { return ResourceType::LIFE_UP; }
