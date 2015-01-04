#include <catch.hpp>

#include "coment/util/TypeMap.h"

using namespace coment;

SCENARIO("a map of type -> object is required")
{
    GIVEN("a fresh typemap")
    {
        TypeMap<> typeMap;

        WHEN("it is empty")
        {
            THEN("there should be no elements")
            {
                REQUIRE(typeMap.getVector()->size() == 0);
            }

            THEN("any type should return nullptr")
            {
                REQUIRE(typeMap.get<int>() == NULL);
            }
        }

        WHEN("a type is added")
        {
            int* i = typeMap.add<int>(5);

            THEN("the pointer should not be null and it should be in the vector")
            {
                REQUIRE(i != NULL);
                REQUIRE(typeMap.getVector()->size() == 1);
            }

            WHEN("it is obtained back from the map")
            {
                int* j = typeMap.get<int>();

                THEN("the pointers should be equal and not null")
                {
                    REQUIRE(j != NULL);
                    REQUIRE(i == j);
                }
            }

            WHEN("it is removed from the map")
            {
                typeMap.remove<int>();

                THEN("the returned pointer should be null and it should no longer be in the map")
                {
                    REQUIRE(typeMap.get<int>() == NULL);
                    REQUIRE(typeMap.getVector()->size() == 0);
                }
            }
        }
    }
}