cmake_minimum_required(VERSION 3.19)
project(InventoryManagementApplication)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(GUI)

# Main executable
add_executable(InventoryManagementExe main.cpp)
target_link_libraries(InventoryManagementExe
        PRIVATE GUILib
        )

# For testing purposes - run DearImgui with DX10 example
add_executable(DearImguiExe ThirdParty/DearImgui/imgui_exe.cpp)
target_link_libraries(DearImguiExe DearImGuiLib )