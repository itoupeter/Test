
#include <boost/test/unit_test.hpp>

#define FRUIT_SEQUENCE \
    (Apple) \
    (Banana) \
    (Orange) \
    // SEQUENCE

#define DEFINE_ENUM_CLASS(EnumType, BaseType, seq) \
    enum class EnumType : BaseType \
    { \
        BOOST_PP_SEQ_ENUM(seq) \
    }; \
    // DEFINE_ENUM_CLASS

    DEFINE_ENUM_CLASS(Fruit, std::uint8_t, FRUIT_SEQUENCE)
#undef DEFINE_ENUM_CLASS

#define DEFINE_ENUM_STRING(unused1, unused2, elem) BOOST_PP_STRINGIZE(elem),
    const std::string c_fruitNames[] = 
    {
        BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_STRING, unused, FRUIT_SEQUENCE)
    };
#undef DEFINE_ENUM_STRING
#define GET_FRUIT_NAME(id) c_fruitNames[id]

template<Fruit id>
class FruitPrinter
{
public:
    int GetId() const
    {
        return static_cast<int>(id);
    }

    std::string GetName() const
    {
        return GET_FRUIT_NAME(static_cast<int>(id));
    }
};

BOOST_AUTO_TEST_CASE(enum_specialization)
{
    static const int c_apple = static_cast<int>(Fruit::Apple);
    static const int c_banana = static_cast<int>(Fruit::Banana);

    static const std::string c_appleName = "Apple";
    static const std::string c_bananaName = "Banana";

    FruitPrinter<Fruit::Apple> apple;
    FruitPrinter<Fruit::Banana> banana;

    BOOST_TEST(apple.GetId() == c_apple);
    BOOST_TEST(banana.GetId() == c_banana);

    BOOST_TEST(apple.GetName() == c_appleName);
    BOOST_TEST(banana.GetName() == c_bananaName);
}
