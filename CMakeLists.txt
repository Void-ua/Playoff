cmake_minimum_required(VERSION 3.16)

project(Playoff VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Sql)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appPlayoff
    src/main.cpp
)

qt_add_resources(appPlayoff "configuration"
    PREFIX "/"
    FILES
    qtquickcontrols2.conf
)

add_subdirectory(src/utils)
add_subdirectory(src/ui)
add_subdirectory(src/db)


target_link_libraries(appPlayoff PRIVATE
    utils
    ui
    db
    Qt6::Quick
    Qt6::Core
    Qt6::Sql
)

include(GNUInstallDirs)

install(TARGETS appPlayoff
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
