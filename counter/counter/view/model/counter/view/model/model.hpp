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
    counter::model::model counter;
    colour which_colour;
};
inline model update(model m, const action::action& act)
{
    m.counter = counter::model::update(m.counter, act);
    if (m.counter.value > 0)
        m.which_colour = colour::green;
    else if (m.counter.value < 0)
        m.which_colour = colour::red;
    else
        m.which_colour = colour::grey;
    return m;
};
} // namespace xzr::counter::view::model
