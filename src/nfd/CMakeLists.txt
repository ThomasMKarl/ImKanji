
if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    set(src_nfd
        FileDialog.cpp
        nfd_win.cpp)
elseif ()
    set(src_nfd
        FileDialog.cpp
        nfd_gtk.cpp)
endif ()

add_library(nfd STATIC ${src_nfd})
