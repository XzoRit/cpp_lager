#include <boost/test/unit_test.hpp>
#include <string>
#include <tennis/view/console.hpp>

namespace
{
using namespace std::string_literals;

using xzr::tennis::action::player_1_scored;
using xzr::tennis::action::player_2_scored;
using xzr::tennis::model::game;
using xzr::tennis::model::point;
using xzr::tennis::view::console::render;

const auto player_1_name { std::string { "john" } };
const auto player_2_name { std::string { "jane" } };
const render r { player_1_name, player_2_name };

BOOST_AUTO_TEST_SUITE(console_tests)

BOOST_AUTO_TEST_CASE(player_1_wins_simple_game)
{
  game g {};

  auto a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": 0 vs. " + player_2_name + ": 0\n");

  g = update(g, player_1_scored {});
  a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": 15 vs. " + player_2_name + ": 0\n");

  BOOST_TEST_INFO("scores twice");
  g = update(g, player_1_scored {});
  a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": 30 vs. " + player_2_name + ": 0\n");

  BOOST_TEST_INFO("scores thrice");
  g = update(g, player_1_scored {});
  a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": 40 vs. " + player_2_name + ": 0\n");

  BOOST_TEST_INFO("player_1 won");
  g = update(g, player_1_scored {});
  a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": won\n");
}
BOOST_AUTO_TEST_CASE(player_2_wins_simple_game)
{
  game g {};

  auto a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": 0 vs. " + player_2_name + ": 0\n");

  BOOST_TEST_INFO("player_2 scores once");
  g = update(g, player_2_scored {});
  a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": 0 vs. " + player_2_name + ": 15\n");

  BOOST_TEST_INFO("scores twice");
  g = update(g, player_2_scored {});
  a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": 0 vs. " + player_2_name + ": 30\n");

  BOOST_TEST_INFO("scores thrice");
  g = update(g, player_2_scored {});
  a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": 0 vs. " + player_2_name + ": 40\n");

  BOOST_TEST_INFO("player_2 won");
  g = update(g, player_2_scored {});
  a = r.draw(g);
  BOOST_TEST(a == "" + player_2_name + ": won\n");
}
BOOST_AUTO_TEST_CASE(deuce_advantage_deuce_win_for_player_1)
{
  game g { game::deuce {} };

  BOOST_TEST_INFO("deuce");
  auto a = r.draw(g);
  BOOST_TEST(a == "deuce\n");

  BOOST_TEST_INFO("advantage " + player_1_name);
  g = update(g, player_1_scored {});
  a = r.draw(g);
  BOOST_TEST(a == "advantage " + player_1_name + "\n");

  BOOST_TEST_INFO("deuce");
  g = update(g, player_2_scored {});
  a = r.draw(g);
  BOOST_TEST(a == "deuce\n");

  BOOST_TEST_INFO("player_1 will win");
  BOOST_TEST_INFO("advantage " + player_1_name + "");
  g = update(g, player_1_scored {});
  a = r.draw(g);
  BOOST_TEST(a == "advantage " + player_1_name + "\n");

  BOOST_TEST_INFO("winner " + player_1_name);
  g = update(g, player_1_scored {});
  a = r.draw(g);
  BOOST_TEST(a == player_1_name + ": won\n");
}
BOOST_AUTO_TEST_CASE(deuce_advantage_win_for_player_2)
{
  game g { game::deuce {} };

  BOOST_TEST_INFO("advantage " + player_2_name + "");
  g = update(g, player_2_scored {});
  auto a = r.draw(g);
  BOOST_TEST(a == "advantage " + player_2_name + "\n");

  BOOST_TEST_INFO("winner " + player_2_name);
  g = update(g, player_2_scored {});
  a = r.draw(g);
  BOOST_TEST(a == "" + player_2_name + ": won\n");
}

BOOST_AUTO_TEST_SUITE_END()
}
