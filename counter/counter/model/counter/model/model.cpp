#include <counter/model/model.hpp>

namespace xzr::counter::model
{
model on_action::operator()(const action::increment&)
{
    ++m.value;
    return m;
}
model on_action::operator()(const action::decrement&)
{
    --m.value;
    return m;
}
model on_action::operator()(const action::reset& act)
{
    m.value = act.new_value;
    return m;
}
model update(model m, const action::action& act)
{
    return std::visit(on_action{m}, act);
}
} // namespace xzr::counter::model
