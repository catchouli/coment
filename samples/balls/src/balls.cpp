#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <set>
#include <functional>
#include <vector>
#include <cstdio>

#include <coment/reflection/MemberOffset.h>
#include <coment/reflection/TypeRegistry.h>

using namespace coment;

struct Position
{
    void test()
    {
        printf("test\n");
    }

    float x, y;
};
REGISTER_COMPONENT(Position);

template <typename T>
void testType()
{
    printf("%s\n", typeid(T).name());
}

int main(int argc, char** argv)
{
    const ComentTypeInfo positionTypeInfo = getTypeInfo("Position");

    float Position::* x = &Position::x;
    float Position::* y = &Position::y;

    size_t test1 = dataMemberOffset(x);
    size_t test2 = dataMemberOffset(y);

    testType<int>();
    testType<Position>();

    system("pause");
}