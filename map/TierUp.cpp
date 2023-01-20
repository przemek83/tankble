#include "TierUp.h"

TierUp::TierUp(unsigned int x, unsigned int y) : PowerUp(NO_ARMOR, x, y) {}

ResourceType TierUp::getResourceType() const { return ResourceType::TIER_UP; }
