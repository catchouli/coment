#include <catch.hpp>

#include <coment/World.h>
#include <coment/managers/EntityManager.h>
#include <coment/managers/ComponentManager.h>

#include "tests/manager_tests/Managers.h"

using namespace coment;

SCENARIO("a manager is added to the world", "[manager]")
{
    World world;
    EntityManager* em = world.getManager<EntityManager>();
    CallbackTestManager* mgr = world.addManager<CallbackTestManager>();

    THEN("callbacks should not have been called yet")
    {
        REQUIRE(mgr->onEntityAddedCalls == 0);
        REQUIRE(mgr->onEntityRemovedCalls == 0);
        REQUIRE(mgr->preUpdateCalls == 0);
        REQUIRE(mgr->postUpdateCalls == 0);
    }

    WHEN("an update is performed")
    {
        world.update();

        THEN("preUpdate and postUpdate should have been called once")
        {
            REQUIRE(mgr->onEntityAddedCalls == 0);
            REQUIRE(mgr->onEntityRemovedCalls == 0);
            REQUIRE(mgr->preUpdateCalls == 1);
            REQUIRE(mgr->postUpdateCalls == 1);
        }
    }

    WHEN("an entity is added to the world")
    {
        Entity e = em->createEntity();

        THEN("onEntityAdded should have been called once and onEntityRemoved 0 times")
        {
            REQUIRE(mgr->onEntityAddedCalls == 1);
            REQUIRE(mgr->onEntityRemovedCalls == 0);
        }

        WHEN("another entity is added to the world")
        {
            em->createEntity();

            THEN("onEntityAdded should have been called twice and onEntityRemoved 0 times")
            {
                REQUIRE(mgr->onEntityAddedCalls == 2);
                REQUIRE(mgr->onEntityRemovedCalls == 0);
            }
        }

        WHEN("an entity is removed from the world")
        {
            em->destroyEntity(e);
            world.update(); // allow for delayed destruction

            THEN("onEntityAdded should have been called once and onEntityRemoved 0 times")
            {
                REQUIRE(mgr->onEntityAddedCalls == 1);
                REQUIRE(mgr->onEntityRemovedCalls == 1);
            }
        }
    }
}