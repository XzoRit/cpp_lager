#include <boost/test/unit_test.hpp>
#include <tennis/model/model.hpp>

namespace xzr::tennis::model
{
std::ostream &operator<<(std::ostream &str, point p)
{
    if (p == point::Love)
        str << "0";
    else if (p == point::Fifteen)
        str << "15";
    else if (p == point::Thirty)
        str << "30";
    else if (p == point::Forty)
        str << "40";
    return str;
}
std::ostream &operator<<(std::ostream &str, const player<game::player_id_1> &p)
{
    str << "player_1: " << p.points;
    return str;
}
std::ostream &operator<<(std::ostream &str, const player<game::player_id_2> &p)
{
    str << "player_2: " << p.points;
    return str;
}
std::ostream &operator<<(std::ostream &str, const game::player_id_1 &)
{
    str << "player_id_1";
    return str;
}
std::ostream &operator<<(std::ostream &str, const game::player_id_2 &)
{
    str << "player_id_2";
    return str;
}
std::ostream &operator<<(std::ostream &str, const game::simple &g)
{
    str << g.player_1 << " vs. " << g.player_2;
    return str;
}
std::ostream &operator<<(std::ostream &str, const game::forty &g)
{
    str << "leading_player: ";
    std::visit([&str](const auto &a) { str << a; }, g.leading_player);
    str << " points_other_player: " << g.points_other_player;
    return str;
}
std::ostream &operator<<(std::ostream &str, game::deuce)
{
    str << "deuce";
    return str;
}
std::ostream &operator<<(std::ostream &str, const game::advantage &g)
{
    str << "advantage: ";
    std::visit([&str](const auto &a) { str << a; }, g.leading);
    return str;
}
std::ostream &operator<<(std::ostream &str, const game::winner &g)
{
    str << "winner ";
    std::visit([&str](const auto &a) { str << a; }, g.the_one_and_only);
    return str;
}
std::ostream &operator<<(std::ostream &str, const game &g)
{
    std::visit([&str](const auto &a) { str << a; }, g.state);
    return str;
}
} // namespace xzr::tennis::model

using xzr::tennis::action::player_1_scored;
using xzr::tennis::action::player_2_scored;
using xzr::tennis::model::game;
using xzr::tennis::model::point;
using xzr::tennis::model::update;

namespace
{
BOOST_AUTO_TEST_SUITE(model_tests)

BOOST_AUTO_TEST_CASE(player_1_scores_and_wins)
{
    const game _1{game::simple{}};
    const game _2{update(_1, player_1_scored{})};
    BOOST_TEST(_2 == (game{game::simple{{point::Fifteen}, {point::Love}}}));
    const game _3{update(_2, player_1_scored{})};
    BOOST_TEST(_3 == (game{game::simple{{point::Thirty}, {point::Love}}}));
    const game _4{update(_3, player_1_scored{})};
    BOOST_TEST(_4 == (game{game::forty{{game::player_id_1{}}, point::Love}}));
    const game _5{update(_4, player_1_scored{})};
    BOOST_TEST(_5 == (game{game::winner{game::player_id_1{}}}));
}
BOOST_AUTO_TEST_CASE(player_2_scores_and_wins)
{
    const game _1{game::simple{}};
    const game _2{update(_1, player_2_scored{})};
    BOOST_TEST(_2 == (game{game::simple{{point::Love}, {point::Fifteen}}}));
    const game _3{update(_2, player_2_scored{})};
    BOOST_TEST(_3 == (game{game::simple{{point::Love}, {point::Thirty}}}));
    const game _4{update(_3, player_2_scored{})};
    BOOST_TEST(_4 == (game{game::forty{{game::player_id_2{}}, point::Love}}));
    const game _5{update(_4, player_2_scored{})};
    BOOST_TEST(_5 == (game{game::winner{game::player_id_2{}}}));
}
BOOST_AUTO_TEST_CASE(forty_deuce)
{
    game forty_love{game::forty{game::player_id_1{}, point::Love}};
    const game forty_fifteen{update(forty_love, player_2_scored{})};
    BOOST_TEST(forty_fifteen == (game{game::forty{game::player_id_1{}, point::Fifteen}}));
    const game forty_thirty{update(forty_fifteen, player_2_scored{})};
    BOOST_TEST(forty_thirty == (game{game::forty{game::player_id_1{}, point::Thirty}}));
    const game deuce{update(forty_thirty, player_2_scored{})};
    BOOST_TEST(deuce == (game{game::deuce{}}));
}
BOOST_AUTO_TEST_CASE(deuce_advantage_deuce)
{
    game g{game::simple{{point::Thirty}, {point::Thirty}}};
    g = update(g, player_1_scored{});

    BOOST_TEST_INFO("deuce");
    const game deuce{update(g, player_2_scored{})};
    BOOST_TEST(deuce == (game{game::deuce{}}));

    BOOST_TEST_INFO("advantage player_1");
    const game advantage_player_1{update(deuce, player_1_scored{})};
    BOOST_TEST(advantage_player_1 == (game{game::advantage{game::player_id_1{}}}));

    BOOST_TEST_INFO("deuce");
    const game deuce_2{update(advantage_player_1, player_2_scored{})};
    BOOST_TEST(deuce_2 == (game{game::deuce{}}));
}
BOOST_AUTO_TEST_CASE(win_for_player_1)
{
    const game advantage_player_1{game::advantage{game::player_id_1{}}};
    const game win_for_player_1{update(advantage_player_1, player_1_scored{})};
    BOOST_TEST(win_for_player_1 == (game{game::winner{game::player_id_1{}}}));
}
BOOST_AUTO_TEST_CASE(win_for_player_2)
{
    const game advantage_player_2{game::advantage{game::player_id_2{}}};
    const game win_for_player_2{update(advantage_player_2, player_2_scored{})};
    BOOST_TEST(win_for_player_2 == (game{game::winner{game::player_id_2{}}}));
}

BOOST_AUTO_TEST_SUITE_END()
} // namespace
