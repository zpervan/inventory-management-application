#ifndef INVENTORYMANAGEMENTAPPLICATION_INITIALIZE_DIRECTX_WINDOW_H
#define INVENTORYMANAGEMENTAPPLICATION_INITIALIZE_DIRECTX_WINDOW_H

#include "../ThirdParty/DearImgui/imgui_impl_dx10.h"
#include "../ThirdParty/DearImgui/imgui_impl_win32.h"

#include <d3d10.h>
#include <tchar.h>
#include <string>

namespace window {
static HWND g_direct_x_window{};
static WNDCLASSEX g_wc{};
static ID3D10Device *g_pd3d_device{nullptr};
static IDXGISwapChain *g_p_swap_chain{nullptr};
static ID3D10RenderTargetView *g_main_render_target_view{nullptr};
}

// Forward declarations
bool CreateDeviceD3D();

void CreateRenderTarget();

void CleanupRenderTarget();

void CleanupDeviceD3D();

LRESULT WndProc(HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param);

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

inline void CreateDirectXWindow(const std::string &application_title) {
  window::g_wc = WNDCLASSEX{sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr),
                            nullptr, nullptr, nullptr, nullptr, _T(application_title.c_str()), nullptr};

  ::RegisterClassEx(&window::g_wc);

  window::g_direct_x_window = ::CreateWindow(window::g_wc.lpszClassName, _T(application_title.c_str()),
                                             WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr,
                                             window::g_wc.hInstance, nullptr);

  // Initialize Direct3D
  if (!CreateDeviceD3D()) {
    CleanupDeviceD3D();
    ::UnregisterClass(window::g_wc.lpszClassName, window::g_wc.hInstance);
  }

  ::ShowWindow(window::g_direct_x_window, SW_SHOWDEFAULT);
  ::UpdateWindow(window::g_direct_x_window);
}

inline bool CreateDeviceD3D() {
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
  sd.OutputWindow = window::g_direct_x_window;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  UINT create_device_flags = 0;

  if (D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, create_device_flags, D3D10_SDK_VERSION,
                                    &sd,
                                    &window::g_p_swap_chain, &window::g_pd3d_device) != S_OK) {
    return false;
  }

  CreateRenderTarget();
  return true;
}

inline void CreateRenderTarget() {
  ID3D10Texture2D *p_back_buffer;
  window::g_p_swap_chain->GetBuffer(0, IID_PPV_ARGS(&p_back_buffer));
  window::g_pd3d_device->CreateRenderTargetView(p_back_buffer, nullptr, &window::g_main_render_target_view);
  p_back_buffer->Release();
}

inline void CleanupDeviceD3D() {
  CleanupRenderTarget();

  if (window::g_p_swap_chain != nullptr) {
    window::g_p_swap_chain->Release();
    window::g_p_swap_chain = nullptr;
  }

  if (window::g_pd3d_device != nullptr) {
    window::g_pd3d_device->Release();
    window::g_pd3d_device = nullptr;
  }
}

inline void CleanupRenderTarget() {
  ID3D10Texture2D *pBackBuffer;
  window::g_p_swap_chain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
  window::g_pd3d_device->CreateRenderTargetView(pBackBuffer, nullptr, &window::g_main_render_target_view);
  pBackBuffer->Release();
}

inline LRESULT WndProc(HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param) {
  if (ImGui_ImplWin32_WndProcHandler(h_wnd, msg, w_param, l_param) != 0) {
    return 1;
  }

  switch (msg) {
    case WM_SIZE:
      if (window::g_pd3d_device != nullptr && w_param != SIZE_MINIMIZED) {
        CleanupRenderTarget();
        window::g_p_swap_chain->ResizeBuffers(0, (UINT) LOWORD(l_param), (UINT) HIWORD(l_param),
                                              DXGI_FORMAT_UNKNOWN, 0);
        CreateRenderTarget();
      }
      return 0;
    case WM_SYSCOMMAND:
      if ((w_param & 0xfff0) == SC_KEYMENU) { // Disable ALT application menu
        return 0;
      }
      break;
    case WM_DESTROY: ::PostQuitMessage(0);
      return 0;
  }
  return ::DefWindowProc(h_wnd, msg, w_param, l_param);
}

#endif //INVENTORYMANAGEMENTAPPLICATION_INITIALIZE_DIRECTX_WINDOW_H
