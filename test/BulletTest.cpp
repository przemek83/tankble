#include <catch2/catch_test_macros.hpp>

#include "Bullet.h"
#include "Direction.h"
#include "TankType.h"

TEST_CASE("Bullet power")
{
    const unsigned int bulletPower{4};
    const Bullet bullet({10, 10}, 10, TankType::ENEMY_TIER_1, bulletPower,
                        Direction::UP);
    REQUIRE(bullet.getPower() == bulletPower);
}
