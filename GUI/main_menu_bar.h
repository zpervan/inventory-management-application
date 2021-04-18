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

void Initialize() {
    /// @TODO: Adjust paths to be relative
    bool ret = assets::LoadTextureFromFile( "C:/msys64/home/zperv/Programming/inventory-management-application/Assets/VVK_logo_novi.jpg", &logo_texture, &logo_width, &logo_height);
    IM_ASSERT(ret);
}

void Create()
{
    ImGui::SetNextWindowSize(main_menu::kGSize);
    ImGui::SetNextWindowPos(main_menu::kGPosition);
    ImGui::Begin("Main Menu", nullptr, properties::kGWindowFlags);
    ImGui::Image(static_cast<ImTextureID>(logo_texture), ImVec2(logo_width, logo_height));

    ImGui::End();
}

}  // namespace main_menu

#endif  // INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_MENU_BAR_H_
