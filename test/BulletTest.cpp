#include <catch2/catch_test_macros.hpp>

#include "Bullet.h"
#include "Direction.h"
#include "TankType.h"

const unsigned int bulletPower{4};
const unsigned int bulletSpeed{10};
const Point point{10, 10};

static Bullet getExampleBullet()
{
    return {point, bulletSpeed, TankType::ENEMY_TIER_1, bulletPower,
            Direction::UP};
}

TEST_CASE("Bullet power")
{
    const Bullet bullet{getExampleBullet()};
    REQUIRE(bullet.getPower() == bulletPower);
}
