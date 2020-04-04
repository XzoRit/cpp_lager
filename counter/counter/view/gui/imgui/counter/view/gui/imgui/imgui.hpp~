#pragma once

#include <counter/view/model/model.hpp>

#include <lager/context.hpp>

#include <imgui.h>

namespace xzr::counter::view::imgui
{
inline void draw(lager::context<xzr::counter::action::action> ctx, xzr::counter::view::model::model m)
{
    ImGui::Begin("Counter");

    ImGui::Text("Hold to repeat");

    ImGui::PushButtonRepeat(true);
    if (ImGui::ArrowButton("##down", ImGuiDir_Down))
        ctx.dispatch(xzr::counter::action::decrement{});

    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    if (ImGui::ArrowButton("##up", ImGuiDir_Up))
        ctx.dispatch(xzr::counter::action::increment{});
    ImGui::PopButtonRepeat();

    ImGui::SameLine();
    if (ImGui::Button("reset"))
        ctx.dispatch(xzr::counter::action::reset{0});

    ImGui::SameLine();
    if (m.which_colour == xzr::counter::view::model::colour::red)
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%d", m.counter.value);
    else if (m.which_colour == xzr::counter::view::model::colour::green)
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", m.counter.value);
    else if (m.which_colour == xzr::counter::view::model::colour::grey)
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "%d", m.counter.value);
    else
        ImGui::Text("%d", m.counter.value);

    ImGui::End();
}
} // namespace xzr::counter::view::imgui
