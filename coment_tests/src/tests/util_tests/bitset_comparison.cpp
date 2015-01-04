#include <catch.hpp>

#include <coment/util/dynamic_bitset.h>

using namespace coment;

SCENARIO("bitmasks need to be compared")
{
    GIVEN("two default bitsets")
    {
        dynamic_bitset<> a;
        dynamic_bitset<> b;

        THEN("they should be equal and produce the same hash")
        {
            auto hash = std::hash<dynamic_bitset<>>();

            REQUIRE(a == b);
            REQUIRE(hash(a) == hash(b));
        }
    }

    GIVEN("two non-equal bitsets")
    {
        dynamic_bitset<> a;
        dynamic_bitset<> b;

        for (int i = 0; i < 52; ++i)
        {
            a.push_back(rand() % 2 == 0);
        }

        b = a;
        b.flip();

        THEN("they should not be equal")
        {
            REQUIRE(a != b);
        }

        THEN("they should produce different hashes [nearly always - but not always]")
        {
            auto hash = std::hash<dynamic_bitset<>>();

            REQUIRE(hash(a) != hash(b));
        }
    }

    GIVEN("two equal bitsets")
    {
        dynamic_bitset<> a;
        dynamic_bitset<> b;

        for (int i = 0; i < 52; ++i)
        {
            a.push_back(rand() % 2 == 0);
        }

        b = a;

        THEN("they should be equal and produce the same hash")
        {
            auto hash = std::hash<dynamic_bitset<>>();

            REQUIRE(a == b);
            REQUIRE(hash(a) == hash(b));
        }
    }

    GIVEN("two non-equal bitsets of differing lengths")
    {
        dynamic_bitset<> a;
        dynamic_bitset<> b;

        for (int i = 0; i < 52; ++i)
        {
            a.push_back(rand() % 2 == 0);
        }

        b = a;
        b.flip();
        b.resize(100);

        THEN("they should not be equal and produce different hashes")
        {
            auto hash = std::hash<dynamic_bitset<>>();

            REQUIRE(a != b);
            REQUIRE(hash(a) != hash(b));
        }
    }

    GIVEN("two non-equal bitsets of differing lengths where the different part is at the end")
    {
        dynamic_bitset<> a;
        dynamic_bitset<> b;

        for (int i = 0; i < 64; ++i)
        {
            a.push_back(rand() % 2 == 0);
        }

        b = a;

        for (int i = 0; i < 64; ++i)
        {
            b.push_back(rand() % 2 == 0);
        }

        THEN("they should not be equal and produce different hashes")
        {
            auto hash = std::hash<dynamic_bitset<>>();

            REQUIRE(a != b);
            REQUIRE(hash(a) != hash(b));
        }
    }

    GIVEN("two equal bitsets of differing lengths")
    {
        dynamic_bitset<> a;
        dynamic_bitset<> b;

        for (int i = 0; i < 52; ++i)
        {
            a.push_back(rand() % 2 == 0);
        }

        b = a;

        b.resize(100);

        THEN("they should be equal and produce the same hash")
        {
            auto hash = std::hash<dynamic_bitset<>>();

            REQUIRE(a == b);
            REQUIRE(hash(a) == hash(b));
        }
    }
}