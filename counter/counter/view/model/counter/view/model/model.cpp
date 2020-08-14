#include <counter/view/model/model.hpp>

#include <counter/model/model.hpp>

#include <ostream>

namespace
{
using namespace xzr::counter;
struct map_to_model_action
{
    model::action::action operator()(const view::model::action::increment&)
    {
        return model::action::increment{};
    }
    model::action::action operator()(const view::model::action::decrement&)
    {
        return model::action::decrement{};
    }
    model::action::action operator()(const view::model::action::reset& act)
    {
        return model::action::reset{act.new_value};
    }
};
} // namespace
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
    int value =
        xzr::counter::model::update(xzr::counter::model::model{m.value}, std::visit(map_to_model_action{}, act)).value;
    if (value > 0)
        return {value, colour::green};
    else if (value < 0)
        return {value, colour::red};
    return {value, colour::grey};
};
} // namespace xzr::counter::view::model
