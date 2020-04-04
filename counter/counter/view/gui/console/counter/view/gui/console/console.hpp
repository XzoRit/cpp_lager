#pragma once

#include <counter/view/model/model.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <optional>

namespace xzr::counter::view::console
{
inline void render(const xzr::counter::view::model::model& m)
{
    constexpr const char* no_colour = "\033[0m";
    constexpr const char* red = "\033[31m";
    constexpr const char* green = "\033[32m";
    constexpr const char* grey = "\033[37m";
    if (m.which_colour == xzr::counter::view::model::colour::red)
        std::cout << '\r' << red << m.counter.value << no_colour << ' ';
    else if (m.which_colour == xzr::counter::view::model::colour::green)
        std::cout << '\r' << green << m.counter.value << no_colour << ' ';
    else if (m.which_colour == xzr::counter::view::model::colour::grey)
        std::cout << '\r' << grey << m.counter.value << no_colour << ' ';
    else
        std::cout << '\r' << m.counter.value << ' ';
}
} // namespace xzr::counter::view::console
namespace xzr::counter::view::console::menu
{
inline std::optional<xzr::counter::action::action> intent(char c)
{
    if (c == '+')
        return xzr::counter::action::increment{};
    if (c == '-')
        return xzr::counter::action::decrement{};
    if (c == '=')
        return xzr::counter::action::reset{0};
    return std::nullopt;
}
inline void add_options(boost::program_options::options_description& desc)
{
    desc.add_options()("+", "increments counter by 1")("-", "decrements counter by 1")("=", "resets counter to 0");
}
} // namespace xzr::counter::view::console::menu
