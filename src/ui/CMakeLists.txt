cmake_minimum_required(VERSION 3.16)

project(ui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_source_files_properties(
    style/Style.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(ui
    URI UiPlayoff
    VERSION 1.0
    QML_FILES

    Main.qml
    App.qml
    controls/MenuButton.qml
    WelcomePage.qml
    Club.qml
    Tour.qml
    TourList.qml
    TourForm.qml
    controls/DatePicker.qml
    controls/FloatInput.qml
    controls/LabelHeaderTable.qml
    controls/Message.qml
    controls/FormButtons.qml

    style/Style.qml
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ui PRIVATE Qt6::Quick)
set(QML_IMPORT_PATH "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "" FORCE)
