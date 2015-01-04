#include <catch.hpp>

#include <coment/World.h>
#include <coment/managers/EntityManager.h>
#include <coment/managers/ComponentManager.h>

#include "tests/manager_tests/Managers.h"

using namespace coment;

SCENARIO("managers are added to and obtained from the world", "[manager]")
{
    World world;
    EntityManager* em = world.getManager<EntityManager>();
    ComponentManager* cm = world.getManager<ComponentManager>();

    GIVEN("the default managers")
    {
        THEN("they should not be null")
        {
            REQUIRE(em != NULL);
            REQUIRE(cm != NULL);
        }
    }

    GIVEN("a fresh world")
    {
        WHEN("a manager is added to the world")
        {
            DefaultManager* defMgr =  world.addManager<DefaultManager>();

            THEN("it should have a valid pointer")
            {
                REQUIRE(defMgr != NULL);
            }
        }

        WHEN("a manager is obtained from the world")
        {
            DefaultManager* defMgr = world.addManager<DefaultManager>();
            DefaultManager* defMgr2 = world.getManager<DefaultManager>();

            THEN("it should have the same pointer as is obtained from addManager")
            {
                REQUIRE(defMgr == defMgr2);
            }
        }
    }
}