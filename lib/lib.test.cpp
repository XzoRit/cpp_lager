#include <boost/test/unit_test.hpp>
#include <lib/lib.hpp>

namespace
{
using xzr::lib::decrement_action;
using xzr::lib::increment_action;
using xzr::lib::reset_action;
using xzr::lib::model;
using xzr::lib::update;

BOOST_AUTO_TEST_SUITE(lib_tests)

BOOST_AUTO_TEST_CASE(lib_update)
{
  const auto a_model{ model{ 0 } };

  const auto b_model{ update(a_model, increment_action{}) };
  BOOST_TEST(b_model.value == a_model.value + 1);

  const auto c_model{ update(b_model, decrement_action{}) };
  BOOST_TEST(c_model.value == b_model.value - 1);

  const auto d_model{ update(c_model, reset_action{ 5 }) };
  BOOST_TEST(d_model.value == 5);
}

BOOST_AUTO_TEST_SUITE_END()
}
