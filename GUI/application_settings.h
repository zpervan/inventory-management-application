#ifndef INVENTORYMANAGEMENTAPPLICATION_IMGUI_CONTENT_WINDOW_H
#define INVENTORYMANAGEMENTAPPLICATION_IMGUI_CONTENT_WINDOW_H

#include <utility>
#include <d3d11.h>

#include "../ThirdParty/Imgui/imgui.h"

static std::pair<int, int> GetScreenResolution()
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    return {desktop.right, desktop.bottom};
}

namespace properties
{
const ImVec4 kGClearColor{0.45f, 0.55f, 0.60f, 1.00f};
const ImGuiWindowFlags kGWindowFlags{ImGuiWindowFlags_NoTitleBar + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoCollapse + ImGuiWindowFlags_NoMove};
}  // namespace properties

namespace main_menu
{
const ImVec2 kGSize{static_cast<float>(GetScreenResolution().first) * 0.15f, static_cast<float>(GetScreenResolution().second)};
/// @TODO: Make main menu position calculated dynamically (no hardcoded values)
const ImVec2 kGPosition{0.0, 22};  // y = font size (16) + frame padding (6)
}  // namespace main_menu

namespace main_window
{
const ImVec2 kGSize{static_cast<float>(GetScreenResolution().first) - main_menu::kGSize.x, static_cast<float>(GetScreenResolution().second)};
const ImVec2 kGPosition{main_menu::kGSize.x, main_menu::kGPosition.y};
}  // namespace main_window

namespace window
{
static HWND g_direct_x_window{};
static WNDCLASSEX g_wc{};
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
static bool done{false};
}  // namespace window

#endif  // INVENTORYMANAGEMENTAPPLICATION_IMGUI_CONTENT_WINDOW_H
