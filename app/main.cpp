#include <boost/program_options.hpp>
#include <lib/lib.hpp>
#include <iostream>
#include <iterator>
#include <optional>

namespace po = boost::program_options;

inline const auto intent = [](auto e) -> std::optional<xzr::lib::action>
{
    if (e == '+') return xzr::lib::increment_action{};
    if (e == '-') return xzr::lib::decrement_action{};
    if (e == '=') return xzr::lib::reset_action{0};
    return std::nullopt;
};

inline const auto render = [](const auto& m)
{
    std::cout << "model.value = " << m.value << '\n';
};

int main(int ac, char* av[])
{
  std::cout << "Hello app\n";

  try
  {
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message");

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) { std::cout << desc << "\n"; }
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

  char c{};
  xzr::lib::model m{};
  while(std::cin >> c)
  {
      if (c == 'q') break;
      if (const auto act = intent(c))
      {
          m = xzr::lib::update(m, *act);
          render(m);
      }
  }

  return 0;
}
