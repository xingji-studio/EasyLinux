cmake_minimum_required(VERSION 3.31)
<<<<<<< HEAD
project(untitled)
=======
project(EasyLinux)
>>>>>>> dev-cat

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

<<<<<<< HEAD
add_executable(untitled main.cpp)
target_link_libraries(untitled
=======
add_executable(EasyLinux main.cpp)
target_link_libraries(EasyLinux
>>>>>>> dev-cat
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

