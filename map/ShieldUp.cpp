#include "ShieldUp.h"

ShieldUp::ShieldUp(Coordinates coordinates) : PowerUp(NO_ARMOR, coordinates) {}

ResourceType ShieldUp::getResourceType() const
{
    return ResourceType::SHIELD_UP;
}
