#include <catch2/catch_test_macros.hpp>

#include <src/Status.h>

TEST_CASE("Status usage", "[Status]")
{
    Status status{{100, 100}};
    SECTION("Check resource type")
    {
        REQUIRE(status.getResourceType() == ResourceType::BACKGROUND);
    }

    SECTION("Check center")
    {
        Point center{status.getCenter()};
        REQUIRE(center == Point{200, 300});
    }
}
