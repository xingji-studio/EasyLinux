cmake_minimum_required(VERSION 3.31)
project(EasyLinux)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(include)

add_executable(EasyLinux
        src/main.cpp
        resources.qrc
        src/SplashScreen.cpp
        include/SplashScreen.h
        src/MainWindow.cpp
        include/MainWindow.h)
target_link_libraries(EasyLinux
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

