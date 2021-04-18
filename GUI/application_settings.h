#ifndef INVENTORYMANAGEMENTAPPLICATION_IMGUI_CONTENT_WINDOW_H
#define INVENTORYMANAGEMENTAPPLICATION_IMGUI_CONTENT_WINDOW_H

#include "../ThirdParty/DearImgui/imgui.h"
#include "directx_window.h"

namespace properties {
const ImVec4 kGClearColor {0.45f, 0.55f, 0.60f, 1.00f};
const ImGuiWindowFlags kGWindowFlags {ImGuiWindowFlags_NoTitleBar + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoCollapse + ImGuiWindowFlags_NoMove};
}

namespace main_menu {
const ImVec2 kGSize {static_cast<float>(GetScreenResolution().first) * 0.15f, static_cast<float>(GetScreenResolution().second)};
/// @TODO: Make main menu position calculated dynamically (no hardcoded values)
const ImVec2 kGPosition{0.0, 22}; // y = font size (16) + frame padding (6)
}

#endif //INVENTORYMANAGEMENTAPPLICATION_IMGUI_CONTENT_WINDOW_H
