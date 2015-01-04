<h2>coment</h2>
<h3>A C++11 component-entity system</h3>

This branch is a complete rewrite of the original 1.0 branch, which is heavily influenced in design by C++03.

If you are looking at an updated version for C++11, this branch may be more appropriate.

This branch is still in development, and will eventually replace the master branch.

<h4>The new architecture<h4>

As much magic and interdependency has been removed. In particular:

- The world is now just a collection of systems and managers, as well as proxy APIs for the default managers
- Managers and Systems are now just managed classes that respond to callbacks, and callbacks should be preferred for sharing data over interdependency between managers and systems in all cases
- All component management is now done by the ComponentManager class, which allows the user to obtain an EntityMap<types...> and keeps it up to date when components and entities are added or removed

These changes should allow the library to more reliable and easier to maintain. Additionally, the library has been been designed using data-driven development, so test cases are already available for all implemented behaviour.

Entity and component managers have been implemented, as well as managed Manager and System classes, so all the fundamental requirements to use the library should be fulfilled. Additional features will be provided through new (independent) core managers. Planned features include: tags, groups, messaging, value management.

For examples of how to use the library, check out the samples and tests. The wiki is currently outdated, as it refers to the master/1.0 branches.
