<h2>coment</h2>
<h3>A C++11 component-entity system</h3>

This branch is a complete rewrite of the original 1.0 branch, which was heavily influenced in design by C++03.

Class documentation: http://cat.rena.so/coment/docs/html/index.html

The library is header only. To use, simply add the include directory to your project/makefile's includes and try some of the following samples. For more fully-fledged samples and examples, check out the samples directory.

If your project uses boost, delete the boost directory from coment\include to prevent mixing boost versions. The included boost headers are from header-only libraries, so are standalone if you don't use boost.

Contact me (cat): (leave an issue)

<h4>Samples</h4>

The 'balls' sample is the simplest place to get started. For windows, the dependencies are included. On other platforms, SDL2 and opengl are required.

<h4>Scripting</h4>

This library works well with the swig wrapper generator for embedded languages.

If all you want is the ability to use native components/systemms, just include the coment headers in your interfaces (or write your own simple wrappers), and then use %template to instantiatate World::addComponent, World::getComponent and World::removeComponent templates for your component types, and World::addSystem and world::removeSystem templates for your system types.

If you want the ability to use scriptable components/systems some modification is required. [This project](https://github.com/Catchouli/webdraw) contains a [modified version of coment](https://github.com/Catchouli/webdraw/tree/master/engine/public/coment) and a set of interfaces and helpers [[1]](https://github.com/Catchouli/webdraw/tree/master/engine/interfaces/interfaces) [[2]](https://github.com/Catchouli/webdraw/blob/master/engine/interfaces/interfaces/typemaps.i) [[3]](https://github.com/Catchouli/webdraw/blob/master/engine/interfaces/interfaces/components.i) [[4]](https://github.com/Catchouli/webdraw/blob/master/engine/interfaces/interfaces/systems.i) which support the registration of lua components and systems, which could be modified to support other scripting languages by providing alternate types to replace LuaTable, (which allows managed lua table references to be passed to c++ as arguments.)

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

The pointers returned for components are temporary, and should not be stored. They may be reallocated at any time between callbacks when a coment API has been called.

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
