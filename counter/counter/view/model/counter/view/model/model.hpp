#pragma once

#include <counter/model/model.hpp>

namespace xzr::counter::view::model
{
enum class colour
{
    grey,
    red,
    green
};
struct model
{
    counter::model::model counter{};
    colour which_colour{colour::grey};
};
model update(model m, const action::action& act);
} // namespace xzr::counter::view::model
