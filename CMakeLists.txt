cmake_minimum_required(VERSION 3.17)

project(InventoryManagementApplication LANGUAGES CXX)

add_subdirectory(Backend)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.0.2\\mingw81_64\\lib\\cmake")

find_package(QT NAMES Qt6 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(TS_FILES InventoryManagementApplication_hr_HR.ts)

set(PROJECT_SOURCES
        main.cpp
        GUI/src/mainwindow.cpp
        GUI/src/mainwindow.h
        GUI/src/mainwindow.ui
        ${TS_FILES}
        )

qt_add_executable(InventoryManagementApplication
        ${PROJECT_SOURCES}
        )

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(InventoryManagementApplication PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        DatabaseQueryLib
        )
