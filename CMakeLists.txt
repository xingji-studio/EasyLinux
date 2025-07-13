cmake_minimum_required(VERSION 3.31)
project(EasyLinux C)

set(CMAKE_C_STANDARD 23)
add_compile_options(-Wall -I/usr/include/gtk-4.0
        -I/usr/include/pango-1.0 -I/usr/include/fribidi
        -I/usr/include/harfbuzz -I/usr/include/gdk-pixbuf-2.0
        -I/usr/include/cairo -I/usr/include/freetype2
        -I/usr/include/libpng16 -I/usr/include/pixman-1
        -I/usr/include/graphene-1.0 -I/usr/lib/graphene-1.0/include
        -mfpmath=sse -msse -msse2 -I/usr/include/glib-2.0
        -I/usr/lib/glib-2.0/include -I/usr/include/libmount
        -I/usr/include/blkid -I/usr/include/sysprof-6 -pthread
        -lgtk-4 -lpangocairo-1.0 -lpango-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lharfbuzz -lvulkan -lgraphene-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0
)
add_executable(EasyLinux main.c)

