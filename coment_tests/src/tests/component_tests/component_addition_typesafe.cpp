#include <catch.hpp>

#include <coment/World.h>
#include <coment/managers/EntityManager.h>
#include <coment/managers/ComponentManager.h>

#include <stdexcept>

using namespace coment;

struct Position
{
    float x, y;
};

struct Velocity
{
    float x, y;
};

struct Radius
{
    float x;
};

SCENARIO("components are added to an entity", "[entity][component]")
{
    World world;

    GIVEN("an uninitialised entity")
    {
        Entity e;

        WHEN("a component is added to the entity")
        {
            THEN("there should be an exception")
            {
                REQUIRE_THROWS_AS(e.addComponent<Position>(), std::invalid_argument);
            }
        }
    }

    GIVEN("a dead entity")
    {
        Entity e = world.createEntity();

        // Copy entity so that destroyEntity() doesn't invalidate our e reference
        Entity e2 = e;
        world.destroyEntity(e2);
        world.update(); // Force update so that delayed entity destruction is performed

        WHEN("a component is added to the entity")
        {
            THEN("there should be an exception")
            {
                REQUIRE_THROWS_AS(e.addComponent<Position>(), std::invalid_argument);
            }
        }
    }

    GIVEN("a new entity")
    {
        Entity e = world.createEntity();

        WHEN("a position is added to an entity")
        {
            Position* p = e.addComponent<Position>();

            THEN("the component pointer should not be null")
            {
                REQUIRE(p != NULL);
            }

            THEN("the component should be obtainable from the component manager")
            {
                // Check that the pointer is the same
                REQUIRE(p == e.getComponent<Position>());
            }

            THEN("the entity should not have a velocity component")
            {
                REQUIRE(e.getComponent<Velocity>() == NULL);
            }
        }
    }

    GIVEN("position, velocity, and radius component types")
    {
        Entity e = world.createEntity();

        auto positionMap = world.getEntityMap<Position>();
        auto velocityMap = world.getEntityMap<Velocity>();
        auto radiusMap = world.getEntityMap<Radius>();
        auto moverMap = world.getEntityMap<Position, Velocity>();
        auto circleMap = world.getEntityMap<Position, Radius>();

        WHEN("a position is added to the entity")
        {
            e.addComponent<Position>();

            THEN("e should be in positionMap but no others")
            {
                REQUIRE(positionMap.mEntities->size() == 1);
                REQUIRE(velocityMap.mEntities->size() == 0);
                REQUIRE(radiusMap.mEntities->size() == 0);
                REQUIRE(moverMap.mEntities->size() == 0);
                REQUIRE(circleMap.mEntities->size() == 0);

                REQUIRE(positionMap.mEntities->at(0) == e);

                WHEN("position is removed from the entity")
                {
                    e.removeComponent<Position>();

                    THEN("the entity should not be in any maps")
                    {
                        REQUIRE(positionMap.mEntities->size() == 0);
                        REQUIRE(velocityMap.mEntities->size() == 0);
                        REQUIRE(radiusMap.mEntities->size() == 0);
                        REQUIRE(moverMap.mEntities->size() == 0);
                        REQUIRE(circleMap.mEntities->size() == 0);
                    }
                }
            }
        }

        WHEN("a velocity is added to the entity")
        {
            e.addComponent<Velocity>();

            THEN("e should be in velocityMap but no others")
            {
                REQUIRE(positionMap.mEntities->size() == 0);
                REQUIRE(velocityMap.mEntities->size() == 1);
                REQUIRE(radiusMap.mEntities->size() == 0);
                REQUIRE(moverMap.mEntities->size() == 0);
                REQUIRE(circleMap.mEntities->size() == 0);

                REQUIRE(velocityMap.mEntities->at(0) == e);

                WHEN("velocity is removed from the entity")
                {
                    e.removeComponent<Velocity>();

                    THEN("the entity should not be in any maps")
                    {
                        REQUIRE(positionMap.mEntities->size() == 0);
                        REQUIRE(velocityMap.mEntities->size() == 0);
                        REQUIRE(radiusMap.mEntities->size() == 0);
                        REQUIRE(moverMap.mEntities->size() == 0);
                        REQUIRE(circleMap.mEntities->size() == 0);
                    }
                }
            }
        }

        WHEN("a radius is added to the entity")
        {
            e.addComponent<Radius>();

            THEN("e should be in radiusMap but no others")
            {
                REQUIRE(positionMap.mEntities->size() == 0);
                REQUIRE(velocityMap.mEntities->size() == 0);
                REQUIRE(radiusMap.mEntities->size() == 1);
                REQUIRE(moverMap.mEntities->size() == 0);
                REQUIRE(circleMap.mEntities->size() == 0);

                REQUIRE(radiusMap.mEntities->at(0) == e);

                WHEN("radius is removed from the entity")
                {
                    e.removeComponent<Radius>();

                    THEN("the entity should not be in any maps")
                    {
                        REQUIRE(positionMap.mEntities->size() == 0);
                        REQUIRE(velocityMap.mEntities->size() == 0);
                        REQUIRE(radiusMap.mEntities->size() == 0);
                        REQUIRE(moverMap.mEntities->size() == 0);
                        REQUIRE(circleMap.mEntities->size() == 0);
                    }
                }
            }
        }

        WHEN("a velocity and a radius are added to the entity")
        {
            e.addComponent<Velocity>();
            e.addComponent<Radius>();

            THEN("e should be in velocityMap and radiusMap but no others")
            {
                REQUIRE(positionMap.mEntities->size() == 0);
                REQUIRE(velocityMap.mEntities->size() == 1);
                REQUIRE(radiusMap.mEntities->size() == 1);
                REQUIRE(moverMap.mEntities->size() == 0);
                REQUIRE(circleMap.mEntities->size() == 0);

                REQUIRE(velocityMap.mEntities->at(0) == e);
                REQUIRE(radiusMap.mEntities->at(0) == e);

                WHEN("velocity is removed from the entity")
                {
                    e.removeComponent<Velocity>();

                    THEN("the entity should only be in the radiusMap")
                    {
                        REQUIRE(positionMap.mEntities->size() == 0);
                        REQUIRE(velocityMap.mEntities->size() == 0);
                        REQUIRE(radiusMap.mEntities->size() == 1);
                        REQUIRE(moverMap.mEntities->size() == 0);
                        REQUIRE(circleMap.mEntities->size() == 0);
                    }
                }

                WHEN("radius is removed from the entity")
                {
                    e.removeComponent<Radius>();

                    THEN("the entity should only be in the velocityMap")
                    {
                        REQUIRE(positionMap.mEntities->size() == 0);
                        REQUIRE(velocityMap.mEntities->size() == 1);
                        REQUIRE(radiusMap.mEntities->size() == 0);
                        REQUIRE(moverMap.mEntities->size() == 0);
                        REQUIRE(circleMap.mEntities->size() == 0);
                    }
                }

                WHEN("velocity and radius are removed from the entity")
                {
                    e.removeComponent<Velocity>();
                    e.removeComponent<Radius>();

                    THEN("the entity should not be in any maps")
                    {
                        REQUIRE(positionMap.mEntities->size() == 0);
                        REQUIRE(velocityMap.mEntities->size() == 0);
                        REQUIRE(radiusMap.mEntities->size() == 0);
                        REQUIRE(moverMap.mEntities->size() == 0);
                        REQUIRE(circleMap.mEntities->size() == 0);
                    }
                }
            }
        }

        WHEN("a position and a velocity are added to the entity")
        {
            e.addComponent<Position>();
            e.addComponent<Velocity>();

            THEN("e should be in positionMap, velocityMap and moverMap")
            {
                REQUIRE(positionMap.mEntities->size() == 1);
                REQUIRE(velocityMap.mEntities->size() == 1);
                REQUIRE(radiusMap.mEntities->size() == 0);
                REQUIRE(moverMap.mEntities->size() == 1);
                REQUIRE(circleMap.mEntities->size() == 0);

                REQUIRE(positionMap.mEntities->at(0) == e);
                REQUIRE(velocityMap.mEntities->at(0) == e);
            }

            WHEN("position is removed from the entity")
            {
                e.removeComponent<Position>();

                THEN("the entity should only be in the velocityMap")
                {
                    REQUIRE(positionMap.mEntities->size() == 0);
                    REQUIRE(velocityMap.mEntities->size() == 1);
                    REQUIRE(radiusMap.mEntities->size() == 0);
                    REQUIRE(moverMap.mEntities->size() == 0);
                    REQUIRE(circleMap.mEntities->size() == 0);
                }
            }

            WHEN("velocity is removed from the entity")
            {
                e.removeComponent<Velocity>();

                THEN("the entity should only be in the positionMap")
                {
                    REQUIRE(positionMap.mEntities->size() == 1);
                    REQUIRE(velocityMap.mEntities->size() == 0);
                    REQUIRE(radiusMap.mEntities->size() == 0);
                    REQUIRE(moverMap.mEntities->size() == 0);
                    REQUIRE(circleMap.mEntities->size() == 0);
                }
            }

            WHEN("position and velocity are removed from the entity")
            {
                e.removeComponent<Position>();
                e.removeComponent<Velocity>();

                THEN("the entity should not be in any maps")
                {
                    REQUIRE(positionMap.mEntities->size() == 0);
                    REQUIRE(velocityMap.mEntities->size() == 0);
                    REQUIRE(radiusMap.mEntities->size() == 0);
                    REQUIRE(moverMap.mEntities->size() == 0);
                    REQUIRE(circleMap.mEntities->size() == 0);
                }
            }
        }

        WHEN("a position and a radius are added to the entity")
        {
            e.addComponent<Position>();
            e.addComponent<Radius>();

            THEN("e should be in positionMap, radiusMap and circleMap")
            {
                REQUIRE(positionMap.mEntities->size() == 1);
                REQUIRE(velocityMap.mEntities->size() == 0);
                REQUIRE(radiusMap.mEntities->size() == 1);
                REQUIRE(moverMap.mEntities->size() == 0);
                REQUIRE(circleMap.mEntities->size() == 1);

                REQUIRE(positionMap.mEntities->at(0) == e);
                REQUIRE(radiusMap.mEntities->at(0) == e);

                WHEN("position is removed from the entity")
                {
                    e.removeComponent<Position>();

                    THEN("the entity should only be in the radiusMap")
                    {
                        REQUIRE(positionMap.mEntities->size() == 0);
                        REQUIRE(velocityMap.mEntities->size() == 0);
                        REQUIRE(radiusMap.mEntities->size() == 1);
                        REQUIRE(moverMap.mEntities->size() == 0);
                        REQUIRE(circleMap.mEntities->size() == 0);
                    }
                }

                WHEN("radius is removed from the entity")
                {
                    e.removeComponent<Radius>();

                    THEN("the entity should only be in the positionMap")
                    {
                        REQUIRE(positionMap.mEntities->size() == 1);
                        REQUIRE(velocityMap.mEntities->size() == 0);
                        REQUIRE(radiusMap.mEntities->size() == 0);
                        REQUIRE(moverMap.mEntities->size() == 0);
                        REQUIRE(circleMap.mEntities->size() == 0);
                    }
                }

                WHEN("position and radius are removed from the entity")
                {
                    e.removeComponent<Position>();
                    e.removeComponent<Radius>();

                    THEN("the entity should not be in any maps")
                    {
                        REQUIRE(positionMap.mEntities->size() == 0);
                        REQUIRE(velocityMap.mEntities->size() == 0);
                        REQUIRE(radiusMap.mEntities->size() == 0);
                        REQUIRE(moverMap.mEntities->size() == 0);
                        REQUIRE(circleMap.mEntities->size() == 0);
                    }
                }
            }
        }
    }
}