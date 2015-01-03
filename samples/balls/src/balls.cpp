#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <set>
#include <functional>
#include <vector>
#include <sstream>

#include <util/dynamic_bitset.h>

#include <managers/EntityManager.h>
#include <managers/ComponentManager.h>
#include <util/TypeEnumerator.h>
#include <util/EntityMap.h>

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
    EntityManager em;
    ComponentManager cm;

    // Temporary create entity function while callbacks aren't implemented
    auto createEntity = [&em, &cm]()
    {
        Entity e = em.createEntity();

        em.onEntityAdded(e);
        cm.onEntityAdded(e);

        return e;
    };

    Entity e1 = createEntity();
    Entity e2 = createEntity();

    cm.addComponent<int>(e1, 5);
    cm.addComponent<char>(e1, 5);
    cm.addComponent<short>(e1, 5);

    auto m1 = cm.getEntityMap<int, char, short>();

    cm.addComponent<float>(e2, 5.0f);
    cm.removeComponent<int>(e1);

    cm.addComponent<int>(e2, 5);
    cm.addComponent<char>(e2, 5);
    cm.addComponent<short>(e2, 5);

    system("pause");
}