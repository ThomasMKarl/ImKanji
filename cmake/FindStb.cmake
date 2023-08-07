find_path(
  Stb_INCLUDE_DIR
  NAMES
    stb_image.h
  HINTS "${Stb_ROOT_DIR}"
  PATH_SUFFIXES include stb
)

# If we find the library, add it as a target
if (Stb_INCLUDE_DIR)
  set(Stb_FOUND TRUE)
  
  # Print a message that we found it
  if (NOT Stb_FIND_QUIETLY)
    message(STATUS "Found Stb")
  endif (NOT Stb_FIND_QUIETLY)

  # Create a target for it, if there isn't one already created
  if (NOT TARGET Stb::Stb)
    add_library(Stb::Stb INTERFACE IMPORTED)
    cmake_path(GET Stb_INCLUDE_DIR FILENAME subfolder)
    if (subfolder STREQUAL "stb")
      cmake_path(GET Stb_INCLUDE_DIR PARENT_PATH Stb_INCLUDE_DIR)
      set_target_properties(Stb::Stb PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Stb_INCLUDE_DIR}")
      message(STATUS "Stb include dir: ${Stb_INCLUDE_DIR}")
    else()
      message(STATUS "found stb.h but subfolder is not \"stb\"")
      set(Stb_INCLUDE_DIR "")
      set(Stb_FOUND FALSE)
    endif()
  endif (NOT TARGET Stb::Stb)
else ()
  # If we don't find the library, fail as appropriate
  if (Stb_FIND_REQUIRED)  
    message(FATAL_ERROR "Stb was NOT found")
  elseif (NOT Stb_FIND_QUIETLY)
    message(STATUS "Stb was NOT found")
  endif (Stb_FIND_REQUIRED)
endif (Stb_INCLUDE_DIR)

# Hide the variables that we set
mark_as_advanced(Stb_INCLUDE_DIR)
