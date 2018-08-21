cmake_minimum_required(VERSION 3.1)

##############################################################################
# Test Options
##############################################################################

option(BIT_MATH_ENABLE_ASAN "Compile and run the address sanetizer" OFF)
option(BIT_MATH_ENABLE_USAN "Compile and run the undefined behavior sanitizer" OFF)
option(BIT_MATH_ENABLE_TSAN "Compile and run the thread sanitizer" OFF)
option(BIT_MATH_ENABLE_COVERAGE "Compile and run code coverage" OFF)

##############################################################################
# Unit Tests
##############################################################################

find_package(Catch REQUIRED)

set(source_files
  main.test.cpp

  bit/math/vector2.test.cpp
  bit/math/matrix2.test.cpp
  bit/math/quaternion.test.cpp
  bit/math/clamped.test.cpp
)

link_libraries("Bit::math" "philsquared::Catch")

add_executable(math_test ${source_files})
add_executable(Bit::math_test ALIAS math_test)

add_test(
  NAME "math_test_default"
  COMMAND math_test -r junit -o "${CMAKE_CURRENT_BINARY_DIR}/bit_math_test.xml"
)

##############################################################################
# Address Sanitizer
##############################################################################

if( BIT_MATH_ENABLE_ASAN )

  add_executable(math_asan ${source_files})
  add_executable(Bit::math_asan ALIAS math_asan)

  target_compile_options(math_asan PRIVATE
    -g
    -O1
    -fno-omit-frame-pointer
    -fsanitize=address
    -fsanitize=leak
  )
  set_property(
    TARGET math_asan
    APPEND PROPERTY LINK_FLAGS "-fsanitize=address -fsanitize=leak"
  )

  add_test(
    NAME "math_asan_default"
    COMMAND math_asan
  )
endif()

#-----------------------------------------------------------------------------
# Undefined Behavior Sanitizer
#-----------------------------------------------------------------------------

if( BIT_MATH_ENABLE_UBSAN )

  add_executable(math_ubsan ${source_files})
  add_executable(Bit::math_ubsan ALIAS math_ubsan)

  target_compile_options(math_ubsan PRIVATE
    -fsanitize=undefined
  )
  set_property(
    TARGET math_ubsan
    APPEND PROPERTY LINK_FLAGS -fsanitize=undefined
  )

  add_test(
    NAME "math_ubsan_default"
    COMMAND math_ubsan
  )
endif()

#-----------------------------------------------------------------------------
# Thread Sanitizer
#-----------------------------------------------------------------------------

if( BIT_MATH_ENABLE_TSAN )

  add_executable(math_tsan ${source_files})
  add_executable(Bit::math_tsan ALIAS math_tsan)

  target_compile_options(math_tsan PRIVATE
    -fsanitize=thread
  )
  set_property(
    TARGET math_tsan
    APPEND PROPERTY LINK_FLAGS -fsanitize=thread
  )

  add_test(
    NAME "math_tsan_default"
    COMMAND math_tsan
  )
endif()

#-----------------------------------------------------------------------------
# Code Coverage
#-----------------------------------------------------------------------------

if( BIT_MATH_ENABLE_COVERAGE )

  add_executable(math_coverage ${source_files})
  add_executable(Bit::math_coverage ALIAS math_coverage)

  target_compile_options(math_coverage PRIVATE
    -g
    -O0
    -fprofile-arcs
    -ftest-coverage
  )
  set_property(
    TARGET math_coverage
    APPEND PROPERTY LINK_FLAGS --coverage
  )

  add_test(
    NAME "math_coverage_default"
    COMMAND math_coverage
  )
endif()
