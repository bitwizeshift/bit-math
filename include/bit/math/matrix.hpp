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
      class matrix_caster;
    } // namespace detail

    inline namespace casts {

      template<typename To, typename From>
      To matrix_cast(const From& from);

    } // inline namespace casts

    // Optimize the common case by pre-instantiating the matrix
#ifdef BIT_MATH_DOUBLE_PRECISION
    extern template class matrix2<double>;
    extern template class matrix3<double>;
    extern template class matrix4<double>;
#else
    extern template class matrix2<float>;
    extern template class matrix3<float>;
    extern template class matrix4<float>;
#endif

  } // namespace math
} // namespace bit



#endif /* BIT_MATH_MATRIX_HPP */
