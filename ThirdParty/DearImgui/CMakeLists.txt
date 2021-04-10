project(DearImGuiLib)

message("-- Adding DearImgui")

# Specify source files
set(SOURCE
        ${PROJECT_SOURCE_DIR}/imconfig.h
        ${PROJECT_SOURCE_DIR}/imgui.h
        ${PROJECT_SOURCE_DIR}/imgui_internal.h
        ${PROJECT_SOURCE_DIR}/imstb_rectpack.h
        ${PROJECT_SOURCE_DIR}/imstb_textedit.h
        ${PROJECT_SOURCE_DIR}/imstb_truetype.h
        ${PROJECT_SOURCE_DIR}/imgui_impl_dx10.h
        ${PROJECT_SOURCE_DIR}/imgui_impl_win32.h
        ${PROJECT_SOURCE_DIR}/implot.h
        ${PROJECT_SOURCE_DIR}/implot_internal.h
        ${PROJECT_SOURCE_DIR}/imgui.cpp
        ${PROJECT_SOURCE_DIR}/imgui_demo.cpp
        ${PROJECT_SOURCE_DIR}/imgui_draw.cpp
        ${PROJECT_SOURCE_DIR}/imgui_tables.cpp
        ${PROJECT_SOURCE_DIR}/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/imgui_impl_dx10.cpp
        ${PROJECT_SOURCE_DIR}/imgui_impl_win32.cpp
        ${PROJECT_SOURCE_DIR}/imgui_exe.cpp
        ${PROJECT_SOURCE_DIR}/implot.cpp
        ${PROJECT_SOURCE_DIR}/implot_demo.cpp
        ${PROJECT_SOURCE_DIR}/implot_items.cpp
        )

# Set the dependencies fow Windows 10 DirectX dependencies
set(WINDOWS_DEPENDENCIES
        imm32
        dwmapi
        d3d10
        d3dx10
        d3dcompiler
        )

add_library(${PROJECT_NAME} STATIC ${SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE "${HEADERS}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${WINDOWS_DEPENDENCIES})