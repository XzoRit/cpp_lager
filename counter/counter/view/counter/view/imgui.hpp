#pragma once

#include <counter/model/model.hpp>

#include <lager/context.hpp>

#include <imgui.h>

namespace xzr::counter::view::imgui
{
inline void draw(lager::context<xzr::counter::action::action> ctx, xzr::counter::model::model m)
{
    ImGui::Begin("Counter");

    ImGui::AlignTextToFramePadding();
    ImGui::Text("Hold to repeat:");
    ImGui::SameLine();

    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    ImGui::Text("%d", m.value);
    ImGui::PushButtonRepeat(true);
    if (ImGui::ArrowButton("##down", ImGuiDir_Down))
        ctx.dispatch(xzr::counter::action::decrement{});
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##up", ImGuiDir_Up))
        ctx.dispatch(xzr::counter::action::increment{});
    ImGui::PopButtonRepeat();
    ImGui::SameLine();
    if (ImGui::Button("reset"))
        ctx.dispatch(xzr::counter::action::reset{});

    ImGui::End();
}
} // namespace xzr::counter::view::imgui
