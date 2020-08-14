#pragma once

#include <iosfwd>
#include <variant>

namespace xzr::counter::view::model::action
{
struct increment
{
};
struct decrement
{
};
struct reset
{
    int new_value{};
};
using action = std::variant<increment, decrement, reset>;
} // namespace xzr::counter::view::model::action
namespace xzr::counter::view::model
{
enum class colour
{
    grey,
    red,
    green
};
std::ostream& operator<<(std::ostream& str, colour c);
struct model
{
    int value{};
    colour which_colour{colour::grey};
};
model update(model m, const action::action& act);
} // namespace xzr::counter::view::model
