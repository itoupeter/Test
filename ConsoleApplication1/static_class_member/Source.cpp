
#include <iostream>

class Base
{
public:
    static Base base;

    Base()
    {
        std::cout << "Constructor" << std::endl;
    }

    ~Base()
    {
        std::cout << "Destructor" << std::endl;
    }
};
 
// without below initialization, the static member Base::base won't be created.
Base Base::base;

int main()
{
    std::cout << "main()" << std::endl;

    return 0;
}