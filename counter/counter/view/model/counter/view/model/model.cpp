#include <counter/view/model/model.hpp>

#include <ostream>

namespace xzr::counter::view::model
{
std::ostream& operator<<(std::ostream& str, colour c)
{
    switch (c)
    {
    case colour::red:
        str << "red";
        break;
    case colour::green:
        str << "green";
        break;
    case colour::grey:
        str << "grey";
        break;
    default:
        str << "unknown";
        break;
    }
    return str;
}
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
