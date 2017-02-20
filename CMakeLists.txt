cmake_minimum_required(VERSION 3.1)

include("${CMAKE_CURRENT_LIST_DIR}/cmake/modules/add_header_library.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/modules/add_test_executable.cmake")

project("bit::math")

set(CMAKE_CXX_VERSION 14)

set(BIT_MATH_VERSION_MAJOR 0 CACHE STRING "major version of bit::math" FORCE)
set(BIT_MATH_VERSION_MINOR 1 CACHE STRING "minor version of bit::math" FORCE)
set(BIT_MATH_VERSION "${BIT_STL_VERSION_MAJOR}.${BIT_STL_VERSION_MINOR}" CACHE STRING "version of bit::math" FORCE)

#-----------------------------------------------------------------------------
# Options
#-----------------------------------------------------------------------------

option(BIT_MATH_DOUBLE_PRECISION "Use double precision for mathematics." off)

option(BIT_COMPILE_INDEPENDENCE_TESTS "Include each header independently in a .cpp file to determine header independence" on)
option(BIT_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" on)

option(BIT_MATH_CACHED_TRIG "Build a cached table for triginometrec function results." off)
option(BIT_MATH_CACHED_INVERSE_TRIG "Build a cached data for inverse triginometric function results." off)

#-----------------------------------------------------------------------------

set(BIT_MATH_TRIG_TABLE_SIZE 4096 CACHE STRING "The size of the trig table to build. This is ignored unless BIT_MATH_CACHED_TRIG is on")

if( BIT_MATH_CACHED_TRIG AND NOT BIT_MATH_TRIG_TABLE_SIZE MATCHES "[1-9][0-9]+" )
  message(FATAL_ERROR "'BIT_MATH_TRIG_TABLE_SIZE' contains invalid value. This must be a numeric entry")
endif()

#-----------------------------------------------------------------------------

set(BIT_MATH_INVERSE_TRIG_TABLE_SIZE 4096 CACHE STRING "The size of the inverse trig table to build. This is ignored unless BIT_MATH_CACHED_INVERSE_TRIG is on")

if( BIT_MATH_CACHED_INVERSE_TRIG AND NOT BIT_MATH_INVERSE_TRIG_TABLE_SIZE MATCHES "[1-9][0-9]+" )
  message(FATAL_ERROR "'BIT_MATH_INVERSE_TRIG_TABLE_SIZE' contains invalid value. This must be a numeric entry")
endif()

#-----------------------------------------------------------------------------
# bit::stl : Interface
#-----------------------------------------------------------------------------

set(headers
      "include/bit/math/angles.hpp"
      "include/bit/math/vector.hpp"
      "include/bit/math/matrix.hpp"
      "include/bit/math/quaternion.hpp"
)
set(sources
      "src/bit/math/angles.cpp"
      "src/bit/math/vector.cpp"
      "src/bit/math/matrix.cpp"
      "src/bit/math/quaternion.cpp"
)

#-----------------------------------------------------------------------------
# bit::math : Library
#-----------------------------------------------------------------------------

add_library("bit_math" ${sources} ${headers})
add_library("bit::math" ALIAS bit_math)
target_include_directories("bit_math" PUBLIC "include")
target_compile_options(bit_math PUBLIC -std=c++14 -DDEBUG)

if( BIT_MATH_DOUBLE_PRECISION )
  target_compile_options(bit_math PUBLIC "-DBIT_MATH_DOUBLE_PRECISION")
endif()

if( BIT_MATH_CACHED_TRIG )
  target_compile_options(bit_math PUBLIC
    "-DBIT_MATH_CACHED_TRIG"
    "-DBIT_MATH_TRIG_TABLE_SIZE=${BIT_MATH_TRIG_TABLE_SIZE}"
  )
endif()

if( BIT_MATH_CACHED_INVERSE_TRIG )
  target_compile_options(bit_math PUBLIC
    "-DBIT_MATH_CACHED_INVERSE_TRIG"
    "-DBIT_MATH_INVERSE_TRIG_TABLE_SIZE=${BIT_MATH_INVERSE_TRIG_TABLE_SIZE}"
  )
endif()

#-----------------------------------------------------------------------------
# bit::math : Interface (independence test)
#-----------------------------------------------------------------------------

if( BIT_COMPILE_INDEPENDENCE_TESTS )

  add_header_library(bit_math_interface ${headers} INCLUDE_DIRECTORIES "include")
  target_include_directories("bit_math_interface" INTERFACE "include")
  target_compile_options(bit_math_interface INTERFACE $<TARGET_PROPERTY:bit_math,INTERFACE_COMPILE_OPTIONS>)

endif()

#-----------------------------------------------------------------------------
# bit::math : Tests
#-----------------------------------------------------------------------------

if( BIT_COMPILE_UNIT_TESTS )

  set(test_sources
        test/main.test.cpp
        test/bit/math/vector2.test.cpp
        test/bit/math/matrix2.test.cpp
  )

  add_test_executable(bit_math_test ${test_sources})
  target_link_libraries(bit_math_test "bit::math")

endif()
