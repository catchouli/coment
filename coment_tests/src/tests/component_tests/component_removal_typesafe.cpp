#include <catch.hpp>

#include <coment/World.h>

SCENARIO("a component needs to be removed")
{
    GIVEN("we're in the middle of an update")
    {
        struct Position {};
        coment::World world;
        auto positionMapper = world.getEntityMap<Position>();

        // Add some extra position entities to make the collection larger
        for (int i = 0; i < 10; ++i)
        {
            coment::Entity e = world.createEntity();
            e.addComponent<Position>();
        }

        // Create entity
        coment::Entity outer_ent = world.createEntity();
        outer_ent.addComponent<Position>();

        // Add some extra position entities to make the collection larger
        for (int i = 0; i < 10; ++i)
        {
            coment::Entity e = world.createEntity();
            e.addComponent<Position>();
        }

        WHEN("we try and remove a component in the middle")
        {
            for (auto& e : positionMapper)
            {
                if (outer_ent == e)
                    e.removeComponent<Position>();
            }
        }
    }
}