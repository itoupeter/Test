
#include <boost/test/unit_test.hpp>

#pragma warning(disable:4996)
#include <gmock/gmock.h>

using ::testing::Mock;


class PerfCounter
{
public:
    using ID = std::uint32_t;

    virtual ~PerfCounter() {}

    virtual void Set(ID id, int x) { (void)id; (void)x; }
    virtual void Increment(ID id) { (void)id; }
};

class MockPerfCounter : public PerfCounter
{
public:
    MOCK_METHOD2(Set, void(ID id, int x));
    MOCK_METHOD1(Increment, void(ID id));
};

template <typename>
class ResourceManager;

struct UseSmartPtr;
struct UseRef;

template <>
class ResourceManager<UseSmartPtr>
{
public:
    explicit
    ResourceManager(std::shared_ptr<PerfCounter> perfCounter)
      : m_perfCounter{ std::move(perfCounter) }
    {}

    void CallSet(PerfCounter::ID id, int x)
    {
        m_perfCounter->Set(id, x);
    }

private:
    std::shared_ptr<PerfCounter> m_perfCounter;
};

template <>
class ResourceManager<UseRef>
{
public:
    explicit
    ResourceManager(PerfCounter& perfCounter)
        : m_perfCounter{ perfCounter }
    {}

    void CallSet(PerfCounter::ID id, int x)
    {
        m_perfCounter.Set(id, x);
    }

private:
    PerfCounter& m_perfCounter;
};

BOOST_AUTO_TEST_CASE(gmock_test)
{
    MockPerfCounter perfCounter;

    BOOST_TEST_CONTEXT("test 1")
    {
        EXPECT_CALL(perfCounter, Set(1, 2))
            .Times(1);

        perfCounter.Set(1, 2);

        BOOST_TEST(Mock::VerifyAndClearExpectations(&perfCounter) == true);
    }

    BOOST_TEST_CONTEXT("test 2")
    {
        EXPECT_CALL(perfCounter, Set(1, 2))
            .Times(2);

        perfCounter.Set(1, 2);

        BOOST_TEST(Mock::VerifyAndClearExpectations(&perfCounter) == false);
    }

    BOOST_TEST_CONTEXT("test 3")
    {
        EXPECT_CALL(perfCounter, Set(1, 2))
            .Times(1);

        BOOST_TEST(Mock::VerifyAndClearExpectations(&perfCounter) == false);
    }
}

BOOST_AUTO_TEST_CASE(gmock_test2)
{
    BOOST_TEST_CONTEXT("smart ptr")
    {
        auto mockPerfCounter = std::make_shared<MockPerfCounter>();
        ResourceManager<UseSmartPtr> resource(mockPerfCounter);

        EXPECT_CALL(*mockPerfCounter, Set(1, 2))
            .Times(1);

        resource.CallSet(1, 2);

        BOOST_TEST(Mock::VerifyAndClearExpectations(mockPerfCounter.get()) == true);
    }

    BOOST_TEST_CONTEXT("ref")
    {
        MockPerfCounter mockPerfCounter;
        ResourceManager<UseRef> resource(mockPerfCounter);

        EXPECT_CALL(mockPerfCounter, Set(1, 2))
            .Times(1);

        resource.CallSet(1, 99);

        BOOST_TEST(Mock::VerifyAndClearExpectations(&mockPerfCounter) == false);
    }
}
