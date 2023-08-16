set(src_data
    Cardbox.cpp
    CmdConfig.cpp
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

add_library(imgui_kanji_data SHARED ${src_data} ${src_error} ${src_app})

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
  target_compile_definitions(imgui_kanji_data PRIVATE PLOG_IMPORT)
else ()
  target_compile_definitions(imgui_kanji_data PRIVATE PLOG_GLOBAL)
endif ()

target_link_libraries(imgui_kanji_data PRIVATE Glaze::Glaze)
target_link_libraries(imgui_kanji_data PRIVATE Plog::Plog)
target_link_libraries(imgui_kanji_data PRIVATE Stb::Stb)
target_link_libraries(imgui_kanji_data PRIVATE imgui_opengl3)
target_include_directories(imgui_kanji_data PRIVATE "." "error" "app")

install(TARGETS imgui_kanji_data)
