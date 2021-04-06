project(DearImGui CXX)

message("-- Adding DearImgui")

# Specify header files
set(HEADERS
        imconfig.h
        imgui.h
        imgui_internal.h
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
        imgui_impl_dx10.h
        imgui_impl_win32.h
        implot.h
        implot_internal.h
        )

# Specify source files
set(SOURCES
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        imgui_impl_dx10.cpp
        imgui_impl_win32.cpp
        imgui_exe.cpp
        implot.cpp
        implot_demo.cpp
        implot_items.cpp
        )

# Create a library
add_library(DearImGui STATIC ${HEADERS} ${SOURCES})

# For testing purposes - run DearImgui with DX10 example
add_executable(DearImguiExe imgui_exe.cpp)

# Set the DirectX dependencies to run the example code
set(WINDOWS_DEPENDENCIES
        imm32
        dwmapi
        d3d10
        d3dx10
        d3dcompiler
        )

# Link the executable, DearImgui library and DirectX10 dependencies
target_link_libraries(DearImguiExe DearImGui ${WINDOWS_DEPENDENCIES})
