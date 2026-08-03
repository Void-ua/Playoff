cmake_minimum_required(VERSION 3.16)

project(db LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Sql)

add_library(db STATIC

    databaseservice.h
    databaseservice.cpp
    databaseworker.h databaseworker.cpp


)

qt_add_resources(db db_migrations
    PRFIx "/"
    FILES

    sql/001_init.sql
    sql/002_create.sql
    sql/003_club.sql
    sql/004_club_changes.sql

)

target_include_directories(db PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(db PRIVATE
    Qt6::Core
    Qt6::Sql
)


