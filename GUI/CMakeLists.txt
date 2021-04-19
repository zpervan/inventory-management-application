cmake_minimum_required(VERSION 3.19)

set(GUI_ROOT ${PROJECT_SOURCE_DIR}/GUI)

add_library(GUILib STATIC
        ${GUI_ROOT}/gui_runner.h
        ${GUI_ROOT}/gui_runner.cpp
        ${GUI_ROOT}/directx_window.h
        ${GUI_ROOT}/application_settings.h
        ${GUI_ROOT}/top_menu_bar.h
        ${GUI_ROOT}/main_menu_bar.h
        ${GUI_ROOT}/main_window.h
        ${GUI_ROOT}/utility.h
        )

add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/DearImgui ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/DearImgui)

target_link_libraries(GUILib PUBLIC DearImGuiLib)