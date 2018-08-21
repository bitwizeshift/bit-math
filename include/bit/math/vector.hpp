/*****************************************************************************
 * \file
 * \todo Document this
 *****************************************************************************/

/*
  The MIT License (MIT)

  Bit Standard Template Library.
  https://github.com/bitwizeshift/bit-stl

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
#ifndef BIT_MATH_VECTOR_HPP
#define BIT_MATH_VECTOR_HPP

// bit::math library
#include "math.hpp"
#include "angles.hpp"

// std library
#include <utility>
#include <stdexcept>
#include <cstddef>
#include <cstdint>

// IWYU pragma: begin_exports
#include "detail/vector/vector2.hpp"
#include "detail/vector/vector3.hpp"
#include "detail/vector/vector4.hpp"
// IWYU pragma: end_exports

namespace bit {
  namespace math {
    namespace detail {

      template<typename To, typename From>
      struct vector_caster;

    } // namespace detail

    inline namespace casts {

      /// \brief Casts from one vector type to another
      ///
      /// \param from the vector to cast from
      /// \return the vector to cast to
      template<typename To, typename From>
      constexpr To vector_cast( const From& from ) noexcept;

    } // inline namespace casts

    /// \brief Trait to detect whether \p T is a \ref vector4
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_vector : std::false_type{};

    template<typename T> struct is_vector<vector2<T>> : std::true_type{};
    template<typename T> struct is_vector<vector3<T>> : std::true_type{};
    template<typename T> struct is_vector<vector4<T>> : std::true_type{};

    // Optimize the common case by pre-instantiating the vector

    extern template class vector2<float_t>;
    extern template class vector3<float_t>;
    extern template class vector4<float_t>;

    using vec2 = vector2<float_t>;
    using vec3 = vector3<float_t>;
    using vec4 = vector3<float_t>;

  } // namespace math

  inline namespace casts {
    using namespace math::casts;
  } // inline namespace casts
} // namespace bit

#include "detail/vector.inl"

#endif /* BIT_MATH_VECTOR_HPP */
