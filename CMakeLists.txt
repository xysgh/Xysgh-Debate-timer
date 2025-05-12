cmake_minimum_required(VERSION 3.16)
project(DebateTimer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

qt_add_executable(DebateTimer
    main.cpp
    mainwindow.cpp
    mainwindow.h
    resources.qrc

)

target_link_libraries(DebateTimer
PRIVATE
    Qt6::Widgets
    Qt6::Multimedia
)
