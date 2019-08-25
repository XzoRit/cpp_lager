#pragma once

#include <lager/util.hpp>
#include <variant>

namespace xzr
{
namespace lib
{
inline namespace v1
{
struct model
{
  int value{ 0 };
};

struct increment_action
{
};
struct decrement_action
{
};
struct reset_action
{
  int new_value = 0;
};

using action = std::variant<increment_action, decrement_action, reset_action>;

inline const auto update = [](model m, const action& act) {
  return std::visit(
    lager::visitor{ [&m](const increment_action&) {
                     ++m.value;
                     return m;
                   },
                    [&m](const decrement_action&) {
                      --m.value;
                      return m;
                    },
                    [&m](const reset_action& act) {
                      m.value = act.new_value;
                      return m;
                    } },
    act);
};
}
}
}
