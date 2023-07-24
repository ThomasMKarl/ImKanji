find_path(
  Glaze_INCLUDE_DIR
  NAMES
    glaze.hpp
  HINTS "${Glaze_ROOT_DIR}"
  PATH_SUFFIXES include glaze
)

# If we find the library, add it as a target
if (Glaze_INCLUDE_DIR)
  set(Glaze_FOUND TRUE)
  
  # Print a message that we found it
  if (NOT Glaze_FIND_QUIETLY)
    message(STATUS "Found Glaze")
  endif (NOT Glaze_FIND_QUIETLY)

  # Create a target for it, if there isn't one already created
  if (NOT TARGET Glaze::Glaze)
    add_library(Glaze::Glaze INTERFACE IMPORTED)
    cmake_path(GET Glaze_INCLUDE_DIR FILENAME subfolder)
    if (subfolder STREQUAL "glaze")
      cmake_path(GET Glaze_INCLUDE_DIR PARENT_PATH Glaze_INCLUDE_DIR)
      set_target_properties(Glaze::Glaze PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Glaze_INCLUDE_DIR}")
      message(STATUS "Glaze include dir: ${Glaze_INCLUDE_DIR}")
    else()
      message(STATUS "found glaze.hpp but subfolder is not \"glaze\"")
      set(Glaze_INCLUDE_DIR "")
      set(Glaze_FOUND FALSE)
    endif()
  endif (NOT TARGET Glaze::Glaze)
else ()
  # If we don't find the library, fail as appropriate
  if (Glaze_FIND_REQUIRED)  
    message(FATAL_ERROR "Glaze was NOT found")
  elseif (NOT Glaze_FIND_QUIETLY)
    message(STATUS "Glaze was NOT found")
  endif (Glaze_FIND_REQUIRED)
endif (Glaze_INCLUDE_DIR)

# Hide the variables that we set
mark_as_advanced(Glaze_INCLUDE_DIR)
