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
    StbImage.cpp
    Unicode.cpp)

set(src_error
    error/Console.cpp
    error/Exceptions.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    set(src_app
        app/AppLauncherWin.cpp)
else ()
    set(src_app
        app/AppLauncherLin.cpp)
endif ()

add_library(imgui_kanji SHARED ${src_data} ${src_windows} ${src_error} ${src_app})
target_link_libraries(imgui_kanji PRIVATE Glaze::Glaze)
target_link_libraries(imgui_kanji PRIVATE Plog::Plog)
target_link_libraries(imgui_kanji PRIVATE Stb::Stb)
target_link_libraries(imgui_kanji PRIVATE imgui imgui_opengl3 imgui_glfw nfd)
target_include_directories(imgui_kanji PRIVATE "." "imgui" "windows" "nfd" "error" "app")
