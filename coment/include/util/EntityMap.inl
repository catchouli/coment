#include "EntityMap.h"

namespace coment
{
    template <typename... ComponentTypes>
    EntityMap<ComponentTypes...>::EntityMap(dynamic_bitset<> componentTypes,
        std::shared_ptr<std::vector<Entity>> entities)
        : mComponentTypes(componentTypes), mEntities(entities)
    {

    }
}