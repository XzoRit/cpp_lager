#include <boost/test/unit_test.hpp>
#include <lib/lib.hpp>

namespace
{
using xzr::lib::model;
using xzr::lib::update;
using xzr::lib::increment_action;

BOOST_AUTO_TEST_SUITE(lib_tests)

BOOST_AUTO_TEST_CASE(lib_add)
{
  const auto old_model{ model{ 0 } };
  const auto new_model{ update(old_model, increment_action{}) };
  BOOST_TEST(new_model.value == old_model.value + 1);
}

BOOST_AUTO_TEST_SUITE_END()
}
