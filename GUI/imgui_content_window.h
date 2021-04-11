#ifndef INVENTORYMANAGEMENTAPPLICATION_IMGUI_CONTENT_WINDOW_H
#define INVENTORYMANAGEMENTAPPLICATION_IMGUI_CONTENT_WINDOW_H

#include <d3d10.h>
#include "../ThirdParty/DearImgui/imgui.h"

namespace properties {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

inline void SetupDearImguiContext(HWND *directx_application_window, ID3D10Device *pd3d_device) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(directx_application_window);
    ImGui_ImplDX10_Init(pd3d_device);
}


#endif //INVENTORYMANAGEMENTAPPLICATION_IMGUI_CONTENT_WINDOW_H
