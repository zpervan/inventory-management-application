#ifndef INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_WINDOW_H_
#define INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_WINDOW_H_

#include "../Backend/DatabaseQuery/database_query.h"
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
inline static DatabaseQuery db;
inline static DatabaseResponse database_response{};

void Initialize()
{
    db.Connect();
    database_response = db.FetchFromDatabase("inventory.pc.borrowed");
}

void Create()
{
    assets::LoadTextureFromFile(
        "C:\\Users\\Zvonimir\\CLionProjects\\InventoryManagement\\Assets\\plus.png",
        &add_texture,
        &add_width,
        &add_height);
    ImGui::SetNextWindowSize(main_window::kGSize);
    ImGui::SetNextWindowPos(main_window::kGPosition);
    ImGui::Begin("Main Window", nullptr, properties::kGWindowFlags);
    ImGui::InputTextWithHint("", "Unesi pojam...", input.data(), 64);
    ImGui::SameLine();
    ImGui::ImageButton(static_cast<ImTextureID>(add_texture), ImVec2(add_width, add_height));

    if (ImGui::BeginTable("database_table", database_response.database_header.size(), flags))
    {
        for (const auto& column_name : database_response.database_header)
        {
            ImGui::TableSetupColumn(column_name.data());
        }
        ImGui::TableHeadersRow();

        for (const auto& values : database_response.database_values)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < values.size(); column++)
            {
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("%s", values.at(column).c_str());
            }
        }
        ImGui::EndTable();
    }
    ImGui::End();
}
}  // namespace main_window

#endif  // INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_WINDOW_H_
