add_subdirectory(data)
add_subdirectory(windows)

set(EXE_NAME imkanji)

file(COPY ${CMAKE_SOURCE_DIR}/resources/kanji.ico DESTINATION ${CMAKE_BINARY_DIR})

## IMKANJI
add_executable(${EXE_NAME} main.cpp)

target_include_directories(${EXE_NAME} PRIVATE "data" "data/app" "data/error" "windows" "windows/imgui" "windows/nfd")

target_link_libraries(${EXE_NAME} PRIVATE imgui_kanji_data)
target_link_libraries(${EXE_NAME} PRIVATE imgui_kanji_gui)
if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
  target_compile_definitions(${EXE_NAME} PRIVATE PLOG_EXPORT)
  set_target_properties(${EXE_NAME} PROPERTIES ENABLE_EXPORTS 1)
  target_sources(${EXE_NAME} PRIVATE ${CMAKE_BINARY_DIR}/winres.rc)
  set(EXTENSION .exe)
else ()
  target_compile_definitions(${EXE_NAME} PRIVATE PLOG_GLOBAL)
endif ()

target_link_libraries(${EXE_NAME} PRIVATE Plog::Plog)
target_link_libraries(${EXE_NAME} PRIVATE Glaze::Glaze)

target_link_libraries(${EXE_NAME} PRIVATE imgui)
target_link_libraries(${EXE_NAME} PRIVATE imgui_glfw)
target_link_libraries(${EXE_NAME} PRIVATE imgui_opengl3)

## IMAKNJI_CMD
add_executable(${EXE_NAME}_cmd main_cmd.cpp)
target_link_libraries(${EXE_NAME}_cmd PRIVATE -static gcc stdc++ winpthread -dynamic)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
  target_compile_definitions(${EXE_NAME}_cmd PRIVATE PLOG_EXPORT)
  set_target_properties(${EXE_NAME}_cmd PROPERTIES ENABLE_EXPORTS 1)
else ()
  target_compile_definitions(${EXE_NAME}_cmd PRIVATE PLOG_GLOBAL)
endif ()

target_include_directories(${EXE_NAME}_cmd PRIVATE "data/" "data/app" "data/error" "windows" "windows/imgui" "windows/nfd")

target_link_libraries(${EXE_NAME}_cmd PRIVATE imgui_kanji_data)

target_link_libraries(${EXE_NAME}_cmd PRIVATE Plog::Plog)
target_link_libraries(${EXE_NAME}_cmd PRIVATE Glaze::Glaze)

target_link_libraries(${EXE_NAME}_cmd PRIVATE imgui)
target_link_libraries(${EXE_NAME}_cmd PRIVATE imgui_glfw)
target_link_libraries(${EXE_NAME}_cmd PRIVATE imgui_opengl3)

set(RESOURCE_FILE "
id ICON \"kanji.ico\"
1 VERSIONINFO
FILEVERSION     1,0,0,0
PRODUCTVERSION  1,0,0,0
BEGIN
  BLOCK \"StringFileInfo\"
  BEGIN
    BLOCK \"040904E4\"
    BEGIN
      VALUE \"CompanyName\", \"Open Boundaries\"
      VALUE \"FileDescription\", \"Kanji Training in ImGui\"
      VALUE \"FileVersion\", \"${GIT_REV}\"
      VALUE \"InternalName\", \"${CMAKE_PROJECT_NAME}\"
      VALUE \"LegalCopyright\", \"\"
      VALUE \"OriginalFilename\", \"${EXE_NAME}${EXTENSION}\"
      VALUE \"ProductName\", \"${CMAKE_PROJECT_NAME}\"
      VALUE \"ProductVersion\", \"${GIT_TAG}\"
    END
  END
  BLOCK \"VarFileInfo\"
  BEGIN
    VALUE \"Translation\", 0x409, 1252
  END
END")

if(EXISTS ${CMAKE_BINARY_DIR}/winres.rc)
    file(READ ${CMAKE_BINARY_DIR}/winres.rc RESOURCE_FILE_)
else()
    set(RESOURCE_FILE_ "")
endif()

if (NOT "${RESOURCE_FILE}" STREQUAL "${RESOURCE_FILE_}")
    file(WRITE ${CMAKE_BINARY_DIR}/winres.rc "${RESOURCE_FILE}")
endif()

install(TARGETS ${EXE_NAME})
install(TARGETS ${EXE_NAME}_cmd)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
