#include <counter/view/gui/console/console.hpp>

#include <boost/program_options/options_description.hpp>

#include <iostream>

namespace xzr::counter::view::console
{
void render(const xzr::counter::view::model::model& m)
{
    constexpr const char* no_colour = "\033[0m";
    constexpr const char* red = "\033[31m";
    constexpr const char* green = "\033[32m";
    constexpr const char* grey = "\033[37m";
    if (m.which_colour == xzr::counter::view::model::colour::red)
        std::cout << '\r' << red << m.value << no_colour << ' ';
    else if (m.which_colour == xzr::counter::view::model::colour::green)
        std::cout << '\r' << green << m.value << no_colour << ' ';
    else if (m.which_colour == xzr::counter::view::model::colour::grey)
        std::cout << '\r' << grey << m.value << no_colour << ' ';
    else
        std::cout << '\r' << m.value << ' ';
}
} // namespace xzr::counter::view::console
namespace xzr::counter::view::console::menu
{
std::optional<xzr::counter::view::model::action::action> intent(char c)
{
    if (c == '+')
        return xzr::counter::view::model::action::increment{};
    if (c == '-')
        return xzr::counter::view::model::action::decrement{};
    if (c == '=')
        return xzr::counter::view::model::action::reset{0};
    return std::nullopt;
}
void add_options(boost::program_options::options_description& desc)
{
    desc.add_options()("+", "increments counter by 1")("-", "decrements counter by 1")("=", "resets counter to 0");
}
} // namespace xzr::counter::view::console::menu
