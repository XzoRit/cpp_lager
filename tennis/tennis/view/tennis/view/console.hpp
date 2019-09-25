#include <tennis/model/model.hpp>
#include <ostream>
#include <sstream>
#include <string>

namespace xzr::tennis::view::console
{
struct render
{
  std::string player_1 {};
  std::string player_2 {};
  struct player_to_string
  {
    const render* the_render;
    std::string operator()(const model::game::player_id_1&) const
    {
      return the_render->player_1;
    }
      std::string operator()(const model::game::player_id_2&) const
    {
      return the_render->player_2;
    }
  };
  std::ostream& draw(std::ostream& str, const model::point& p) const
  {
    if (p == model::point::Love)
      str << "0";
    else if (p == model::point::Fifteen)
      str << "15";
    else if (p == model::point::Thirty)
      str << "30";
    else if (p == model::point::Forty)
      str << "40";
    return str;
  }
  std::ostream& draw(std::ostream& str, const model::game::simple& g) const
  {
      str << player_1 << ": ";
      draw(str, g.player_1.points);
      str << " vs. " << player_2 << ": ";
      draw(str, g.player_2.points);
      str << '\n';
    return str;
  }
  std::ostream& draw(std::ostream& str, const model::game::forty& g) const
  {
    if (std::get_if<model::game::player_id_1>(&g.leading_player))
    {
        str << visit(player_to_string { this }, g.leading_player) << ": ";
        draw(str, model::point::Forty);
        str << " vs. " << player_2 << ": ";
        draw(str, g.points_other_player);
    }
    else
    {
        str << player_1 << ": ";
        draw(str, g.points_other_player);
        str  << " vs. " << visit(player_to_string { this }, g.leading_player) << ": ";
        draw(str, model::point::Forty);
    }
    str << '\n';
    return str;
  }
  std::ostream& draw(std::ostream& str, model::game::deuce) const
  {
    str << "deuce\n";
    return str;
  }
  std::ostream& draw(std::ostream& str, const model::game::advantage& g) const
  {
    str << "advantage " << visit(player_to_string { this }, g.leading) << "\n";
    return str;
  }
  std::ostream& draw(std::ostream& str, const model::game::winner& g) const
  {
    str << visit(player_to_string { this }, g.the_one_and_only) << ": won\n";
    return str;
  }
    std::string draw(const model::game& g) const
  {
    std::stringstream str;
    visit([this, &str](const auto& a) { draw(str, a); }, g.state);
    return str.str();
  }
};
}
