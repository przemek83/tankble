#include <catch2/catch_test_macros.hpp>

#include <src/Config.h>

TEST_CASE("Set element sizes", "[config]")
{
    Config& config{Config::getInstance()};

    SECTION("check initial sizes")
    {
        REQUIRE(config.getBoardHeight() == 600);
        REQUIRE(config.getBoardWidth() == 600);
        REQUIRE(config.getSatusWidth() == 200);
        REQUIRE(config.getTileSize() == 30);
        REQUIRE(config.getBulletSize() == 6);
    }

    SECTION("check updating sizes")
    {
        config.screenSizeChanged(1920, 1080);
        REQUIRE(config.getBoardHeight() == 1080);
        REQUIRE(config.getBoardWidth() == 1080);
        REQUIRE(config.getSatusWidth() == 840);
        REQUIRE(config.getTileSize() == 54);
        REQUIRE(config.getBulletSize() == 10);
    }

    config.screenSizeChanged(800, 600);
}
