cmake_minimum_required(VERSION 3.19)
project(GUILib)

add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/Imgui ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/Imgui)
add_subdirectory(${CMAKE_SOURCE_DIR}/Backend/DatabaseQuery ${CMAKE_CURRENT_BINARY_DIR}/Backend/DatabaseQuery)

set(GUI_ROOT ${CMAKE_SOURCE_DIR}/GUI)
file(GLOB Src ${GUI_ROOT}/*.h ${GUI_ROOT}/*.cpp)

add_library(${PROJECT_NAME} STATIC ${Src})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            DatabaseQueryLib
            ImguiLib
        )

install(TARGETS GUILib)