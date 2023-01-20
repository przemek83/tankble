#include "TierUp.h"

TierUp::TierUp(Coordinates coordinates) : PowerUp(NO_ARMOR, coordinates) {}

ResourceType TierUp::getResourceType() const { return ResourceType::TIER_UP; }
