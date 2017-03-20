/**
 * \file matrix.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_MATRIX_HPP
#define BIT_MATH_MATRIX_HPP

#include "vector.hpp"

#include "detail/matrix/matrix2.hpp"
#include "detail/matrix/matrix3.hpp"
#include "detail/matrix/matrix4.hpp"

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

    // Optimize the common case by pre-instantiating the matrix
#ifdef BIT_MATH_DOUBLE_PRECISION
    extern template class matrix2<double>;
    extern template class matrix3<double>;
    extern template class matrix4<double>;

    using mat2 = matrix2<double>;
    using mat3 = matrix3<double>;
    using mat4 = matrix4<double>;
#else
    extern template class matrix2<float>;
    extern template class matrix3<float>;
    extern template class matrix4<float>;

    using mat2 = matrix2<float>;
    using mat3 = matrix3<float>;
    using mat4 = matrix4<float>;
#endif

  } // namespace math
} // namespace bit

#include "detail/matrix.inl"

#endif /* BIT_MATH_MATRIX_HPP */
