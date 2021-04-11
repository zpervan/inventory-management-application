#include <iostream>
#include "gui_runner.h"
#include "directx_window.h"
#include "imgui_content_window.h"


void Runner::Run() {
    CreateDirectXWindow(application_title);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(window::g_direct_x_window);
    ImGui_ImplDX10_Init(window::g_pd3d_device);
    // Main loop
    bool done = false;

    while (!done) {

        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }

        if (done) break;

        // Start the Dear ImGui frame
        ImGui_ImplDX10_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");

            ImGui::Text("This is some useful text.");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float *) &properties::clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = {properties::clear_color.x * properties::clear_color.w,
                                                 properties::clear_color.y * properties::clear_color.w,
                                                 properties::clear_color.z * properties::clear_color.w,
                                                 properties::clear_color.w};
        window::g_pd3d_device->OMSetRenderTargets(1, &window::g_main_render_target_view, nullptr);
        window::g_pd3d_device->ClearRenderTargetView(window::g_main_render_target_view, clear_color_with_alpha);
        ImGui_ImplDX10_RenderDrawData(ImGui::GetDrawData());

        window::g_p_swap_chain->Present(1, 0); // Present with vsync
    }
}
