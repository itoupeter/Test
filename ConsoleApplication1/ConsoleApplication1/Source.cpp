
#include <map>
#include <string>
#include <iostream>

#pragma warning(push)
#pragma warning(disable:4348)

#include <boost\spirit\include\karma.hpp>

#pragma warning(pop)

namespace karma = boost::spirit::karma;

struct Data
{
    std::string name;
};

//namespace boost
//{
//namespace spirit
//{
//namespace traits
//{
//    template <>
//    struct transform_attribute<const Data, std::string, karma::domain>
//    {
//        typedef std::string type;
//
//        static std::string pre(const Data& d) 
//        {
//            return d.name;
//        }
//    };
//}
//}
//}

//using pair_type = std::pair<int, Data>;
using pair_type = std::pair<int, int>;
using DataContainer = std::vector<pair_type>;
//using DataContainer = std::map<int, Data>;

template <typename OutputIterator>
struct key_value 
    : karma::grammar<OutputIterator, std::vector<pair_type>()>
{
    key_value()
        : key_value::base_type(query)
    {
        query = pair << *(';' << pair);
        pair = karma::int_ << ':' << karma::int_;
    }

    karma::rule<OutputIterator, std::vector<pair_type>()> query;
    karma::rule<OutputIterator, pair_type()> pair;
};

int main()
{
    using sink_type = std::back_insert_iterator<std::string>;

    std::map<int, Data> persons = {
        {1, {"Liang"}}, {2, {"Peng"}}
    };
    std::vector<pair_type> persons1 = {
        {1, 2}, {2, 3}
    };
    std::vector<std::pair<int, Data> > persons2 = {
        {1, {"Liang"}}, {2, {"Peng"}}
    };
    std::vector<Data> persons3 = {
        {"Liang"}, {"Peng"}
    };
    std::vector<std::string> persons4 = {
        "Liang", "Peng"
    };
    std::vector<int> persons5 = {
        1, 2
    };
    std::string result;
    sink_type sink(result);
    key_value<sink_type> g;

    karma::generate(sink, g, persons1);

    std::cout << result << std::endl;

    return 0;
}