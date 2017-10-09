#pragma once

#include <memory>
#include <string>

class MyClass
    : public std::enable_shared_from_this<MyClass>
{
public:
    MyClass(const MyClass& other) = delete;
    MyClass& operator=(const MyClass& other) = delete;

    static std::shared_ptr<MyClass> Create(const std::string& name);

protected:
    MyClass(const std::string& name);
    
private:
    std::string m_name;
};

std::shared_ptr<MyClass> MyClass::Create(const std::string& name)
{
    // Ctor protected, use a forwarder
    struct Forwarder : MyClass
    {
        Forwarder(const std::string& name)
            : MyClass(name)
        {}
    };
    
    return std::make_shared<Forwarder>(name);
}

MyClass::MyClass(const std::string& name)
{
    m_name = name;
}
