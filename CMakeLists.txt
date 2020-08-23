cmake_minimum_required(VERSION 3.5)

project(Screencaster LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SRC ${CMAKE_SOURCE_DIR}/src)

include_directories(
    ${SRC}/screencaster
    ${SRC}/ui
)

add_executable(${PROJECT_NAME}
    ${SRC}/screencaster/Screencaster.cpp
    ${SRC}/screencaster/Screencaster.h
    ${SRC}/screencaster/Settings.h
    ${SRC}/ui/main.qrc
    ${SRC}/ui/MainWindow.cpp
    ${SRC}/ui/MainWindow.h
    ${SRC}/ui/MainWindow.ui
    ${SRC}/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
