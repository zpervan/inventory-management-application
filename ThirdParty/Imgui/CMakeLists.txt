cmake_minimum_required(VERSION 3.19)
project(ImguiLib)

# @TODO: Check if shared libraries can be used instead of static
# Add FreeType paths
set(FreeType_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/misc/thirdparty/FreeType/include)
set(FreeType_LIB_X64 ${CMAKE_CURRENT_SOURCE_DIR}/misc/thirdparty/FreeType/lib/win64/freetype.lib)
include_directories(${FreeType_INCLUDE_DIR})

# Add all imgui header and source files
file(GLOB_RECURSE Imgui_SRC "*.h" "*.cpp")

# Exclude the executable file
list(REMOVE_ITEM Imgui_SRC "${CMAKE_CURRENT_SOURCE_DIR}/imgui_exe.cpp")

add_library(${PROJECT_NAME} ${Imgui_SRC})

if(CMAKE_GENERATOR MATCHES "NMake Makefiles")
    # Add DirectX11 paths
    set(DirectX11_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/misc/thirdparty/DirectX11/include)
    set(DirectX11_LIBS_X64_PATH ${CMAKE_CURRENT_SOURCE_DIR}/misc/thirdparty/DirectX11/lib/x64)
    file(GLOB DirectX11_LIBS_X64 "${DirectX11_LIBS_X64_PATH}/*.lib")
    include_directories(${DirectX11_LIBS_X64})

    target_link_libraries(${PROJECT_NAME}
            PRIVATE
                ${FreeType_LIB_X64}
                ${DirectX11_LIBS_X64}
            )
else()
    set(WINDOWS_DEPENDENCIES
            imm32
            dwmapi
            d3d11
            d3dx11
            d3dcompiler
            )
    target_link_libraries(${PROJECT_NAME} PRIVATE ${WINDOWS_DEPENDENCIES} ${FreeType_LIB_X64})
endif()

install(TARGETS ImguiLib)
