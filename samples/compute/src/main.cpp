#include <cstdlib>
#include <stdexcept>
#include <iostream>

int entry(int argc, char** argv);
int main(int argc, char** argv)
{
    try
    {
        return entry(argc, argv);
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
        system("pause");
    }
}