#ifndef INVENTORYMANAGEMENTAPPLICATION_INITIALIZE_DIRECTX_WINDOW_H
#define INVENTORYMANAGEMENTAPPLICATION_INITIALIZE_DIRECTX_WINDOW_H

#include "../ThirdParty/Imgui/imgui_impl_dx11.h"
#include "../ThirdParty/Imgui/imgui_impl_win32.h"

#include "utility.h"
#include "application_settings.h"

#include <string>
#include <d3d11.h>
#include <tchar.h>

// Forward declarations of helper functions
static bool CreateDeviceD3D(HWND hWnd);
static void CleanupDeviceD3D();
static void CreateRenderTarget();
static void CleanupRenderTarget();
static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static void CreateDirectXWindow(const std::string& application_title)
{
    window::g_wc = WNDCLASSEX{sizeof(WNDCLASSEX),
                              CS_CLASSDC,
                              WndProc,
                              0L,
                              0L,
                              GetModuleHandle(nullptr),
                              nullptr,
                              nullptr,
                              nullptr,
                              nullptr,
                              _T(application_title.c_str()),
                              nullptr};

    ::RegisterClassEx(&window::g_wc);

    const auto screen_resolution = GetScreenResolution();

    window::g_direct_x_window = ::CreateWindow(window::g_wc.lpszClassName,
                                               _T(application_title.c_str()),
                                               WS_OVERLAPPEDWINDOW,
                                               0,
                                               0,
                                               screen_resolution.first,
                                               screen_resolution.second,
                                               nullptr,
                                               nullptr,
                                               window::g_wc.hInstance,
                                               nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(window::g_direct_x_window))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(window::g_wc.lpszClassName, window::g_wc.hInstance);
        return;
    }

    ::ShowWindow(window::g_direct_x_window, SW_SHOWDEFAULT);
    ::UpdateWindow(window::g_direct_x_window);
}

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    // createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_0,
    };

    if (D3D11CreateDeviceAndSwapChain(NULL,
                                      D3D_DRIVER_TYPE_HARDWARE,
                                      NULL,
                                      createDeviceFlags,
                                      featureLevelArray,
                                      2,
                                      D3D11_SDK_VERSION,
                                      &sd,
                                      &window::g_pSwapChain,
                                      &window::g_pd3dDevice,
                                      &featureLevel,
                                      &window::g_pd3dDeviceContext) != S_OK)
    {
        return false;
    }

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (window::g_pSwapChain != nullptr)
    {
        window::g_pSwapChain->Release();
        window::g_pSwapChain = NULL;
    }
    if (window::g_pd3dDeviceContext != nullptr)
    {
        window::g_pd3dDeviceContext->Release();
        window::g_pd3dDeviceContext = NULL;
    }
    if (window::g_pd3dDevice != nullptr)
    {
        window::g_pd3dDevice->Release();
        window::g_pd3dDevice = NULL;
    }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    window::g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    window::g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &window::g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (window::g_mainRenderTargetView)
    {
        window::g_mainRenderTargetView->Release();
        window::g_mainRenderTargetView = NULL;
    }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    {
        return true;
    }

    switch (msg)
    {
        case WM_SIZE:
            if (window::g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
            {
                CleanupRenderTarget();
                window::g_pSwapChain->ResizeBuffers(
                    0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
                CreateRenderTarget();
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU)  // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

static void InitializeImguiContext()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    /// @TODO: Adjust paths to be relative
//    io.Fonts->AddFontFromFileTTF(
//        R"(C:\msys64\home\zperv\Programming\inventory-management-application\ThirdParty\DearImgui\misc\fonts\Karla-Regular.ttf)",
//        16.0f);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(window::g_direct_x_window);
    ImGui_ImplDX11_Init(window::g_pd3dDevice, window::g_pd3dDeviceContext);
}

static void CheckForEvents()
{
    MSG msg;
    while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE) != 0)
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
        {
            window::done = true;
        }
    }
}

static void StartDearImguiFrame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

static void Render()
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

static void Destroy()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(window::g_direct_x_window);
    ::UnregisterClass(window::g_wc.lpszClassName, window::g_wc.hInstance);
}
#endif  // INVENTORYMANAGEMENTAPPLICATION_INITIALIZE_DIRECTX_WINDOW_H
