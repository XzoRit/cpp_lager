#include <boost/test/unit_test.hpp>

#include <counter/model/model.hpp>
#include <counter/view/model/model.hpp>

namespace
{
BOOST_AUTO_TEST_SUITE(counter_view_model)

BOOST_AUTO_TEST_CASE(update_view_model)
{
    const auto a_model{xzr::counter::view::model::model{0}};
    BOOST_CHECK_EQUAL(a_model.which_colour, xzr::counter::view::model::colour::grey);

    const auto b_model{xzr::counter::view::model::update(a_model, xzr::counter::action::increment{})};
    BOOST_CHECK_EQUAL(b_model.which_colour, xzr::counter::view::model::colour::green);

    const auto c_model{xzr::counter::view::model::update(b_model, xzr::counter::action::decrement{})};
    BOOST_CHECK_EQUAL(c_model.which_colour, xzr::counter::view::model::colour::grey);

    const auto d_model{xzr::counter::view::model::update(c_model, xzr::counter::action::decrement{})};
    BOOST_CHECK_EQUAL(d_model.which_colour, xzr::counter::view::model::colour::red);

    const auto e_model{xzr::counter::view::model::update(d_model, xzr::counter::action::reset{0})};
    BOOST_CHECK_EQUAL(e_model.which_colour, xzr::counter::view::model::colour::grey);
}

BOOST_AUTO_TEST_SUITE_END()
} // namespace
