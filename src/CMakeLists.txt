add_subdirectory(imgui)
add_subdirectory(nfd)

set(src_windows
    windows/ConfigWindow.cpp
    windows/FlashcardWindow.cpp
    windows/GraphemeWindow.cpp
    windows/Imgui.cpp
    windows/LogWindow.cpp
    windows/MainMenuBar.cpp
    windows/MainWindow.cpp
    windows/TableWindow.cpp)

set(src_data
    Cardbox.cpp
    Flashcard.cpp
    HData.cpp
    Platform.cpp
    StbImage.cpp)

add_library(imkanji SHARED ${src_data} ${src_windows})
target_link_libraries(imkanji PRIVATE Glaze::Glaze)
target_link_libraries(imkanji PRIVATE Plog::Plog)
target_link_libraries(imkanji PRIVATE imgui imgui_opengl3 imgui_glfw nfd)
target_include_directories(imkanji PRIVATE "." "imgui" "windows" "nfd")
