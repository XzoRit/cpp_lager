#pragma once

#include <variant>

namespace xzr::counter::model::action
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
} // namespace xzr::counter::model::action
namespace xzr::counter::model
{
struct model
{
    int value{0};
};
model update(model m, const action::action& act);
} // namespace xzr::counter::model
