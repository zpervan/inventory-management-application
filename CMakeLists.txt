cmake_minimum_required(VERSION 3.20)
project(InventoryManagement)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/bin")

message("-- Code generator: ${CMAKE_GENERATOR}")

add_subdirectory(GUI)

# Inventory management main executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} GUILib)

add_executable(ImguiDx11 ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Imgui/imgui_win32_dx11_example.cpp)
target_link_libraries(ImguiDx11 ImguiLib)

install(TARGETS ${PROJECT_NAME})

file(GLOB_RECURSE LIBS "*.dll" "*.lib")

# TODO: Filter out unnecessary libraries
foreach(LIB ${LIBS})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            -E copy ${LIB} ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

