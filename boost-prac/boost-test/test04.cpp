#define BOOST_TEST_MODULE My first test module.
#include <boost/test/included/unit_test.hpp>

class point3d
{
    int x_;
    int y_;
    int z_;
    public:
    point3d(int const x = 0, int const y = 0, int const z = 0)
        :x_(x), y_(y), z_(z) {}
    int x() const { return x_; }
    point3d& x(int const x) { x_ = x; return *this; }

    int y() const { return y_; }
    point3d& y(int const y) { y_ = y; return *this; }

    int z() const { return z_; }
    point3d& z(int const z) { z_ = z; return *this; }

    bool operator==(point3d const & pt) const
    {
        return x_ == pt.x_ && y_ == pt.y_ && z_ == pt.z_;
    }

    bool operator!=(point3d const & pt) const
    {
        return !(*this == pt);
    }

    bool operator<(point3d const & pt) const
    {
        return x_ < pt.x_ || y_ < pt.y_ || z_ < pt.z_;
    }

    friend std::ostream& operator<<(std::ostream& stream,
                point3d const & pt)
    {
        stream << "(" << pt.x_ << "," << pt.y_ << "," << pt.z_ << ")";
        return stream;
    }

    void offset(int const offsetx, int const offsety, int const offsetz)
    {
        x_ += offsetx;
        y_ += offsety;
        z_ += offsetz;
    }

    static point3d origin() { return point3d{}; }
};


// ---------------------------------------
BOOST_AUTO_TEST_SUITE(test_contruction)

BOOST_AUTO_TEST_CASE(test_construction)
{
    auto p = point3d{ 1, 2, 3 };
    BOOST_TEST(p.x() == 1);
    BOOST_TEST(p.y() == 2);
    BOOST_TEST(p.z() == 4); // will fail.
}

BOOST_AUTO_TEST_CASE(test_origin)
{
    auto p = point3d::origin();
    BOOST_TEST(p.x() == 0);
    BOOST_TEST(p.y() == 0);
    BOOST_TEST(p.z() == 0);
}

BOOST_AUTO_TEST_SUITE_END()

// --------------------------------
BOOST_AUTO_TEST_SUITE(test_operations)
BOOST_AUTO_TEST_SUITE(test_methods)

BOOST_AUTO_TEST_CASE(test_offset)
{
    auto p = point3d{ 1, 2, 3 };
    p.offset(1, 1, 1);
    BOOST_TEST(p.x() == 2);
    BOOST_TEST(p.y() == 3);
    BOOST_TEST(p.z() == 3); // will fail.
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

// ---------------------------------
BOOST_AUTO_TEST_SUITE(test_operations)
BOOST_AUTO_TEST_SUITE(test_operators)

BOOST_AUTO_TEST_CASE(
    test_equal,
    *boost::unit_test::description("test operator==")
    *boost::unit_test::label("opeq"))
{
    auto p1 = point3d{ 1, 2, 3 };
    auto p2 = point3d{ 1, 2, 3 };
    auto p3 = point3d{ 3, 2, 1 };
    BOOST_TEST(p1 == p2);
    BOOST_TEST(p1 == p3); // will fail.
}

BOOST_AUTO_TEST_CASE(
    test_not_equal,
    *boost::unit_test::description("test operator!=")
    *boost::unit_test::label("opeq")
    *boost::unit_test::depends_on(
        "test_operations/test_operators/test_equal"))
{
    auto p1 = point3d{ 1, 2, 3 };
    auto p2 = point3d{ 3, 2, 1 };
    BOOST_TEST(p1 != p2);
}

BOOST_AUTO_TEST_CASE(test_less)
{
    auto p1 = point3d{ 1, 2, 3 };
    auto p2 = point3d{ 1, 2, 3 };
    auto p3 = point3d{ 3, 2, 1 };
    BOOST_TEST(!(p1 < p2));
    BOOST_TEST(p1 < p3);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
