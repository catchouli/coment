#include <catch.hpp>

#include <coment/World.h>
#include <coment/managers/EntityManager.h>
#include <coment/managers/ComponentManager.h>

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
    EntityManager& em = *world.getManager<EntityManager>();
    ComponentManager& cm = *world.getManager<ComponentManager>();

    GIVEN("an uninitialised entity")
    {
        Entity e;

        WHEN("a component is added to the entity")
        {
            THEN("there should be an exception")
            {
                REQUIRE_THROWS(cm.addComponent<Position>(e));
            }
        }
    }

    GIVEN("a dead entity")
    {
        Entity e = em.createEntity();

        // Copy entity so that destroyEntity() doesn't invalidate our e reference
        Entity e2 = e;
        em.destroyEntity(e2);
        world.update(); // Force update so that delayed entity destruction is performed

        WHEN("a component is added to the entity")
        {
            THEN("there should be an exception")
            {
                REQUIRE_THROWS(cm.addComponent<Position>(e));
            }
        }
    }

    GIVEN("a new entity")
    {
        Entity e = em.createEntity();

        WHEN("a component is added to an entity")
        {
            Position* p = cm.addComponent<Position>(e);

            THEN("the component pointer should not be null")
            {
                REQUIRE(p != NULL);
            }

            THEN("the component should be obtainable from the component manager")
            {
                // Check that the pointer is the same
                REQUIRE(p == cm.getComponent<Position>(e));
            }
        }
    }

    GIVEN("position, velocity, and radius component types")
    {
        Entity e = em.createEntity();

        auto positionMap = cm.getEntityMap<Position>();
        auto velocityMap = cm.getEntityMap<Velocity>();
        auto radiusMap = cm.getEntityMap<Radius>();
        auto moverMap = cm.getEntityMap<Position, Velocity>();
        auto circleMap = cm.getEntityMap<Position, Radius>();

        WHEN("a position is added to the entity")
        {
            cm.addComponent<Position>(e);

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
                    cm.removeComponent<Position>(e);

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
            cm.addComponent<Velocity>(e);

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
                    cm.removeComponent<Velocity> (e);

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
            cm.addComponent<Radius>(e);

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
                    cm.removeComponent<Radius>(e);

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
            cm.addComponent<Velocity>(e);
            cm.addComponent<Radius>(e);

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
                    cm.removeComponent<Velocity>(e);

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
                    cm.removeComponent<Radius>(e);

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
                    cm.removeComponent<Velocity>(e);
                    cm.removeComponent<Radius>(e);

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
            cm.addComponent<Position>(e);
            cm.addComponent<Velocity>(e);

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
                cm.removeComponent<Position>(e);

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
                cm.removeComponent<Velocity>(e);

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
                cm.removeComponent<Position>(e);
                cm.removeComponent<Velocity>(e);

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
            cm.addComponent<Position>(e);
            cm.addComponent<Radius>(e);

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
                    cm.removeComponent<Position>(e);

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
                    cm.removeComponent<Radius>(e);

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
                    cm.removeComponent<Position>(e);
                    cm.removeComponent<Radius>(e);

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