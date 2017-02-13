/**
 * \file vector.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_VECTOR_HPP
#define BIT_MATH_VECTOR_HPP

#include <utility>
#include <stdexcept>
#include <cstddef>
#include <cstdint>

#include "math.hpp"
#include "angles.hpp"

// Include vector types
#include "detail/vector/vector2.hpp"
#include "detail/vector/vector3.hpp"
#include "detail/vector/vector4.hpp"

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

    // Optimize the common case by pre-instantiating the vector
#ifdef BIT_MATH_DOUBLE_PRECISION
    extern template class vector2<double>;
    extern template class vector3<double>;
    extern template class vector4<double>;
#else
    extern template class vector2<float>;
    extern template class vector3<float>;
    extern template class vector4<float>;
#endif

  } // namespace math
} // namespace bit

#include "detail/vector.inl"

#endif /* BIT_MATH_VECTOR_HPP */
