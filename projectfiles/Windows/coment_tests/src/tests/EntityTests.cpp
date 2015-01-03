#include <catch.hpp>

#include <coment/managers/EntityManager.h>

SCENARIO("entities can be created", "[entity]")
{
    GIVEN("A new entity manager")
    {
        coment::EntityManager em;
    }
}