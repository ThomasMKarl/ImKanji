cmake_minimum_required(VERSION 3.9.1)

find_package(Version REQUIRED)

project(ImKanji VERSION ${GIT_TAG})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

if (${BUILD_DEBUG})
    message("Debug build...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -g -fprofile-arcs -ftest-coverage")
    add_definitions(-DDEBUG)
    set(CONFIG debug)
elseif (${BUILD_PROFILE})
    message("Profile build...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pg")
    set(CONFIG profile)
else ()
    message("Release build...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    set(CONFIG release)
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CONFIG}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CONFIG}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CONFIG}/lib)

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
find_package(Stb REQUIRED)

add_subdirectory(src)

## TESTING
if (${BUILD_TESTING})
    add_subdirectory(test)
endif ()
