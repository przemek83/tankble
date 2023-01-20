#include "LifeUp.h"

LifeUp::LifeUp(unsigned int x, unsigned int y) : PowerUp(NO_ARMOR, x, y) {}

ResourceType LifeUp::getResourceType() const { return ResourceType::LIFE_UP; }
