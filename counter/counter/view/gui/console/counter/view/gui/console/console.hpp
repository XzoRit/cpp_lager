#pragma once

#include <counter/view/model/model.hpp>

#include <optional>

namespace boost::program_options
{
class options_description;
}
namespace xzr::counter::view::model
{
struct model;
}
namespace xzr::counter::view::console
{
void render(const xzr::counter::view::model::model& m);
} // namespace xzr::counter::view::console
namespace xzr::counter::view::console::menu
{
std::optional<xzr::counter::view::model::action::action> intent(char c);
void add_options(boost::program_options::options_description& desc);
} // namespace xzr::counter::view::console::menu
