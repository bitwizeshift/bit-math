cmake_minimum_required(VERSION 3.1)

find_package(Catch REQUIRED)

set(source_files
  main.test.cpp

  bit/math/vector2.test.cpp
  bit/math/matrix2.test.cpp
  bit/math/quaternion.test.cpp
  bit/math/clamped.test.cpp
)

add_executable(bit_math_test ${source_files})

target_link_libraries(bit_math_test PRIVATE "bit::math" "philsquared::Catch")

#-----------------------------------------------------------------------------
# Testing
#-----------------------------------------------------------------------------

add_test( NAME "bit_math_test_default"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:bit_math_test>" )

#-----------------------------------------------------------------------------

add_test( NAME "bit_math_test_all"
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND "$<TARGET_FILE:bit_math_test>" "*" )
