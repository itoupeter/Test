
#include "Class.h"

#include <memory>

int main()
{
    auto derivedPtr = new Derived;

    static_cast<Base1*>(derivedPtr)->Foo();
    static_cast<Base2*>(derivedPtr)->Foo();

    Derived derived;

    static_cast<Base1>(derived).Foo();
    static_cast<Base2>(derived).Foo();

    return 0;
}