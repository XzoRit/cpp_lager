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
    model operator()(const action::increment &)
    {
        ++m.value;
        return m;
    }
    model operator()(const action::decrement &)
    {
        --m.value;
        return m;
    }
    model operator()(const action::reset &act)
    {
        m.value = act.new_value;
        return m;
    }
    model m{};
};
model update(model m, const action::action &act)
{
    return std::visit(on_action{m}, act);
};
} // namespace xzr::counter::model
