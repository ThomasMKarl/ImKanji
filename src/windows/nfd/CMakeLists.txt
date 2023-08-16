set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    set(src_nfd
        FileDialog.cpp
        nfd_win.cpp)
else ()
    find_package(Pango REQUIRED)
    pkg_check_modules(GTK REQUIRED gtk+-3.0)
    set(src_nfd
        FileDialog.cpp
        nfd_gtk.cpp)
endif ()

add_library(nfd STATIC ${src_nfd})
include_directories(${GLIB_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS} ${PANGO_INCLUDE_DIRS})
target_link_libraries(nfd PRIVATE ${GTK_LIBRARIES} ${PANGO_LIBRARIES})
target_link_directories(nfd PRIVATE ${GTK_LIBRARY_DIRS} ${PANGO_LIBRARY_DIRS})
