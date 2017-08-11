#define BOOST_TEST_MODULE My first test module.
#include <boost/test/included/unit_test.hpp>

struct standart_fixture {
    standart_fixture() { BOOST_TEST_MESSAGE("setup"); }
    ~standart_fixture() { BOOST_TEST_MESSAGE("cleanup"); }
    int n { 42 };
};

struct extended_fixture {
    std::string name;
    int data;

    extended_fixture(std::string const& n = "")
        : name(n), data(0)
    {
        BOOST_TEST_MESSAGE("setup" + name);
    }

    ~extended_fixture()
    {
        BOOST_TEST_MESSAGE("cleanup" + name);
    }
};

void fixture_setup()
{
    BOOST_TEST_MESSAGE("fixture setup");
}

void fixture_cleanup()
{
    BOOST_TEST_MESSAGE("fixture cleanup");
}

// fixture -----------------
BOOST_FIXTURE_TEST_SUITE(suite1, extended_fixture)

BOOST_AUTO_TEST_CASE(case1)
{
    BOOST_TEST(data == 0);
}

BOOST_AUTO_TEST_CASE(case2)
{
    ++data;
    BOOST_TEST(data == 1);
}

BOOST_AUTO_TEST_SUITE_END()

// fixture ---------------
BOOST_FIXTURE_TEST_SUITE(suite2, extended_fixture)

BOOST_AUTO_TEST_CASE(case1)
{
    BOOST_TEST(data == 0);
}

BOOST_FIXTURE_TEST_CASE(case2, standart_fixture)
{
    BOOST_TEST(n == 42);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(test_case_multifix,
    * boost::unit_test::fixture<extended_fixture>(std::string("fix1"))
    * boost::unit_test::fixture<extended_fixture>(std::string("fix2"))
    * boost::unit_test::fixture<standart_fixture>())
{
    BOOST_TEST(true);
}

BOOST_GLOBAL_FIXTURE(standart_fixture);

