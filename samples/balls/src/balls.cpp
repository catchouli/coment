#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <set>
#include <functional>
#include <vector>
#include <sstream>

#include <coment/World.h>
#include <coment/managers/EntityManager.h>
#include <coment/managers/ComponentManager.h>
#include <coment/util/TypeEnumerator.h>
#include <coment/util/EntityMap.h>
#include <coment/util/dynamic_bitset.h>

namespace boost
{
    // specialise dynamic bitset for size_t& to return the hash of the underlying data
    template <>
    inline void to_block_range(const dynamic_bitset<>& b, size_t& hash_result)
    {
        //hash_result = boost::hash_value(b.m_bits);
        //hash_result = 0;
        int i = 0;
    }
}

using namespace coment;

int main(int argc, char** argv)
{
    World world;

    // Add managers to world
    EntityManager* em = world.getManager<EntityManager>();
    ComponentManager* cm = world.getManager<ComponentManager>();

    Entity e1 = em->createEntity();
    Entity e2 = em->createEntity();

    cm->addComponent<int>(e1, 5);
    cm->addComponent<char>(e1, 5);
    cm->addComponent<short>(e1, 5);

    auto m1 = cm->getEntityMap<int, char, short>();

    cm->addComponent<float>(e2, 5.0f);
    cm->removeComponent<int>(e1);

    cm->addComponent<int>(e2, 5);
    cm->addComponent<char>(e2, 5);
    cm->addComponent<short>(e2, 5);

    system("pause");
}