
#include <boost/test/unit_test.hpp>


struct CreationPolicy
{
    template <typename TObject>
    struct Singleton
    {
        static std::shared_ptr<TObject> Create()
        {
            static auto m_singleton = std::make_shared<TObject>();

            return m_singleton;
        }
    };

    template <typename TObject>
    struct New
    {
        static std::shared_ptr<TObject> Create()
        {
            return std::make_shared<TObject>();
        }
    };
};


template <typename TObject, template <typename> typename TCreationPolicy>
class ObjectFactory : public TCreationPolicy<TObject>
{
public:
    static std::shared_ptr<TObject> GetObject()
    {
        return TCreationPolicy<TObject>::Create();
    }
};


BOOST_AUTO_TEST_CASE(policy_test)
{
    struct Foo {};

    BOOST_TEST_CONTEXT("new policy")
    {
        auto obj1 = ObjectFactory<Foo, CreationPolicy::New>::GetObject();
        auto obj2 = ObjectFactory<Foo, CreationPolicy::New>::GetObject();

        BOOST_TEST(obj1.get() != obj2.get());
    }

    BOOST_TEST_CONTEXT("singleton policy")
    {
        auto obj1 = ObjectFactory<Foo, CreationPolicy::Singleton>::GetObject();
        auto obj2 = ObjectFactory<Foo, CreationPolicy::Singleton>::GetObject();

        BOOST_TEST(obj1.get() == obj2.get());
    }
}
