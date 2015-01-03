#include <catch.hpp>

#include <vector>

SCENARIO("vectors can be sized and resized", "[vector]")
{
    GIVEN("A vector with some items")
    {
        std::vector<int> v(5);

        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() >= 5);

        WHEN("the size is increased")
        {
            v.resize(10);

            THEN("the size and capacity change")
            {
                REQUIRE(v.size() == 10);
                REQUIRE(v.capacity() >= 10);
            }
        }
    }
}