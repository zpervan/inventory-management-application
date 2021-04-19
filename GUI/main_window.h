#ifndef INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_WINDOW_H_
#define INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_WINDOW_H_

#include "application_settings.h"
#include "utility.h"

namespace main_window
{

/// @TODO: Move to a setting file
std::string input{};
static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;

static int add_width{0};
static int add_height{0};
static ID3D11ShaderResourceView* add_texture = nullptr;

void Create()
{
    assets::LoadTextureFromFile("C:\\msys64\\home\\zperv\\Programming\\inventory-management-application\\Assets\\plus.png", &add_texture, &add_width, &add_height);
    ImGui::SetNextWindowSize(main_window::kGSize);
    ImGui::SetNextWindowPos(main_window::kGPosition);
    ImGui::Begin("Main Window", nullptr, properties::kGWindowFlags);
    ImGui::InputTextWithHint("", "Unesi pojam...", input.data(), 64);
    ImGui::SameLine();
    ImGui::ImageButton(static_cast<ImTextureID>(add_texture), ImVec2(add_width, add_height));

    if (ImGui::BeginTable("table1", 3, flags))
    {
        for (int row = 0; row < 5; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 3; column++)
            {
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("Hello %d,%d", column, row);
            }
        }
        ImGui::EndTable();
    }
    ImGui::End();
}
}  // namespace main_window

#endif  // INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_WINDOW_H_
