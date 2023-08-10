add_subdirectory(imgui)
add_subdirectory(nfd)

set(src_windows
    ConfigWindow.cpp
    FlashcardWindow.cpp
    GraphemeWindow.cpp
    Imgui.cpp
    LogWindow.cpp
    MainMenuBar.cpp
    MainWindow.cpp
    TableWindow.cpp)

add_library(imgui_kanji_gui SHARED ${src_windows})
target_link_libraries(imgui_kanji_gui PRIVATE Glaze::Glaze)
target_link_libraries(imgui_kanji_gui PRIVATE Plog::Plog)
#target_link_libraries(imgui_kanji_gui PRIVATE Stb::Stb)
target_link_libraries(imgui_kanji_gui PRIVATE imgui imgui_opengl3 imgui_glfw nfd imgui_kanji_data)
target_include_directories(imgui_kanji_gui PRIVATE "." "imgui" "nfd" "../data" "../data/error")
