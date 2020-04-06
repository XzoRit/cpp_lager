#pragma once

#include <counter/model/model.hpp>

#include <iosfwd>

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
    counter::model::model counter{};
    colour which_colour{colour::grey};
};
model update(model m, const action::action& act);
} // namespace xzr::counter::view::model
