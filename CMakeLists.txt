cmake_minimum_required (VERSION 3.14)
project (EasyLinux)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    message(STATUS "----- GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")
    message(STATUS "----- GKT3_LIBRARIES: ${GTK3_LIBRARIES}")
    message(STATUS "----- GTK3_LINK_LIBRARIES: ${GTK3_LINK_LIBRARIES}")
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    list(APPEND FC_DEP_LIBS ${GTK3_LIBRARIES})
endif()

add_executable (main
        src/main.c
)

#add_definitions (${GTK3_CFLAGS_OTHER})
message(STATUS "----- ${GTK3_CFLAGS_OTHER}")
# -pthread

target_link_libraries (main ${FC_DEP_LIBS})