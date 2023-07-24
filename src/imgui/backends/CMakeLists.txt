add_library(imgui_opengl3 SHARED imgui_impl_opengl3.cpp)
add_library(imgui_glfw SHARED imgui_impl_glfw.cpp)

target_include_directories(imgui_opengl3 PRIVATE "..")
target_include_directories(imgui_glfw PRIVATE "..")

target_link_libraries(imgui_opengl3 imgui opengl32)
target_link_libraries(imgui_glfw imgui glfw3)
