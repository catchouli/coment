#include <catch.hpp>

#include <coment/World.h>
#include <coment/managers/EntityManager.h>

using namespace coment;

SCENARIO("entities are created", "[entity]")
{
    GIVEN("a new entity world")
    {
        // Create world and get entity manager
        World world;
        EntityManager& em = *world.getManager<EntityManager>();

        WHEN("an entity is not initialised")
        {
            Entity a;

            THEN("it should report as uninitialised")
            {
                REQUIRE(a.isInitialised() == false);
            }
        }

        WHEN("entities are created")
        {
            Entity a = em.createEntity();
            Entity b = em.createEntity();

            THEN("they should report as initialised")
            {
                REQUIRE(a.isInitialised() == true);
                REQUIRE(b.isInitialised() == true);
            }

            THEN("their IDs and unique IDs should be different")
            {
                REQUIRE(a.getId() != b.getId());
                REQUIRE(a.getUniqueId() != b.getUniqueId());
            }
        }

        WHEN("an entity is destroyed")
        {
            Entity a = em.createEntity();

            // Destroy it an entity
            em.destroyEntity(a);

            THEN("its IDs should be -1 to signify uninitialised")
            {
                REQUIRE(a.isInitialised() == false);
                REQUIRE(a.getId() == -1);
                REQUIRE(a.getUniqueId() == -1);
            }
        }

        WHEN("an entity is recycled")
        {
            Entity a = em.createEntity();

            // Store old entity Ids
            EntityId oldId = a.getId();
            EntityId oldUniqueId = a.getUniqueId();

            // Destroy the entity, and perform an update so that delayed destruction can take place
            em.destroyEntity(a);
            world.update();

            // Create a new entity
            Entity b = em.createEntity();

            THEN("the original entity should report as uninitialised and the new one as initialised")
            {
                REQUIRE(a.isInitialised() == false);
                REQUIRE(b.isInitialised() == true);
            }

            THEN("it should have a recycled common ID but a new unique ID")
            {
                REQUIRE(b.getId() == oldId);
                REQUIRE(b.getUniqueId() != oldUniqueId);
            }
        }
    }
}