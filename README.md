<h2>coment</h2>
<h3>A C++11 component-entity system</h3>

This branch is a complete rewrite of the original 1.0 branch, which was heavily influenced in design by C++03.

<h4>The new architecture</h4>

As much magic and interdependency has been removed as is possible. In particular:

- The world is now just a collection of systems and managers, as well as proxy APIs for the default managers
- Managers and Systems are now just managed classes that respond to callbacks, and callbacks should be preferred for sharing data over interdependency between managers and systems in all cases
- All component management is now done by the ComponentManager class, which allows the user to obtain an EntityMap<types...> and keeps it up to date when components and entities are added or removed

These changes should allow the library to more reliable and easier to maintain. Additionally, the library has been been designed using data-driven development, so test cases are already available for all implemented behaviour.

Entity and component managers have been implemented, as well as managed Manager and System classes, so all the fundamental requirements to use the library should be fulfilled. Additional features will be provided through new (independent) core managers. Planned features include: tags, groups, messaging, value management.

For examples of how to use the library, check out the samples and tests. The wiki is currently outdated, as it refers to the master/1.0 branches.

<h4>Usage</h4>

<h5>The World</h5>

The primary point of access to the engine is through the World class, which can be constructed like so:

```C++
#include <coment/World.h>

coment::World world;
```

The world is a manager for Managers and Systems (more on those later.) It also provides proxy APIs for the default managers, which provide the default behaviour for coment.

<h5>Entities</h5>

An entity is an object in the world which has a number of components registered to it. These components represent the entity's data, and can be added to or removed from the entity at runtime. Entities can be created like so:

```C++
coment::Entity e = world.createEntity();
```

<h5>Components</h5>

Components are data classes that can be added to an entity. It is recommended that these classes are pure data, but they can contain logic if it suits your design. Components generally inherit from coment::Component. This is not currently enforced, but may be in the future.

A component is created and added to an entity as follows:

```C++
struct Position
  : coment::Component
{
  Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
  
  float x, y;
}

coment::World world;

coment::Entity e = world.createEntity();
Position* p = e.addComponent<Position>(50.0f, 39.0f);
p = e.getComponent<Position>(); // unnecessary since addComponent already returns a pointer
e.removeComponent<Position>(); // p is now invalid
```

Initialisation arguments can be passed into addComponent and are forwarded to one of the object's constructors.

Entities can then be automatically mapped based on their constituent components, allowing logic to be defined based on the entitys' data. These maps are automatically kept up to date when entities and components are added to or removed from the engine, and are represented internally by a flat array for efficient iteration.

```C++
auto moverMap = world.getEntityMap<Position, Velocity>();

for (auto& e : moverMap)
{
  // Get components
  Position* p = e.getComponent<Position>();
  const Velocity* v = e.getComponent<Velocity>();
  
  p.x += dt * v.x;
  p.y += dt * v.y;
}
```

Entities in moverMap are guaranteed to at least have the components Position and Velocity, but may have other components.

Entity::getComponent() will return nullptr if the entity does not have a component, which can be used to check if an entity has a component of a particular type and provide a default if not. (In other words, optional components.)

The pointers returned for components are temporary, and should not be stored. They may be reallocated at any time between callbacks.

<h5>Systems</h5>

Systems are classes managed by the world which provide game logic for your entities. To do this, the base System class defines callbacks which are used to notify all systems and allow them to do any necessary processing.

Systems can be added or removed from to the world in a similar way that components are added to entities. Similarly, arguments can also be passed for initialisation.

```C++
class MovementSystem
  : public coment::System
{
  void onUpdate() override
  {
    static auto moverMap = world.getEntityMap<Position, Velocity>();
    
    for (auto& e : moverMap)
    {
      // Get components
      Position* p = e.getComponent<Position>();
      const Velocity* v = e.getComponent<Velocity>();
      
      p.x += dt * v.x;
      p.y += dt * v.y;
    }
  }
};

// Add the system to the world, so that it can start updating entities
world.addSystem<MovementSystem>();
```

Available callbacks include: onEntityAdded(e), onEntityRemoved(e), preUpdate(), onUpdate(), and postUpdate().

<h5>Managers</h5>

Managers provide the behaviour for the whole engine, and are compartmentalised into Manager classes that are synchronised through callbacks similar to System callbacks. The following default managers are provided: EntityManager, ComponentManager. The Entity and World classes provide proxy APIs for these managers. They can also be obtained directly using World::getManager<T>().

Custom mamangers can also be provided in a similar way to Systems. The callbacks provided include: onEntityAdded(e), onEntityRemoved(e), preUpdate(), postUpdate().
