cmake_minimum_required(VERSION 3.19)

set(GUI_ROOT ${PROJECT_SOURCE_DIR}/GUI)

add_library(GUILib STATIC
        ${GUI_ROOT}/gui_runner.h
        ${GUI_ROOT}/gui_runner.cpp
        )

add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/DearImgui ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/DearImgui)

target_link_libraries(GUILib PRIVATE DearImGuiLib)