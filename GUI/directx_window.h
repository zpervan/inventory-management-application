#ifndef INVENTORYMANAGEMENTAPPLICATION_INITIALIZE_DIRECTX_WINDOW_H
#define INVENTORYMANAGEMENTAPPLICATION_INITIALIZE_DIRECTX_WINDOW_H

#include <iostream>
#include <string>

#include <d3d11.h>
#include <tchar.h>
#include <winuser.h>

#include "../ThirdParty/DearImgui/imgui_impl_dx11.h"
#include "../ThirdParty/DearImgui/imgui_impl_win32.h"

// Forward declarations
static bool CreateDeviceD3D(HWND hWnd);
static void CleanupDeviceD3D();
static void CreateRenderTarget();
static void CleanupRenderTarget();
static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static std::pair<int, int> GetScreenResolution();

namespace window
{
static HWND g_direct_x_window{};
static WNDCLASSEX g_wc{};

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

static std::pair<int, int> g_window_size{GetScreenResolution()};
}  // namespace window

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
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) != 0)
    {
        return 1;
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
            {
                return 0;
            }
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

std::pair<int, int> GetScreenResolution()
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

#endif  // INVENTORYMANAGEMENTAPPLICATION_INITIALIZE_DIRECTX_WINDOW_H
