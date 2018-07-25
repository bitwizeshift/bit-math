/*****************************************************************************
 * \file
 * \brief todo: fill in documentation
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
#ifndef BIT_MATH_MATRIX_HPP
#define BIT_MATH_MATRIX_HPP

#include "vector.hpp"

#include <type_traits> // std::true_type/std::false_type
#include <memory>      // std::addressof

// IWYU pragma: begin_exports
#include "detail/matrix/matrix2.hpp"
#include "detail/matrix/matrix3.hpp"
#include "detail/matrix/matrix4.hpp"
// IWYU pragma: end_exports

namespace bit {
  namespace math {
    namespace detail {
      template<typename To, typename From>
      struct matrix_caster;
    } // namespace detail

    inline namespace casts {

      template<typename To, typename From>
      constexpr To matrix_cast(const From& from);

    } // inline namespace casts

    /// \brief Trait to detect whether \p T is a \ref vector4
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_matrix : std::false_type{};

    template<typename T> struct is_matrix<matrix2<T>> : std::true_type{};
    template<typename T> struct is_matrix<matrix3<T>> : std::true_type{};
    template<typename T> struct is_matrix<matrix4<T>> : std::true_type{};

    // Optimize the common case by pre-instantiating the matrix

    extern template class matrix2<float_t>;
    extern template class matrix3<float_t>;
    extern template class matrix4<float_t>;

    using mat2 = matrix2<float_t>;
    using mat3 = matrix3<float_t>;
    using mat4 = matrix4<float_t>;

  } // namespace math
  inline namespace casts {
    using namespace math::casts;
  } // inline namespace casts
} // namespace bit

#include "detail/matrix.inl"

#endif /* BIT_MATH_MATRIX_HPP */
