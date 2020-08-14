#pragma once

#include <counter/view/model/model.hpp>

#include <lager/context.hpp>

namespace xzr::counter::view::model
{
struct model;
}
namespace xzr::counter::view::imgui
{
void draw(lager::context<xzr::counter::view::model::action::action> ctx, xzr::counter::view::model::model m);
} // namespace xzr::counter::view::imgui
