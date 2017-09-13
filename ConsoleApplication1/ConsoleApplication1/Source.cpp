
#include <map>
#include <string>
#include <iostream>

#pragma warning(push, 0)

#include <boost\config\warning_disable.hpp>
#include <boost\spirit\include\karma.hpp>
#include <boost\fusion\include\std_pair.hpp>

#pragma warning(pop)

namespace karma = boost::spirit::karma;

struct Data
{
    std::string name;
};

namespace boost
{
namespace spirit
{
namespace traits
{
    template <>
    struct transform_attribute<const Data, std::string, karma::domain>
    {
        typedef std::string type;
        static std::string pre(const Data& d) 
        {
            return d.name;
        }
    };
}
}
}

using pair_type = std::pair<int, Data>;
using container_type = std::map<int, Data>;

template <typename OutputIterator>
struct key_value 
    : karma::grammar<OutputIterator, container_type()>
{
    key_value()
        : key_value::base_type(query)
    {
        query = pair << *(';' << pair);
        pair = karma::int_ << ':' << karma::attr_cast(karma::string);
    }

    karma::rule<OutputIterator, container_type()> query;
    karma::rule<OutputIterator, pair_type()> pair;
};

int main()
{
    std::map<int, Data> persons = {
        {1, {"Liang"}}, {2, {"Peng"}}
    };
    std::string result;

    karma::generate(
        std::back_inserter(result), 
        key_value<std::back_insert_iterator<std::string> >(), 
        persons);

    std::cout << result << std::endl;

    return 0;
}