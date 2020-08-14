#include <counter/model/model.hpp>

namespace
{
using namespace xzr::counter::model::action;
using namespace xzr::counter::model;
struct on_action
{
    model operator()(const increment&);
    model operator()(const decrement&);
    model operator()(const reset& act);
    model m{};
};
model on_action::operator()(const increment&)
{
    ++m.value;
    return m;
}
model on_action::operator()(const decrement&)
{
    --m.value;
    return m;
}
model on_action::operator()(const reset& act)
{
    m.value = act.new_value;
    return m;
}
} // namespace
namespace xzr::counter::model
{
model update(model m, const action::action& act)
{
    return std::visit(on_action{m}, act);
}
} // namespace xzr::counter::model
