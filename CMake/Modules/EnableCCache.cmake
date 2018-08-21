#.rst:
# EnableCCache
# ---------
#
# Enables ccache support in CMake
#
# This module defines the following functions:
#
# ::
#
#     enable_ccache()
#
# Enables ccache in the current project, if it's discovered
#
include(CMakeParseArguments)

macro(enable_ccache)

  set(__FIND_ROOT_PATH_MODE_PROGRAM ${CMAKE_FIND_ROOT_PATH_MODE_PROGRAM})
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

  find_program(CCACHE_PATH ccache)

  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ${__FIND_ROOT_PATH_MODE_PROGRAM})
  set(__FIND_ROOT_PATH_MODE_PROGRAM)

  if(CCACHE_PATH)
    if(  "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
      set(__ccache_cxx_flags -Qunused-arguments -fcolor-diagnostics)
    endif()
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PATH} ${__ccache_cxx_flags})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PATH})
  endif()

  mark_as_advanced(CCACHE_PATH)

endmacro()
