#pragma once

#include <tuple>
#include <variant>

namespace xzr::tennis::action
{
struct player_1_scored
{
};
struct player_2_scored
{
};
using score_action = std::variant<player_1_scored, player_2_scored>;
}
namespace xzr::tennis::model
{
enum class point
{
  Love,
  Fifteen,
  Thirty,
  Forty
};
point operator++(point p)
{
  if (p == point::Love)
    return point::Fifteen;
  if (p == point::Fifteen)
    return point::Thirty;
  if (p == point::Thirty)
    return point::Forty;
  return p;
}
template <class player_id>
struct player
{
  point points { point::Love };
};
template <class player_id_a, class player_id_b>
inline bool operator==(const player<player_id_a>& a, const player<player_id_b>& b)
{
  return a.points == b.points;
}
template <class player_id_a, class player_id_b>
inline bool operator!=(const player<player_id_a>& a, const player<player_id_b>& b)
{
  return !(a == b);
}
struct game
{
  struct player_id_1
  {
  };
  struct player_id_2
  {
  };
  using player_1_or_player_2 = std::variant<player_id_1, player_id_2>;
  struct simple
  {
    player<player_id_1> player_1;
    player<player_id_2> player_2;
  };
  struct forty
  {
    player_1_or_player_2 leading_player {};
    point points_other_player { point::Love };
  };
  struct deuce
  {
  };
  struct advantage
  {
    player_1_or_player_2 leading {};
  };
  struct winner
  {
    player_1_or_player_2 the_one_and_only {};
  };
  using state_type = std::variant<simple, forty, deuce, advantage, winner>;
  state_type state;
};
inline bool operator==(const game::player_id_1& a, const game::player_id_1& b)
{
  return true;
}
inline bool operator!=(const game::player_id_1& a, const game::player_id_1& b)
{
  return !(a == b);
}
inline bool operator==(const game::player_id_2& a, const game::player_id_2& b)
{
  return true;
}
inline bool operator!=(const game::player_id_2& a, const game::player_id_2& b)
{
  return !(a == b);
}
inline bool operator==(const game::simple& a, const game::simple& b)
{
  return std::make_tuple(a.player_1, a.player_2) == std::make_tuple(b.player_1, b.player_2);
}
inline bool operator!=(const game::simple& a, const game::simple& b)
{
  return !(a == b);
}
inline bool operator==(const game::forty& a, const game::forty& b)
{
  return std::make_tuple(a.leading_player, a.points_other_player) == std::make_tuple(b.leading_player, b.points_other_player);
}
inline bool operator!=(const game::forty& a, const game::forty& b)
{
  return !(a == b);
}
inline bool operator==(const game::deuce& a, const game::deuce& b)
{
  return true;
}
inline bool operator!=(const game::deuce& a, const game::deuce& b)
{
  return !(a == b);
}
inline bool operator==(const game::advantage& a, const game::advantage& b)
{
  return a.leading == b.leading;
}
inline bool operator!=(const game::advantage& a, const game::advantage& b)
{
  return !(a == b);
}
inline bool operator==(const game::winner& a, const game::winner& b)
{
  return a.the_one_and_only == b.the_one_and_only;
}
inline bool operator!=(const game::winner& a, const game::winner& b)
{
  return !(a == b);
}
inline bool operator==(const game& a, const game& b)
{
  return a.state == b.state;
}
inline bool operator!=(const game& a, const game& b) { return !(a == b); }
}
namespace xzr::tennis::model::impl
{
bool scorer_gets_forty_points(const game::simple& g, action::player_1_scored)
{
  return g.player_1.points == point::Thirty;
}
bool scorer_gets_forty_points(const game::simple& g, action::player_2_scored)
{
  return g.player_2.points == point::Thirty;
}
game::forty create_forty_game(const game::simple& g, action::player_1_scored)
{
  return { game::player_id_1 {}, g.player_2.points };
}
game::forty create_forty_game(const game::simple& g, action::player_2_scored)
{
  return { game::player_id_2 {}, g.player_1.points };
}
game::winner create_winner_game(const game::forty& g, action::player_1_scored)
{
  return { game::player_id_1 {} };
}
game::winner create_winner_game(const game::forty& g, action::player_2_scored)
{
  return { game::player_id_2 {} };
}
game::advantage create_advantage_game(const game::deuce& g, action::player_1_scored)
{
  return game::advantage { game::player_id_1 {} };
}
game::advantage create_advantage_game(const game::deuce& g, action::player_2_scored)
{
  return game::advantage { game::player_id_2 {} };
}
template <class player_scored>
struct create_deuce_or_winner_game;
template <>
struct create_deuce_or_winner_game<action::player_1_scored>
{
  game::state_type operator()(const game::player_id_1& p) const
  {
    return game::winner { p };
  }
  game::state_type operator()(const game::player_id_2&) const
  {
    return game::deuce {};
  }
};
template <>
struct create_deuce_or_winner_game<action::player_2_scored>
{
  game::state_type operator()(const game::player_id_1&) const
  {
    return game::deuce {};
  }
  game::state_type operator()(const game::player_id_2& p) const
  {
    return game::winner { p };
  }
};
bool is_deuce(const game::forty& g, action::player_1_scored)
{
  return std::get_if<game::player_id_2>(&g.leading_player);
}
bool is_deuce(const game::forty& g, action::player_2_scored)
{
  return std::get_if<game::player_id_1>(&g.leading_player);
}
game::simple inc_score_of(const game::simple& g, action::player_1_scored)
{
  return { { ++g.player_1.points }, g.player_2 };
}
game::simple inc_score_of(const game::simple& g, action::player_2_scored)
{
  return { g.player_1, { ++g.player_2.points } };
}
template <class scoring_player>
struct update_game_state
{
  game operator()(const game::simple& g) const
  {
    if (scorer_gets_forty_points(g, scoring_player {}))
      return game { create_forty_game(g, scoring_player {}) };
    else
      return game { inc_score_of(g, scoring_player {}) };
  }
  game operator()(const game::forty& g) const
  {
    if (is_deuce(g, scoring_player {}))
      return game { game::deuce {} };
    else
      return game { create_winner_game(g, scoring_player {}) };
  }
  game operator()(const game::deuce& g) const
  {
    return game { create_advantage_game(g, scoring_player {}) };
  }
  game operator()(const game::advantage& g) const
  {
    return game { std::visit(create_deuce_or_winner_game<scoring_player> {}, g.leading) };
  }
  game operator()(const game::winner& g) const { return game { g }; }
};
struct apply_score_action
{
  template <class scoring_player>
  game operator()(scoring_player) const
  {
    return std::visit(update_game_state<scoring_player> {}, current_game.state);
  }
  const game& current_game;
};
}
namespace xzr::tennis::model
{
game update(const game& g, const action::score_action& player_scored)
{
  return std::visit(impl::apply_score_action { g }, player_scored);
}
}
