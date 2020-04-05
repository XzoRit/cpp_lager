#include <counter/view/model/model.hpp>

namespace xzr::counter::view::model
{
model update(model m, const action::action& act)
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
