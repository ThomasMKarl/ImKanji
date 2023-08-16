find_package(Freetype REQUIRED)

set(src_imgui
    binary_to_compressed_c.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_freetype.cpp
    imgui_stdlib.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp)

add_library(imgui SHARED ${src_imgui})
target_include_directories(imgui PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(imgui ${FREETYPE_LIBRARIES})

add_subdirectory(backends)

install(TARGETS imgui)
