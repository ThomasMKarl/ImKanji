add_subdirectory(data)
add_subdirectory(windows)

## IMKANJI
add_executable(imkanji main.cpp)

target_include_directories(imkanji PRIVATE "data/" "data/app" "data/error" "windows" "windows/imgui" "windows/nfd")

target_link_libraries(imkanji PRIVATE imgui_kanji_data)
target_link_libraries(imkanji PRIVATE imgui_kanji_gui)
if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    target_sources(imkanji PRIVATE ../resources/icon.rc)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Linux)
else ()
    message(FATAL_ERROR "Your OS is not supported, CMake will exit.")
endif ()

target_link_libraries(imkanji PRIVATE Plog::Plog)
target_link_libraries(imkanji PRIVATE Glaze::Glaze)

target_link_libraries(imkanji PRIVATE imgui)
target_link_libraries(imkanji PRIVATE imgui_glfw)
target_link_libraries(imkanji PRIVATE imgui_opengl3)

## IMAKNJI_CMD
add_executable(imkanji_cmd main_cmd.cpp)

target_include_directories(imkanji_cmd PRIVATE "data/" "data/app" "data/error" "windows" "windows/imgui" "windows/nfd")

target_link_libraries(imkanji_cmd PRIVATE imgui_kanji_data)

target_link_libraries(imkanji_cmd PRIVATE Plog::Plog)
target_link_libraries(imkanji_cmd PRIVATE Glaze::Glaze)

target_link_libraries(imkanji_cmd PRIVATE imgui)
target_link_libraries(imkanji_cmd PRIVATE imgui_glfw)
target_link_libraries(imkanji_cmd PRIVATE imgui_opengl3)
