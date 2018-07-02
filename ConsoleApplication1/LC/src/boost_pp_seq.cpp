
#include "boost/test/unit_test.hpp"
#include <boost/preprocessor/seq.hpp>


#define SEQUENCE \
    (Apple) \
    (Banana) \
    (HelloWorld) \
    // SEQUENCE


BOOST_AUTO_TEST_SUITE(boost_pp_seq_tests)

BOOST_AUTO_TEST_CASE(boost_pp_seq_enum_test)
{
#define DEFINE_ENUM_CLASS(EnumType, UnderlyingType, Seq) \
    enum class EnumType : UnderlyingType \
    { \
        BOOST_PP_SEQ_ENUM(Seq) \
    }; \
    //

    DEFINE_ENUM_CLASS(ProblemId, std::uint16_t, SEQUENCE)

#undef DEFINE_ENUM_CLASS

    (void)ProblemId::Apple;
    (void)ProblemId::HelloWorld;
}

BOOST_AUTO_TEST_CASE(boost_pp_seq_for_each_test)
{
#define DEFINE_ASSIGNMENT_EXPRESSION(unused, value, elem) \
    int elem ## = value; \
    // DEFINE_ASSIGNMENT_EXPRESSION

    BOOST_PP_SEQ_FOR_EACH(DEFINE_ASSIGNMENT_EXPRESSION, 99, SEQUENCE)

#undef DEFINE_ASSIGNMENT_EXPRESSION

    BOOST_TEST(Apple == 99);
    BOOST_TEST(HelloWorld == 99);
}

BOOST_AUTO_TEST_SUITE_END() // boost_pp_seq_tests
