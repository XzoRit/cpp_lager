#pragma once

#include <variant>

namespace xzr::counter::action
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
} // namespace xzr::counter::action
namespace xzr::counter::model
{
struct model
{
    int value{0};
};
struct on_action
{
    model operator()(const action::increment&);
    model operator()(const action::decrement&);
    model operator()(const action::reset& act);
    model m{};
};
model update(model m, const action::action& act);
} // namespace xzr::counter::model
