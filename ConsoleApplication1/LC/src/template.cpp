
#include <iostream>
#include <string>
#include <boost/test/unit_test.hpp>

class Base
{
public:
    template <typename T = void>
    std::string Foo()
    {
        return "default";
    }

    template <>
    std::string Foo<int>()
    {
        return "int";
    }

    template <>
    std::string Foo<double>()
    {
        return "double";
    }
};

BOOST_AUTO_TEST_CASE(member_function_specialization_test)
{
    Base base;

    BOOST_TEST(base.Foo<>() == "default");
    BOOST_TEST(base.Foo<int>() == "int");
    BOOST_TEST(base.Foo<double>() == "double");
}

//------------------------------------------------------------------

template <typename T = void>
class Base2
{
public:
    std::string Foo()
    {
        return "default";
    }
};

template <>
class Base2<int>
{
public:
    std::string Foo()
    {
        return "int";
    }
};

BOOST_AUTO_TEST_CASE(class_specialization_test)
{
    Base2<> base;
    Base2<int> base2;

    BOOST_TEST(base.Foo() == "default");
    BOOST_TEST(base2.Foo() == "int");
}