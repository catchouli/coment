#include <catch.hpp>

#include <coment/util/dynamic_bitset.h>

using namespace coment;

SCENARIO("bitmask needs to be checked if it's a subset")
{
    GIVEN("two bitsets where one is 0-length")
    {
        dynamic_bitset<> a;
        dynamic_bitset<> b;

        b.resize(32);
        b[31] = true;

        THEN("b should not be a subset of a, a should be a subset of be")
        {
            REQUIRE(a.is_subset_of(b));
            REQUIRE(!b.is_subset_of(a));
        }
    }

    GIVEN("two equal subsets")
    {
        dynamic_bitset<> a;
        dynamic_bitset<> b;

        for (int i = 0; i < 64; ++i)
        {
            a.push_back(rand() % 2 == 0);
        }

        b = a;

        THEN("they should be subsets of each other")
        {
            REQUIRE(a.is_subset_of(b));
            REQUIRE(b.is_subset_of(a));
        }
    }

    GIVEN("two subsets of the same length where one is a subset of the other")
    {
        dynamic_bitset<> a;
        dynamic_bitset<> b;

        for (int i = 0; i < 64; ++i)
        {
            a.push_back(rand() % 2 == 0);
        }

        b = a;

        a[31] = false;
        b[31] = true;

        THEN("they should be subsets of each other")
        {
            REQUIRE(a.is_subset_of(b));
            REQUIRE(!b.is_subset_of(a));
        }
    }
}