cmake_minimum_required(VERSION 3.16)

project(models LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(models STATIC
  
  m_menu.h m_menu.cpp
  tournament_list.h tournament_list.cpp
  tournament_form.h tournament_form.cpp
  tournament_control.h tournament_control.cpp
)

target_include_directories(models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(models PRIVATE Qt6::Core)
