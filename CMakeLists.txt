cmake_minimum_required(VERSION 3.9.1)
project(ImKanji)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

if (${BUILD_DEBUG})
    message("Debug build...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -g -fprofile-arcs -ftest-coverage")
    add_definitions(-DDEBUG)
elseif (${BUILD_PROFILE})
    message("Profile build...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pg")
else ()
    message("Release build...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

message("Environment:")
message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message("CMAKE_HOME_DIRECTORY: ${CMAKE_HOME_DIRECTORY}")
message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message("CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH}")

message("System:")
message("CMAKE_SYSTEM: ${CMAKE_SYSTEM}")
message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message("CMAKE_SYSTEM_VERSION: ${CMAKE_SYSTEM_VERSION}")
message("CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}")

find_package(Plog REQUIRED)
find_package(Glaze REQUIRED)

add_subdirectory(src)

add_executable(main main.cpp)

target_include_directories(main PRIVATE "src" "src/windows" "src/imgui" "src/nfd")

target_link_libraries(main PRIVATE imkanji)

target_link_libraries(main PRIVATE Plog::Plog)
target_link_libraries(main PRIVATE Glaze::Glaze)

target_link_libraries(main PRIVATE imgui)
target_link_libraries(main PRIVATE imgui_glfw)
target_link_libraries(main PRIVATE imgui_opengl3)
