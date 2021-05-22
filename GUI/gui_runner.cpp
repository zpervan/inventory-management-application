#include "gui_runner.h"

#include <d3d10.h>

#include "application_settings.h"
#include "directx_window.h"
#include "main_menu_bar.h"
#include "main_window.h"
#include "top_menu_bar.h"

void Runner::Run()
{
    CreateDirectXWindow(application_title);
    InitializeImguiContext();
    main_menu::Initialize();
    main_window::Initialize();

    while (!done_)
    {
        CheckForEvents();
        if (done_)
        {
            break;
        }

        StartDearImguiFrame();

        /** GUI Components START **/
        menu_bar::Create();
        main_menu::Create();
        main_window::Create();
        /** GUI Components END **/

        Render();
    }

    Destroy();
}

void Runner::InitializeImguiContext()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    /// @TODO: Adjust paths to be relative
    io.Fonts->AddFontFromFileTTF(
        R"(C:\msys64\home\zperv\Programming\inventory-management-application\ThirdParty\DearImgui\misc\fonts\Karla-Regular.ttf)",
        16.0f);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(window::g_direct_x_window);
    ImGui_ImplDX11_Init(window::g_pd3dDevice, window::g_pd3dDeviceContext);
}

void Runner::CheckForEvents()
{
    MSG msg;
    while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE) != 0)
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
        {
            done_ = true;
        }
    }
}

void Runner::StartDearImguiFrame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void Runner::Render()
{
    ImGui::Render();

    const float clear_color_with_alpha[4] = {properties::kGClearColor.x * properties::kGClearColor.w,
                                             properties::kGClearColor.y * properties::kGClearColor.w,
                                             properties::kGClearColor.z * properties::kGClearColor.w,
                                             properties::kGClearColor.w};

    window::g_pd3dDeviceContext->OMSetRenderTargets(1, &window::g_mainRenderTargetView, NULL);
    window::g_pd3dDeviceContext->ClearRenderTargetView(window::g_mainRenderTargetView, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    window::g_pSwapChain->Present(1, 0);  // Present with vsync
    // g_pSwapChain->Present(0, 0); // Present without vsync
}

void Runner::Destroy()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(window::g_direct_x_window);
    ::UnregisterClass(window::g_wc.lpszClassName, window::g_wc.hInstance);
}
