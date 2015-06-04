#include <catch.hpp>

#include <coment/World.h>
#include <coment/managers/EntityManager.h>
#include <coment/managers/ComponentManager.h>

#include "tests/system_tests/CallbackTestSystem.h"

using namespace coment;

SCENARIO("a system is added to the world", "[manager]")
{
    World world;
    EntityManager* em = world.getManager<EntityManager>();
    CallbackTestSystem* system = world.addSystem<CallbackTestSystem>();

    THEN("callbacks should not have been called yet")
    {
        REQUIRE(system->onEntityAddedCalls == 0);
        REQUIRE(system->onEntityRemovedCalls == 0);
        REQUIRE(system->preUpdateCalls == 0);
        REQUIRE(system->onUpdateCalls == 0);
        REQUIRE(system->postUpdateCalls == 0);
    }

    WHEN("an update is performed")
    {
        world.update();

        THEN("preUpdate and postUpdate should have been called once")
        {
            REQUIRE(system->onEntityAddedCalls == 0);
            REQUIRE(system->onEntityRemovedCalls == 0);
            REQUIRE(system->preUpdateCalls == 1);
            REQUIRE(system->onUpdateCalls == 1);
            REQUIRE(system->postUpdateCalls == 1);
        }
    }

    WHEN("an entity is added to the world")
    {
        Entity e = em->createEntity();

        THEN("onEntityAdded should have been called once and onEntityRemoved 0 times")
        {
            REQUIRE(system->onEntityAddedCalls == 1);
            REQUIRE(system->onEntityRemovedCalls == 0);
        }

        WHEN("another entity is added to the world")
        {
            em->createEntity();

            THEN("onEntityAdded should have been called twice and onEntityRemoved 0 times")
            {
                REQUIRE(system->onEntityAddedCalls == 2);
                REQUIRE(system->onEntityRemovedCalls == 0);
            }
        }

        WHEN("an entity is removed from the world")
        {
            em->destroyEntity(e);
            world.update(); // allow for delayed destruction

            THEN("onEntityAdded should have been called once and onEntityRemoved 0 times")
            {
                REQUIRE(system->onEntityAddedCalls == 1);
                REQUIRE(system->onEntityRemovedCalls == 1);
            }
        }

        WHEN("a system's constructor runs")
        {
            THEN("getWorld() should be valid")
            {
                struct MySystem
                    : public coment::System<MySystem>
                {
                public:

                    MySystem(coment::World* rightWorld)
                    {
                        auto* world = getWorld();

                        REQUIRE(world == rightWorld);
                    }
                };

                world.addSystem<MySystem>(&world);
            }
        }
    }
}