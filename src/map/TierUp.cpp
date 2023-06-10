#include "TierUp.h"

TierUp::TierUp(Point point) : PowerUp(NO_ARMOR, point) {}

ResourceType TierUp::getResourceType() const { return ResourceType::TIER_UP; }
