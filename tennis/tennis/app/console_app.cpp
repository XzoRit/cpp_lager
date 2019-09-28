#include <tennis/model/model.hpp>
#include <tennis/view/console.hpp>

#include <lager/event_loop/manual.hpp>
#include <lager/store.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <iterator>
#include <optional>

namespace po = boost::program_options;

inline const auto intent = [](auto e) -> std::optional<xzr::tennis::action::score_action> {
  if (e == '1')
    return xzr::tennis::action::player_1_scored{};
  if (e == '2')
    return xzr::tennis::action::player_2_scored{};
  return std::nullopt;
};

int main(int ac, char* av[])
{
  std::cout << "tennis console app\n";

  try
  {
    po::options_description desc("tennis console app");
    desc.add_options()("help", "produce help message")("1", "player 1 scored")(
      "2", "player 2 scored")("q", "quits application");

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
      std::cout << desc << "\n";
      return 0;
    }

    xzr::tennis::view::console::render tennis_render{ "Alice", "Bob" };
    auto store = lager::make_store<xzr::tennis::action::score_action>(
      xzr::tennis::model::game{},
      xzr::tennis::model::update,
      [&tennis_render](const auto& model) {
        tennis_render.draw(model);
      },
      lager::with_manual_event_loop{});

    auto c = char{};
    while (std::cin >> c)
    {
      if (c == 'q')
        break;
      if (const auto act = intent(c))
      {
        store.dispatch(*act);
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "Exception of unknown type!\n";
  }

  return 0;
}