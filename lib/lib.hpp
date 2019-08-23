#pragma once

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
const auto update = [](model m, const action& act) {
  return std::visit([&m](const auto&) { return ++m.value, m; }, act);
};
}
}
}
