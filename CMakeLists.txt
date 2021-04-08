cmake_minimum_required(VERSION 3.19)
project(InventoryManagementApplication)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Backend)
add_subdirectory(ThirdParty/DearImgui)
add_subdirectory(ThirdParty/GoogleTest)

add_executable(InventoryManagementExe main.cpp)

target_link_libraries(InventoryManagementExe
        PRIVATE DatabaseQueryLib
        )