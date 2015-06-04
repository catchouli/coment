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

        WHEN("a default manager is added to the world")
        {
            EntityManager* newEm = world.addManager<EntityManager>(&world);
            ComponentManager* newCm = world.addManager<ComponentManager>();

            THEN("it should have a new pointer and the world should return a the new pointer")
            {
                REQUIRE(newEm == world.getManager<EntityManager>());
                REQUIRE(newCm == world.getManager<ComponentManager>());
            }
        }
    }

    GIVEN("a fresh world")
    {
        WHEN("a manager is added to the world")
        {
            DefaultManager* defMgr = world.addManager<DefaultManager>();

            THEN("it should have a valid pointer")
            {
                REQUIRE(defMgr != NULL);
            }
        }

        WHEN("a manager is added to the world")
        {
            struct TestManager
                : public coment::Manager<TestManager>
            {
                TestManager(coment::World* rightWorld)
                {
                    REQUIRE(rightWorld == getWorld());
                }
            };

            world.addManager<TestManager>(&world);
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