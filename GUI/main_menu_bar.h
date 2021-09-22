#ifndef INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_MENU_BAR_H_
#define INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_MENU_BAR_H_

#include <iostream>

#include "application_settings.h"
#include "utility.h"

namespace main_menu
{

/// @TODO: Move the texture loading functionality into a separate function
static int logo_width{0};
static int logo_height{0};
static ID3D11ShaderResourceView* logo_texture = nullptr;

static int home_width{0};
static int home_height{0};
static ID3D11ShaderResourceView* home_texture = nullptr;

static int database_width{0};
static int database_height{0};
static ID3D11ShaderResourceView* database_texture = nullptr;

static int qr_width{0};
static int qr_height{0};
static ID3D11ShaderResourceView* qr_texture = nullptr;

void Initialize() {
    /// @TODO: Adjust paths to be relative
    IM_ASSERT(assets::LoadTextureFromFile( "C:/Users/Zvonimir/CLionProjects/InventoryManagement/Assets/VVK_logo_novi.jpg", &logo_texture, &logo_width, &logo_height));
    IM_ASSERT(assets::LoadTextureFromFile( "C:/Users/Zvonimir/CLionProjects/InventoryManagement/Assets/home.png", &home_texture, &home_width, &home_height));
    IM_ASSERT(assets::LoadTextureFromFile( "C:/Users/Zvonimir/CLionProjects/InventoryManagement/Assets/browser.png", &database_texture, &database_width, &database_height));
    IM_ASSERT(assets::LoadTextureFromFile( "C:/Users/Zvonimir/CLionProjects/InventoryManagement/Assets/meetup.png", &qr_texture, &qr_width, &qr_height));
}

void Create()
{
    ImGui::SetNextWindowSize(main_menu::kGSize);
    ImGui::SetNextWindowPos(main_menu::kGPosition);
    ImGui::Begin("Main Menu", nullptr, properties::kGWindowFlags);
    ImGui::Image(static_cast<ImTextureID>(logo_texture), ImVec2(logo_width, logo_height));
    ImGui::ImageButton(static_cast<ImTextureID>(home_texture), ImVec2(home_width, home_height));
    ImGui::ImageButton(static_cast<ImTextureID>(database_texture), ImVec2(database_width, database_height));
    ImGui::ImageButton(static_cast<ImTextureID>(qr_texture), ImVec2(qr_width, qr_height));

    ImGui::End();
}

}  // namespace main_menu

#endif  // INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_MENU_BAR_H_
