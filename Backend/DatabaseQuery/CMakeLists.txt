cmake_minimum_required(VERSION 3.19)

# Custom location of the PostgreSQL library
set(PostgreSQL_DIR "${CMAKE_SOURCE_DIR}/Backend/ThirdParty/PostgreSQL13")
set(PostgreSQL_ROOT "${PostgreSQL_DIR}")
set(PostgreSQL_LIBRARY_DIR "${PostgreSQL_DIR}/lib")
set(PostgreSQL_INCLUDE_DIRS "${PostgreSQL_DIR}/include")
set(PostgreSQL_LIBRARIES "${PostgreSQL_DIR}/lib/libpq.lib")

# Include the found INCLUDE directory
include_directories(${PostgreSQL_INCLUDE_DIRS})

# Include the found LIBRARY directory
link_directories(${PostgreSQL_LIBRARY_DIRS})

# Print the PostgreSQL locations
#message("-- PostgreSQL_ROOT: ${PostgreSQL_ROOT}")
#message("-- PostgreSQL_INCLUDE_DIR: ${PostgreSQL_INCLUDE_DIRS}")
#message("-- PostgreSQL_LIBRARY_DIR: ${PostgreSQL_LIBRARY_DIR}")
#message("-- PostgreSQL_LIBRARIES: ${PostgreSQL_LIBRARIES}")

message("-- Adding DatabaseQueryLib")

add_library(DatabaseQueryLib STATIC
        ${PROJECT_SOURCE_DIR}/DatabaseQuery/database_query.h
        ${PROJECT_SOURCE_DIR}/DatabaseQuery/database_query.cpp
        )

target_link_libraries(DatabaseQueryLib
        PUBLIC ${PostgreSQL_LIBRARIES}
        )

