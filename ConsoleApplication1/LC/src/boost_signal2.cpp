
#pragma warning(disable: 4996)
#include <boost/test/unit_test.hpp>
#include <boost/signals2.hpp>


BOOST_AUTO_TEST_CASE(single_slot_test)
{
    static const int c_preValue = 1;
    static const int c_postValue = 2;

    struct HelloWorld
    {
        void operator()(int& i) const
        {
            i = c_postValue;
        }
    };

    HelloWorld helloWorld;

    boost::signals2::signal<void(int&)> signal;
    signal.connect(helloWorld);

    int number = c_preValue;
    signal(number);

    BOOST_TEST(number == c_postValue);
}

BOOST_AUTO_TEST_CASE(multiple_slots_test)
{
    static const int c_addValue1 = 1;
    static const int c_addValue2 = 2;
    static const int c_preValue = 0;
    static const int c_postValue = 3;

    struct Hello
    {
        void operator()(int& i) const
        {
            i += c_addValue1;
        }
    };

    struct World
    {
        void operator()(int& i) const
        {
            i += c_addValue2;
        }
    };

    Hello hello;
    World world;

    boost::signals2::signal<void(int&)> signal;
    signal.connect(hello);
    signal.connect(world);

    int number = c_preValue;
    signal(number);

    BOOST_TEST(number == c_postValue);
}

BOOST_AUTO_TEST_CASE(multiple_slots_ordering_test)
{
    static const int c_value1 = 1;
    static const int c_value2 = 2;
    static const int c_value3 = 3;
    static const std::vector<int> c_values = {c_value3, c_value2, c_value1 };

    auto slot1 = [](std::vector<int>& v) { v.push_back(c_value1); };
    auto slot2 = [](std::vector<int>& v) { v.push_back(c_value2); };
    auto slot3 = [](std::vector<int>& v) { v.push_back(c_value3); };

    boost::signals2::signal<void(std::vector<int>&)> signal;
    signal.connect(1, slot1);
    signal.connect(0, slot2);
    signal.connect(slot3, boost::signals2::at_front);

    std::vector<int> values;
    signal(values);

    BOOST_TEST(values == c_values, boost::test_tools::per_element());
}

namespace fulfilled_slot
{
struct FulfilledRequest
{
    typedef std::vector<int> result_type;

    template<typename TInputIterator>
    result_type operator()(TInputIterator first, TInputIterator last) const
    {
        result_type values;

        while (first != last)
        {
            values.push_back(*first++);
            break;
        }

        return values;
    }
};
} // namespace fulfilled_slot_test

BOOST_AUTO_TEST_CASE(fulfilled_slot_test)
{
    using namespace fulfilled_slot;

    static const int c_value1 = 1;
    static const int c_value2 = 2;
    static const std::vector<int> c_values = {c_value1};

    auto slot1 = [](){ return c_value1; };
    auto slot2 = [](){ return c_value2; };

    boost::signals2::signal<int(), FulfilledRequest> signal;
    signal.connect(slot1);
    signal.connect(slot2);
    
    BOOST_TEST(signal() == c_values, boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(duplicate_slot_test)
{
    static const int c_preValue = 0;
    static const int c_postValue = 2;

    auto slot = [](int& x){ ++x; };

    boost::signals2::signal<void(int&)> signal;
    signal.connect(slot);
    signal.connect(slot);

    int number = c_preValue;

    signal(number);

    // Duplicate slot is called multiple times
    BOOST_TEST(number == c_postValue);
}

BOOST_AUTO_TEST_CASE(connection_test)
{
    static const int c_preValue = 0;
    static const int c_postValue = 0;

    auto slot = [](int& x) { ++x; };

    boost::signals2::signal<void(int&)> signal;
    auto connection = signal.connect(slot);

    // disconnect here
    connection.disconnect();

    int number = c_preValue;
    signal(number);

    BOOST_TEST(connection.connected() == false);
    BOOST_TEST(number == c_postValue);
}

BOOST_AUTO_TEST_CASE(blocking_slot_test)
{
    static const int c_preValue = 0;
    static const int c_postValue = 0;
    static const int c_postValue2 = 1;

    auto slot = [](int& x) { ++x; };

    boost::signals2::signal<void(int&)> signal;
    auto connection = signal.connect(slot);

    int number = c_preValue;

    // block in scope
    {
        boost::signals2::shared_connection_block block(connection);

        signal(number);
    }

    BOOST_TEST(number == c_postValue);

    // block gone outsides scope
    signal(number);

    BOOST_TEST(number == c_postValue2);
}

BOOST_AUTO_TEST_CASE(scoped_connection_test)

{
    static const int c_preValue = 0;
    static const int c_postValue = 0;

    auto slot = [](int& x) { ++x; };

    boost::signals2::signal<void(int&)> signal;

    {
        boost::signals2::scoped_connection scopedConnection(signal.connect(slot));
    }
    
    int number = c_preValue;

    // disconnected outsides connection scope
    signal(number);

    BOOST_TEST(number == c_postValue);
}
