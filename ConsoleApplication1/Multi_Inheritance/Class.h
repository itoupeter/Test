#pragma once

#include <iostream>

class Base1
{
public:
    void Foo()
    {
        std::cout << "In Base1" << std::endl;
    }
};

class Base2
{
public:
    void Foo()
    {
        std::cout << "In Base2" << std::endl;
    }
};

class Derived
    : public Base1
    , public Base2
{};