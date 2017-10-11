cmake_minimum_required(VERSION 3.1)

find_package(Catch REQUIRED)

set(source_files
  main.test.cpp

  test/main.test.cpp
  test/bit/math/vector2.test.cpp
  test/bit/math/matrix2.test.cpp
  test/bit/math/quaternion.test.cpp
  test/bit/math/clamped.test.cpp
)

add_executable(math_test ${source_files})

target_link_libraries(math_test PRIVATE "bit::math" "philsquared::Catch")

#-----------------------------------------------------------------------------
# Testing
#-----------------------------------------------------------------------------

add_test( NAME "math_test_default"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:math_test>" )

#-----------------------------------------------------------------------------

add_test( NAME "math_test_all"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:math_test>" "*" )
