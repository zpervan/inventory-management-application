cmake_minimum_required(VERSION 3.19)
project(InventoryManagementApplication)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Backend)

add_executable(InventoryManagement main.cpp)

target_link_libraries(InventoryManagement
        PRIVATE DatabaseQueryLib
        )