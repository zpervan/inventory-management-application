cmake_minimum_required(VERSION 3.19)

# Add libraries
set(FMT_ROOT "${CMAKE_SOURCE_DIR}/ThirdParty/FMT")
add_subdirectory(${FMT_ROOT} ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/FMT)
include_directories(${FMT_ROOT}/include)

# Custom location of the PostgreSQL library
set(PostgreSQL_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/PostgreSQL13")
set(PostgreSQL_ROOT "${PostgreSQL_DIR}")
set(PostgreSQL_LIBRARY_DIR "${PostgreSQL_DIR}/lib")
set(PostgreSQL_INCLUDE_DIRS "${PostgreSQL_DIR}/include")
set(PostgreSQL_LIBRARIES "${PostgreSQL_DIR}/lib/libpq.lib")

include_directories(${PostgreSQL_INCLUDE_DIRS})
link_directories(${PostgreSQL_LIBRARY_DIRS})

# Print the PostgreSQL locations
#message("-- PostgreSQL_ROOT: ${PostgreSQL_ROOT}")
#message("-- PostgreSQL_INCLUDE_DIR: ${PostgreSQL_INCLUDE_DIRS}")
#message("-- PostgreSQL_LIBRARY_DIR: ${PostgreSQL_LIBRARY_DIR}")
#message("-- PostgreSQL_LIBRARIES: ${PostgreSQL_LIBRARIES}")

message("-- Adding DatabaseQueryLib")

add_library(DatabaseQueryLib STATIC
        ${PROJECT_SOURCE_DIR}/Backend/DatabaseQuery/database_query.h
        ${PROJECT_SOURCE_DIR}/Backend/DatabaseQuery/database_query.cpp
        )

target_link_libraries(DatabaseQueryLib
        PRIVATE ${PostgreSQL_LIBRARIES}
        PRIVATE fmt
        )

