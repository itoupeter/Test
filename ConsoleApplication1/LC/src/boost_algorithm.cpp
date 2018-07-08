
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>

BOOST_AUTO_TEST_CASE(Boyer_Moore_test)
{
    static const std::string corpus1 = "ioanlasdababck;fa";
    static const std::string corpus2 = "akfnknasdfkla;sdj";
    static const std::string pattern = "ababc";

    boost::algorithm::boyer_moore<std::string::const_iterator> bm(pattern.begin(), pattern.end());

    const auto& result1 = bm(corpus1.begin(), corpus1.end());
    const auto& result2 = bm(corpus2);

    BOOST_TEST((result1.first != corpus1.end()));
    BOOST_TEST((result1.second != corpus1.end()));
    BOOST_TEST((result2.first == corpus2.end()));
    BOOST_TEST((result2.second == corpus2.end()));

    const auto& result3 = boost::algorithm::boyer_moore_search(corpus1, pattern);
    const auto& result4 = boost::algorithm::boyer_moore_search(corpus2.begin(), corpus2.end(), pattern.begin(), pattern.end());

    BOOST_TEST((result3.first != corpus1.end()));
    BOOST_TEST((result3.second != corpus1.end()));
    BOOST_TEST((result4.first == corpus2.end()));
    BOOST_TEST((result4.second == corpus2.end()));
}

// There is also none_of, any_of, one_of, etc.
BOOST_AUTO_TEST_CASE(all_of_test)
{
    static const std::vector<int> v = {2, 2, 2, 2};
    static const std::unordered_map<int, int> umap = {{1, 3}, {5, 11}, {8, 57}};

    BOOST_TEST(
        std::all_of(
            std::begin(v),
            std::end(v),
            [](const auto& e){ return (e & 1) == 0; })
        == true);

    BOOST_TEST(
        boost::algorithm::all_of(
            umap,
            [](auto const& e){ return (e.first & 1) == 1; })
        == false);

    BOOST_TEST(boost::algorithm::all_of_equal(v, 2) == true);
}
