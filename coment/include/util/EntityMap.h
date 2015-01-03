#pragma once

#include "TypeEnumerator.h"
#include "dynamic_bitset.h"
#include "../Entity.h"

#include <vector>
#include <memory>
#include <set>

namespace coment
{
    template <typename... ComponentTypes>
    class EntityMap
    {
    public:

        EntityMap(dynamic_bitset<> componentTypes, std::shared_ptr<std::vector<Entity>> entities);

    private:

        dynamic_bitset<> mComponentTypes;

        std::shared_ptr<std::vector<Entity>> mEntities;

    };
}

#include "EntityMap.inl"