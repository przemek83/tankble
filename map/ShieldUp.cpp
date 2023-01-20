#include "ShieldUp.h"

ShieldUp::ShieldUp(unsigned int x, unsigned int y) : PowerUp(NO_ARMOR, x, y) {}

ResourceType ShieldUp::getResourceType() const
{
    return ResourceType::SHIELD_UP;
}
