cmake_minimum_required(VERSION 3.1)

enable_testing()

set(BIT_MATH_CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake/Modules")
set(BIT_MATH_CMAKE_FIND_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake/FindModules")
set(BIT_MATH_CMAKE_TEMPLATE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake/Templates")

set(CMAKE_MODULE_PATH "${BIT_MATH_CMAKE_MODULE_PATH}" "${CMAKE_MODULE_PATH}")

##############################################################################
# Project Options
##############################################################################

option(BIT_MATH_COMPILE_HEADER_SELF_CONTAINMENT_TESTS "Include each header independently in a .cpp file to determine header self-containment" OFF)
option(BIT_MATH_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" OFF)
option(BIT_MATH_GENERATE_DOCS "Generates doxygen documentation" OFF)
option(BIT_MATH_INSTALL_DOCS "Install documentation for this library" OFF)
option(BIT_MATH_VERBOSE_CONFIGURE "Verbosely configures this library project" OFF)

option(BIT_MATH_DOUBLE_PRECISION "Use double precision for mathematics." OFF)
option(BIT_MATH_INCLUDE_HALF "Includes bit::math::half for IEEE half-precision floating points" ON)

set(BIT_MATH_DOXYGEN_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/doxygen" CACHE STRING "Output location for doxygen")

##############################################################################
# Project
##############################################################################

project("BitMath" LANGUAGES CXX)

set(BIT_MATH_VERSION_MAJOR 0 CACHE STRING "major version of bit::math" FORCE)
set(BIT_MATH_VERSION_MINOR 1 CACHE STRING "minor version of bit::math" FORCE)
set(BIT_MATH_VERSION_PATCH 62 CACHE STRING "patch version of bit::math" FORCE)

set(BIT_MATH_VERSION "${BIT_MATH_VERSION_MAJOR}.${BIT_MATH_VERSION_MINOR}.${BIT_MATH_VERSION_PATCH}" CACHE STRING "version of Bit::math" FORCE)

if( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake" )
  include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
  conan_basic_setup(TARGETS)
else()
  # Setup backup path if Conan is not used
  set(CMAKE_MODULE_PATH "${BIT_MATH_CMAKE_FIND_MODULE_PATH}" "${CMAKE_MODULE_PATH}")
endif()

if( BIT_MATH_VERBOSE_CONFIGURE )
  message(STATUS "Bit::math ${BIT_MATH_VERSION}")
endif()

#-----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# default to debug when building CMake
if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES )
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

#-----------------------------------------------------------------------------

if(BIT_MATH_DOUBLE_PRECISION)
  set(FLOAT_TYPE "double")
else()
  set(FLOAT_TYPE "float")
endif()

# Generate Files
configure_file(
  "${BIT_MATH_CMAKE_TEMPLATE_PATH}/version.hpp.in"
  "${CMAKE_CURRENT_LIST_DIR}/generated-include/bit/math/version.hpp"
  @ONLY
)
configure_file(
  "${BIT_MATH_CMAKE_TEMPLATE_PATH}/config.hpp.in"
  "${CMAKE_CURRENT_LIST_DIR}/generated-include/bit/math/config.hpp"
  @ONLY
)

#-----------------------------------------------------------------------------

set(headers
  include/bit/math/angles.hpp
  include/bit/math/vector.hpp
  include/bit/math/matrix.hpp
  include/bit/math/quaternion.hpp
  include/bit/math/clamped.hpp
  include/bit/math/euler.hpp
  include/bit/math/interpolation.hpp
  include/bit/math/transform.hpp
  include/bit/math/simplex.hpp
)

set(sources
  src/bit/math/angles.cpp
  src/bit/math/vector.cpp
  src/bit/math/matrix.cpp
  src/bit/math/quaternion.cpp
  src/bit/math/euler.cpp
  src/bit/math/simplex.cpp
)


if( BIT_MATH_INCLUDE_HALF )
  list(APPEND headers include/bit/math/half.hpp)
  list(APPEND sources src/bit/math/half.cpp)
endif()

if( BIT_MATH_CACHED_TRIG )
  list(APPEND sources generated-src/bit/math/trig_table.cpp)
endif()

#-----------------------------------------------------------------------------

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
  add_compile_options(-Wall -Wstrict-aliasing -pedantic -Werror)
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
  # TODO: Determine MSVC necessary compiler flags
endif()

add_library(math ${sources} ${headers})
add_library(Bit::math ALIAS math)
target_include_directories(math PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/generated-include>
  $<INSTALL_INTERFACE:include>
)

# *nix systems require linking to the math library with -lm
if( UNIX )
  target_link_libraries(math PRIVATE "m")
endif()

##############################################################################
# Header Self-Containment Tests
##############################################################################

include(AddHeaderSelfContainmentTest)

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
  add_subdirectory(docs)
endif()

##############################################################################
# Installation
##############################################################################

set(PACKAGE_NAME "BitMath")
set(PACKAGE_VERSION "${BIT_MATH_VERSION}")
set(PACKAGE_VERSION_MAJOR "${BIT_MATH_VERSION_MAJOR}")
set(PACKAGE_VERSION_MINOR "${BIT_MATH_VERSION_MINOR}")

configure_file(
  "${BIT_MATH_CMAKE_TEMPLATE_PATH}/PackageConfigVersion.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}ConfigVersion.cmake"
  @ONLY
)

configure_file(
  "${BIT_MATH_CMAKE_TEMPLATE_PATH}/PackageConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}Config.cmake"
  @ONLY
)

#-----------------------------------------------------------------------------

include(GNUInstallDirs)

set(BIT_MATH_CMAKE_CONFIG_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PACKAGE_NAME}")

# Includes

set(exclude_filter)
if( NOT BIT_MATH_INCLUDE_HALF )
  set(exclude_filter PATTERN "bit/math/half.hpp" EXCLUDE)
endif()
install(
  DIRECTORY "include/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  ${exclude_filter}
)

set(exclude_filter)
if( NOT BIT_MATH_CACHED_TRIG )
  set(exclude_filter PATTERN "generated-include/bit/math/trig_table.hpp" EXCLUDE)
endif()
install(
  DIRECTORY "generated-include/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  ${exclude_filter}
)

# Targets
install(
  TARGETS "math"
  EXPORT "${PACKAGE_NAME}Targets"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
install(
  EXPORT "${PACKAGE_NAME}Targets"
  NAMESPACE "Bit::"
  DESTINATION "${BIT_MATH_CMAKE_CONFIG_DESTINATION}"
)
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}ConfigVersion.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}Config.cmake"
  DESTINATION "${BIT_MATH_CMAKE_CONFIG_DESTINATION}"
)

# Documentation
if( BIT_MATH_INSTALL_DOCS AND BIT_MATH_GENERATE_DOCS )
  install(
    DIRECTORY "${BIT_MATH_DOXYGEN_OUTPUT_PATH}/"
    DESTINATION "${CMAKE_INSTALL_DOCDIR}"
  )
endif()
