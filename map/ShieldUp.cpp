#include "ShieldUp.h"

ShieldUp::ShieldUp(Point point) : PowerUp(NO_ARMOR, point) {}

ResourceType ShieldUp::getResourceType() const
{
    return ResourceType::SHIELD_UP;
}
