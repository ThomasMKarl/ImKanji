find_path(
  Plog_INCLUDE_DIR
  NAMES
    Init.h
    Log.h
    Logger.h
    Record.h
    Severity.h
    Util.h
    WinApi.h
  HINTS "${Plog_ROOT_DIR}"
  PATH_SUFFIXES include plog
)

# If we find the library, add it as a target
if (Plog_INCLUDE_DIR)
  set(Plog_FOUND TRUE)
  
  # Print a message that we found it
  if (NOT Plog_FIND_QUIETLY)
    message(STATUS "Found Plog")
  endif (NOT Plog_FIND_QUIETLY)

  # Create a target for it, if there isn't one already created
  if (NOT TARGET Plog::Plog)
    add_library(Plog::Plog INTERFACE IMPORTED)
    cmake_path(GET Plog_INCLUDE_DIR FILENAME subfolder)
    if (subfolder STREQUAL "plog")
      cmake_path(GET Plog_INCLUDE_DIR PARENT_PATH Plog_INCLUDE_DIR)
      set_target_properties(Plog::Plog PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Plog_INCLUDE_DIR}")
      message(STATUS "Plog include dir: ${Plog_INCLUDE_DIR}")
    else()
      message(STATUS "found Log.h but subfolder is not \"plog\"")
      set(Plog_INCLUDE_DIR "")
      set(Plog_FOUND FALSE)
    endif()
  endif (NOT TARGET Plog::Plog)
else ()
  # If we don't find the library, fail as appropriate
  if (Plog_FIND_REQUIRED)  
    message(FATAL_ERROR "Plog was NOT found")
  elseif (NOT Plog_FIND_QUIETLY)
    message(STATUS "Plog was NOT found")
  endif (Plog_FIND_REQUIRED)
endif (Plog_INCLUDE_DIR)

# Hide the variables that we set
mark_as_advanced(Plog_INCLUDE_DIR)
