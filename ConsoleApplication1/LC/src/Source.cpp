
#include <boost/test/unit_test.hpp>

#include <functional>
#include <random>

BOOST_AUTO_TEST_CASE(std_bind_test)
{
    using namespace std::placeholders;

    int a = 0;
    int b = 0;
    int c = 0;

    auto Assign = [&](int x, int y, int z)
    {
        a = x;
        b = y;
        c = z;
    };

    auto CheckValues = [&](int x, int y, int z)
    {
        BOOST_TEST(a == x);
        BOOST_TEST(b == y);
        BOOST_TEST(c == z);
    };

    BOOST_TEST_CONTEXT("bind by value")
    {
        std::bind(Assign, _1, _2, 99)(1, 2, 3);
        CheckValues(1, 2, 99);

        std::bind(Assign, _2, _2, _2)(1, 2, 3);
        CheckValues(2, 2, 2);

        std::bind(Assign, _3, _2, _1)(1, 2, 3);
        CheckValues(3, 2, 1);
    }

    BOOST_TEST_CONTEXT("bind by ref")
    {
        int refValue = 100;
        auto binded = std::bind(Assign, 99, refValue, std::ref(refValue));

        binded(1, 2, 3);
        CheckValues(99, 100, 100);

        refValue = 10;

        binded(1, 2, 3);
        CheckValues(99, 100, 10);
    }

    BOOST_TEST_CONTEXT("nested bind")
    {
        auto Increment = [](int x){ return x + 1; };
        auto binded = std::bind(Assign, 99, std::bind(Increment, _3), _2);

        binded(1, 2, 3); // calls Assign(99, Increment(3), 2)
        CheckValues(99, 4, 2);
    }

    BOOST_TEST_CONTEXT("bind to class member")
    {
        struct Foo
        {
            int operator()(bool) const
            {
                return 0;
            }

            int operator()(int x) const
            {
                return x + 1;
            }

            int Inc(int x) const
            {
                return x + 1;
            }

            int data = 10;
        };

        Foo foo;

        auto bindFunc = std::bind(&Foo::Inc, &foo, _1);
        BOOST_TEST(bindFunc(10) == 11);
        
        auto bindData = std::bind(&Foo::data, _1);
        BOOST_TEST(bindData(foo) == 10);

        auto binded = std::bind(Foo(), _1);
        BOOST_TEST(binded(99) == 100);
        BOOST_TEST(binded(true) == 0);
    }
}
