/**
 * \file point.hpp
 *
 * \brief This header contains the geometric primitive 'point' used to
 *        identify a location in 2d or 3d coordinate systems
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_DETAIL_GEOMETRY_POINT_HPP
#define BIT_MATH_DETAIL_GEOMETRY_POINT_HPP

// bit::math library
#include "../vector.hpp"

// std library
#include <cstddef> // std::size_t, std::ptrdiff_t
#include <tuple>   // std::tie

// IWYU pragma: begin_exports
#include "detail/point/point2.hpp"
#include "detail/point/point3.hpp"
// IWYU pragma: end_exports

#endif /* BIT_MATH_DETAIL_GEOMETRY_POINT_HPP */
