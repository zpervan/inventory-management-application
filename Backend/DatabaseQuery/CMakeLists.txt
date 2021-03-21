cmake_minimum_required(VERSION 3.19)

find_package(PostgreSQL REQUIRED)

message("-- PostgreSQL include paths: " ${PostgreSQL_INCLUDE_DIRS})
message("-- PostgreSQL lib path: " ${PostgreSQL_LIBRARY_DIR})
message("-- PostgreSQL libraries: " ${PostgreSQL_LIBRARIES})

include_directories(${PostgreSQL_INCLUDE_DIRS})
link_directories(${PostgreSQL_LIBRARY_DIR})

message("-- Adding DatabaseQueryLib")

add_library(DatabaseQueryLib STATIC
        ${PROJECT_SOURCE_DIR}/DatabaseQuery/database_query.h
        ${PROJECT_SOURCE_DIR}/DatabaseQuery/database_query.cpp
        )

target_link_libraries(DatabaseQueryLib
        PUBLIC ${PostgreSQL_LIBRARIES}
        )

