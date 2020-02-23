#include <imgui.h>

#include <stdexcept>
#include <string>

namespace xzr::counter::view::imgui
{
void run()
{
    {
        ImGui::BeginChild("tennis field");
        ImGuiIO &io = ImGui::GetIO();
        ImDrawList *draw_list = ImGui::GetWindowDrawList();

        const ImColor color = ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        const ImDrawCornerFlags corners_none = 0;
        const float thickness = 10.0f;
        const float rounding = 0.0f;
        const ImVec2 p = ImVec2(0, 0);

        draw_list->AddRect(ImVec2(p.x + 10, p.y + 10), ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight()), color,
                           rounding, corners_none, thickness);

        const float x = p.x + 4.0f;
        static float y = p.y + 4.0f;
        const float width = 25.0f;
        const float height = 100.0f;
        draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + width, y + height), color);

        const int key_down{81};
        const int key_up{82};
        if (io.KeysDownDuration[key_up] >= 0.0f)
        {
            y -= 10;
        }
        if (io.KeysDownDuration[key_down] >= 0.0f)
        {
            y += 10;
        }
        ImGui::EndChild();
    }
}
} // namespace xzr::counter::view::imgui
