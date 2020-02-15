#pragma once

#include <lager/util.hpp>

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
inline const auto update = [](model m, const action::action &act) {
    return std::visit(lager::visitor{[&m](const action::increment &) {
                                         ++m.value;
                                         return m;
                                     },
                                     [&m](const action::decrement &) {
                                         --m.value;
                                         return m;
                                     },
                                     [&m](const action::reset &act) {
                                         m.value = act.new_value;
                                         return m;
                                     }},
                      act);
};
} // namespace xzr::counter::model
