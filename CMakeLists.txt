cmake_minimum_required(VERSION 3.1)

enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

#-----------------------------------------------------------------------------
# Project Setup
#-----------------------------------------------------------------------------

# default to debug when building CMake
if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES )
set(CMAKE_BUILD_TYPE DEBUG)
endif()

include(EnableCCache)

# enable cacche to speed up compilations
enable_ccache()

include(CMakeDependentOption)

option(BIT_MATH_COMPILE_HEADER_SELF_CONTAINMENT_TESTS "Include each header independently in a .cpp file to determine header self-containment" off)
option(BIT_MATH_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" off)
option(BIT_MATH_GENERATE_DOCUMENTATION "Generates doxygen documentation" off)

option(BIT_MATH_DOUBLE_PRECISION "Use double precision for mathematics." off)
option(BIT_MATH_CACHED_TRIG "Build a cached table for triginometrec function results." off)
option(BIT_MATH_INCLUDE_HALF "Includes bit::math::half for IEEE half-precision floating points" on)

set(BIT_MATH_TRIG_TABLE_SIZE 1024 CACHE STRING "The size of the trig table to build. This is ignored unless BIT_MATH_CACHED_TRIG is on")
set(BIT_MATH_INVERSE_TRIG_TABLE_SIZE 4096 CACHE STRING "The size of the inverse trig table to build. This is ignored unless BIT_MATH_CACHED_TRIG is on")

project("BitMath" LANGUAGES CXX)

#-----------------------------------------------------------------------------
# Option Validation
#-----------------------------------------------------------------------------

if( BIT_MATH_CACHED_TRIG AND NOT BIT_MATH_TRIG_TABLE_SIZE MATCHES "[1-9][0-9]+" )
  message(FATAL_ERROR "'BIT_MATH_TRIG_TABLE_SIZE' contains an invalid value. This must be a numeric entry")
endif()

#-----------------------------------------------------------------------------

if( BIT_MATH_CACHED_TRIG AND NOT BIT_MATH_INVERSE_TRIG_TABLE_SIZE MATCHES "[1-9][0-9]+" )
  message(FATAL_ERROR "'BIT_MATH_INVERSE_TRIG_TABLE_SIZE' contains an invalid value. This must be a numeric entry")
endif()

#-----------------------------------------------------------------------------
# Version Info
#-----------------------------------------------------------------------------

set(BIT_MATH_VERSION_MAJOR 0 CACHE STRING "major version of bit::math" FORCE)
set(BIT_MATH_VERSION_MINOR 1 CACHE STRING "minor version of bit::math" FORCE)
set(BIT_MATH_VERSION_PATCH 62 CACHE STRING "patch version of bit::math" FORCE)

set(BIT_MATH_VERSION "${BIT_MATH_VERSION_MAJOR}.${BIT_MATH_VERSION_MINOR}.${BIT_MATH_VERSION_PATCH}" CACHE STRING "version of bit::math" FORCE)

if( BIT_STL_VERBOSE_CONFIGURE )
  message(STATUS "bit::math ${BIT_MATH_VERSION}")
endif()

#-----------------------------------------------------------------------------
# bit::math
#-----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

#-----------------------------------------------------------------------------
# bit::math : Sources
#-----------------------------------------------------------------------------

# Note: This generates into the current 'include' directory so that
#       other local headers can use it from relative path includes, rather
#       than requiring a specific include path to the library for this to work
set(__template_file "${CMAKE_CURRENT_LIST_DIR}/version.hpp.in")
set(__output_file "${CMAKE_CURRENT_LIST_DIR}/include/bit/math/version.hpp")

configure_file("${__template_file}" "${__output_file}")

set(headers
      "include/bit/math/angles.hpp"
      "include/bit/math/vector.hpp"
      "include/bit/math/matrix.hpp"
      "include/bit/math/quaternion.hpp"
      "include/bit/math/clamped.hpp"
      "include/bit/math/euler.hpp"
      "include/bit/math/interpolation.hpp"
      "include/bit/math/transform.hpp"
      "include/bit/math/simplex.hpp"
#      "include/bit/math/point.hpp"
)

set(sources
      "src/bit/math/angles.cpp"
      "src/bit/math/vector.cpp"
      "src/bit/math/matrix.cpp"
      "src/bit/math/quaternion.cpp"
      "src/bit/math/euler.cpp"
      "src/bit/math/simplex.cpp"
)

if( BIT_MATH_INCLUDE_HALF )
  list(APPEND headers "include/bit/math/half.hpp")
  list(APPEND sources "src/bit/math/half.cpp")
endif()

#-----------------------------------------------------------------------------
# Generate trig-table
#-----------------------------------------------------------------------------

if( BIT_MATH_CACHED_TRIG )

  #---------------------------------------------------------------------------
  # Configuration for files
  #---------------------------------------------------------------------------

  if(BIT_MATH_DOUBLE_PRECISION)
    set(FLOAT_TYPE "double")
  else()
    set(FLOAT_TYPE "float")
  endif()

  set(sin_table_generator_file "${CMAKE_CURRENT_BINARY_DIR}/angles/generator.sin_table.cpp")
  set(sin_table_file "${CMAKE_CURRENT_BINARY_DIR}/src/bit/math/angles/angles.g_sin_table.cpp")

  #---------------------------------------------------------------------------
  # Write Files
  #---------------------------------------------------------------------------

  # Write generator file if not already written
  if( NOT EXISTS "${sin_table_generator_file}.in" )
    file(WRITE "${sin_table_generator_file}.in"
"
#include <cmath>
#include <iostream>

int main()
{
  const auto pi   = @FLOAT_TYPE@(3.14159265358979323846264338327950288419716939937510);
  const auto size = @FLOAT_TYPE@(@BIT_MATH_TRIG_TABLE_SIZE@);

  for(auto i=0; i<@BIT_MATH_TRIG_TABLE_SIZE@; ++i)
  {
    auto angle = pi * (i / size);
    auto result = std::sin(angle);
    std::cout << result << ';';
  }

  return 0;
}"
    )
  endif()

  # Write cache file if not already written
  if( NOT EXISTS "${sin_table_file}.in" )
    file(WRITE "${sin_table_file}.in"
"
// This file is autogenerated through cmake; do not modify
//
//

#include <array>

namespace bit {
  namespace math {

    const std::array<@FLOAT_TYPE@,@BIT_MATH_TRIG_TABLE_SIZE@> g_sin_table = { @SIN_VALUES@ };

  } // namespace math
} // namespace bit"
    )
  endif()

  #---------------------------------------------------------------------------
  # Generate Files
  #---------------------------------------------------------------------------

  configure_file("${sin_table_generator_file}.in" "${sin_table_generator_file}" @ONLY)

  # Generate the cache source file if anything has changed
  if( "${sin_table_file}.in" IS_NEWER_THAN "${sin_table_file}" )
    message(STATUS "Generating sin cache")

    if( UNIX )
      # *nix systems require linking to the math library with -lm
      set(flags "-lm")
    endif()

    try_run(RUN_RESULT_VAR COMPILE_RESULT_VAR
      "${CMAKE_CURRENT_BINARY_DIR}/angles"
      "${sin_table_generator_file}"
      CMAKE_FLAGS ${flags}
      COMPILE_OUTPUT_VARIABLE compile_output
      RUN_OUTPUT_VARIABLE run_output
    )
    string(REPLACE ";" ",\n" SIN_VALUES "${run_output}")

    if( NOT COMPILE_RESULT_VAR )
      message(FATAL_ERROR "Error generating precomputed sin table. Compilation failed with message:\n ${compile_output}")
    endif()

    configure_file("${sin_table_file}.in" "${sin_table_file}" @ONLY)

    message(STATUS "Generating sin cache - done")
  endif()

  #---------------------------------------------------------------------------
  # Append generated sources
  #---------------------------------------------------------------------------

  # Add the cache source file
  list(APPEND sources "${sin_table_file}")

endif()

#-----------------------------------------------------------------------------
# bit::math : Library
#-----------------------------------------------------------------------------

add_library(math ${sources} ${headers})
add_library("bit::math" ALIAS math)
target_include_directories(math PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

# Add compiler-specific flags
if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_compile_options(math PUBLIC -Wall -Wstrict-aliasing -pedantic -Werror)
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
  target_compile_options(math PUBLIC -Wall -Wstrict-aliasing -pedantic -Werror)
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
  # TODO: Determine MSVC necessary compiler flags
endif()

#-----------------------------------------------------------------------------
# bit::math : Header Self-Containment Test
#-----------------------------------------------------------------------------

if( BIT_MATH_COMPILE_HEADER_SELF_CONTAINMENT_TESTS )
  add_header_self_containment_test(math_header_self_containment_test ${headers})
  add_library(bit::math::header_self_containment_test ALIAS math_header_self_containment_test)

  target_include_directories(math_header_self_containment_test PRIVATE $<TARGET_PROPERTY:math,INCLUDE_DIRECTORIES>)
  target_compile_options(math_header_self_containment_test PRIVATE $<TARGET_PROPERTY:math,INTERFACE_COMPILE_OPTIONS>)
endif()

#-----------------------------------------------------------------------------
# bit::math : Unit Tests
#-----------------------------------------------------------------------------

if( BIT_MATH_COMPILE_UNIT_TESTS )
  add_subdirectory(test)
endif()

#-----------------------------------------------------------------------------
# bit::math : Documentation
#-----------------------------------------------------------------------------

if( BIT_MATH_GENERATE_DOCUMENTATION )
  add_subdirectory(doc)
endif()

#-----------------------------------------------------------------------------
# bit::math : Export
#-----------------------------------------------------------------------------

include(ExportLibrary)

if( EXISTS "$ENV{BIT_HOME}" )
  set(CMAKE_INSTALL_PREFIX "$ENV{BIT_HOME}")
endif()

export_library( TARGETS math
                PACKAGE Math
                VERSION ${BIT_MATH_VERSION}
                MAJOR_VERSION ${BIT_MATH_VERSION_MAJOR}
                MINOR_VERSION ${BIT_MATH_VERSION_MINOR}
                INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include"
                              "${CMAKE_CURRENT_BINARY_DIR}/include"
                NAMESPACE "bit::"
                PREFIX_PACKAGE )
