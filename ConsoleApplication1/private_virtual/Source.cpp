
#include <iostream>
#include <memory>

class Base
{
public:
    void callFoo()
    {
        foo();
    }

private:
    virtual void foo() = 0;
};

class Derived : public Base
{
private:
    virtual void foo() override
    {
        std::cout << "Derived::foo(), i = " << i << std::endl;
    }

    int i = 1;
    int j = 1;
};

class Derived2 : public Derived
{
private:
    virtual void foo() override
    {
        std::cout << "Derived2::foo(), i = " << i << std::endl;
    }

    int i = 2;
};

int main()
{
    Base *basePtr = new Derived2;

    basePtr->callFoo();

    return 0;
}