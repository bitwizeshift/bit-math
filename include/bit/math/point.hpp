/*****************************************************************************
 * \file
 * \brief This header contains the geometric primitive 'point' used to
 *        identify a location in 2d or 3d coordinate systems
 *****************************************************************************/

/*
  The MIT License (MIT)

  Bit Math Library.
  https://github.com/bitwizeshift/bit-math

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
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
