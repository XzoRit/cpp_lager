#include <boost/test/unit_test.hpp>

#include <counter/model/model.hpp>

namespace
{
using xzr::counter::action::decrement;
using xzr::counter::action::increment;
using xzr::counter::action::reset;
using xzr::counter::model::model;
using xzr::counter::model::update;

BOOST_AUTO_TEST_SUITE(counter_model)

BOOST_AUTO_TEST_CASE(update_model)
{
    const auto a_model{model{0}};

    const auto b_model{update(a_model, increment{})};
    BOOST_TEST(b_model.value == a_model.value + 1);

    const auto c_model{update(b_model, decrement{})};
    BOOST_TEST(c_model.value == b_model.value - 1);

    const auto d_model{update(c_model, reset{5})};
    BOOST_TEST(d_model.value == 5);

    const auto e_model{update(d_model, reset{})};
    BOOST_TEST(e_model.value == 0);
}

BOOST_AUTO_TEST_SUITE_END()
} // namespace
