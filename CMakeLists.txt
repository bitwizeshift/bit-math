cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

include(GitBuildInformation)
include(MakeVersionHeader)
include(AddIndependenceCheck)
include(AddTestExecutable)

project("bit-math")

# This project requires at least c++14 support
set(CMAKE_CXX_VERSION 14)

git_build_information( PATCH_VARIABLE BIT_MATH_VERSION_PATCH
                       BUILD_VARIABLE BIT_MATH_BUILD_NUMBER
                       BRANCH_VARIABLE BIT_MATH_BRANCH
                       REF 574bf75d354bf269e0e5aa1fbb4290166bdba74d
)

set(BIT_MATH_VERSION_MAJOR 0 CACHE STRING "major version of bit::math" FORCE)
set(BIT_MATH_VERSION_MINOR 1 CACHE STRING "minor version of bit::math" FORCE)
set(BIT_MATH_VERSION_PATCH ${BIT_MATH_VERSION_PATCH} CACHE STRING "patch version of bit::math" FORCE)
set(BIT_MATH_VERSION "${BIT_MATH_VERSION_MAJOR}.${BIT_MATH_VERSION_MINOR}.${BIT_MATH_VERSION_PATCH}" CACHE STRING "version of bit::math" FORCE)
set(BIT_MATH_BUILD_NUMBER "${BIT_MATH_BUILD_NUMBER}" CACHE STRING "build number of bit::math" FORCE)

message(STATUS "bit::math ${BIT_MATH_VERSION} (${BIT_MATH_BRANCH} ${BIT_MATH_BUILD_NUMBER})")

make_version_header("${CMAKE_CURRENT_BINARY_DIR}/include/version.hpp"
  MAJOR ${BIT_MATH_VERSION_MAJOR}
  MINOR ${BIT_MATH_VERSION_MINOR}
  PATCH ${BIT_MATH_VERSION_PATCH}
  BUILD ${BIT_MATH_BUILD_NUMBER}
  PREFIX BIT_MATH
  SUFFIX "a"
  TAG ${BIT_MATH_BRANCH}
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")

#-----------------------------------------------------------------------------
# bit::stl : Sources
#-----------------------------------------------------------------------------

set(headers
      "include/bit/math/angles.hpp"
      "include/bit/math/vector.hpp"
      "include/bit/math/matrix.hpp"
      "include/bit/math/quaternion.hpp"
      "include/bit/math/clamped.hpp"
      "include/bit/math/euler.hpp"
)

set(sources
      "${CMAKE_CURRENT_BINARY_DIR}/include/version.hpp"
      "src/bit/math/angles.cpp"
      "src/bit/math/vector.cpp"
      "src/bit/math/matrix.cpp"
      "src/bit/math/quaternion.cpp"
      "src/bit/math/euler.cpp"
)

#-----------------------------------------------------------------------------
# Options
#-----------------------------------------------------------------------------

option(BIT_MATH_DOUBLE_PRECISION "Use double precision for mathematics." off)

option(BIT_COMPILE_INDEPENDENCE_TESTS "Include each header independently in a .cpp file to determine header independence" on)
option(BIT_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" on)

option(BIT_MATH_CACHED_TRIG "Build a cached table for triginometrec function results." off)

set(BIT_MATH_TRIG_TABLE_SIZE 1024 CACHE STRING "The size of the trig table to build. This is ignored unless BIT_MATH_CACHED_TRIG is on")

set(BIT_MATH_INVERSE_TRIG_TABLE_SIZE 4096 CACHE STRING "The size of the inverse trig table to build. This is ignored unless BIT_MATH_CACHED_TRIG is on")

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
// This file is autogenerated, do not modify
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

  configure_file("${sin_table_generator_file}.in" "${sin_table_generator_file}"  @ONLY)

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
target_compile_options(math PUBLIC -std=c++14
  $<$<CONFIG:DEBUG>:-DDEBUG>
  $<$<CONFIG:RELEASE>:-DNDEBUG -DRELEASE>
)

if( BIT_MATH_DOUBLE_PRECISION )
  target_compile_options(math PUBLIC "-DBIT_MATH_DOUBLE_PRECISION")
endif()

if( BIT_MATH_CACHED_TRIG )
  target_compile_definitions(math PUBLIC
    "-DBIT_MATH_CACHED_TRIG"
    "-DBIT_MATH_TRIG_TABLE_SIZE=${BIT_MATH_TRIG_TABLE_SIZE}"
    "-DBIT_MATH_INVERSE_TRIG_TABLE_SIZE=${BIT_MATH_INVERSE_TRIG_TABLE_SIZE}"
  )
endif()

#-----------------------------------------------------------------------------
# bit::math : Interface (independence test)
#-----------------------------------------------------------------------------

if( BIT_COMPILE_INDEPENDENCE_TESTS )

  add_independence_check(bit_math_interface ${headers})
  target_include_directories("bit_math_interface" PRIVATE "include")
  target_compile_options(bit_math_interface PRIVATE $<TARGET_PROPERTY:math,INTERFACE_COMPILE_OPTIONS>)

endif()

#-----------------------------------------------------------------------------
# bit::math : Tests
#-----------------------------------------------------------------------------

if( BIT_COMPILE_UNIT_TESTS )

  find_package(Catch)

  set(test_sources
        test/main.test.cpp
        test/bit/math/vector2.test.cpp
        test/bit/math/matrix2.test.cpp
        test/bit/math/quaternion.test.cpp
        test/bit/math/clamped.test.cpp
  )

  add_test_executable(bit_math_test ${test_sources})
  target_link_libraries(bit_math_test "bit::math" "philsquared::Catch")

endif()

#-----------------------------------------------------------------------------
# bit::math : Export
#-----------------------------------------------------------------------------

include(ExportLibrary)

if( EXISTS "$ENV{BIT_HOME}" )
  set(CMAKE_INSTALL_PREFIX "$ENV{BIT_HOME}")
endif()

export_library( TARGETS math
                PACKAGE math
                VERSION ${BIT_MATH_VERSION}
                MAJOR_VERSION ${BIT_MATH_VERSION_MAJOR}
                MINOR_VERSION ${BIT_MATH_VERSION_MINOR}
                INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include"
                              "${CMAKE_CURRENT_BINARY_DIR}/include"
                NAMESPACE "bit::"
                PREFIX_PACKAGE )
