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
} // namespace bit

#include "detail/matrix.inl"

#endif /* BIT_MATH_MATRIX_HPP */
