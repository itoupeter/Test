
#include <boost/test/unit_test.hpp>
#include <boost/preprocessor/seq.hpp>


#define SEQUENCE \
    (Apple) \
    (Banana) \
    (HelloWorld) \
    // SEQUENCE

#define COMPLEX_SEQUENCE \
    ((Apple)(PingGuo)(1)) \
    ((Banana)(XiangJiao)(2)) \
    ((HelloWorld)(NiHao)(3)) \
    // COMPLEX_SEQUENCE


BOOST_AUTO_TEST_CASE(seq_enum_test)
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

BOOST_AUTO_TEST_CASE(seq_for_each_test)
{
#define DEFINE_ASSIGNMENT_EXPRESSION(unused, value, elem) \
    int elem = value; \
    // DEFINE_ASSIGNMENT_EXPRESSION

    BOOST_PP_SEQ_FOR_EACH(DEFINE_ASSIGNMENT_EXPRESSION, 99, SEQUENCE)

#undef DEFINE_ASSIGNMENT_EXPRESSION

    BOOST_TEST(Apple == 99);
    BOOST_TEST(HelloWorld == 99);
}

BOOST_AUTO_TEST_CASE(seq_cat_test)
{
    int BOOST_PP_SEQ_CAT(SEQUENCE) = 999;

    BOOST_TEST(AppleBananaHelloWorld == 999);
}

BOOST_AUTO_TEST_CASE(stringize_test)
{
    BOOST_TEST(BOOST_PP_STRINGIZE(BOOST_PP_SEQ_CAT(SEQUENCE)) == "AppleBananaHelloWorld");
}

BOOST_AUTO_TEST_CASE(seq_elem_test)
{
#define DEFINE_ASSIGNMENT(unused1, unused2, elem) \
    int BOOST_PP_SEQ_ELEM(0, elem) = BOOST_PP_SEQ_ELEM(2, elem); \
    // DEFINE_ASSIGNMENT

    BOOST_PP_SEQ_FOR_EACH(DEFINE_ASSIGNMENT, unused, COMPLEX_SEQUENCE)

#undef DEFINE_ASSIGNMENT

    BOOST_TEST(Apple == 1);
    BOOST_TEST(Banana == 2);
}
