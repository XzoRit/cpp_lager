#pragma once

#include <counter/model/model.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <optional>

namespace xzr::counter::view::console
{
inline void render(const xzr::counter::model::model& a)
{
    std::cout << '\r' << a.value;
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
