#include <iostream>
#include <memory>
#include <cstdint>

template <typename T1>
class A
{
    template <typename T2>
    void b(T2 t2);
};

template <typename T1>
template <typename T2>
void A<typename T1>::b(T2 t2)
{

}

int main(int argc, char** argv)
{

    system("pause");
}