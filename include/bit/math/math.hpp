/**
 * \file math.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_MATH_HPP
#define BIT_MATH_MATH_HPP

#include "version.hpp"

#include <cmath>
#include <type_traits>
#include <utility>

namespace bit {
  namespace math {

    //------------------------------------------------------------------------
    // Types
    //------------------------------------------------------------------------

#if BIT_MATH_DOUBLE_PRECISION
    using float_t = double;
#else
    using float_t = float;
#endif

    template<typename T>
    using enable_if_float = std::enable_if<std::is_floating_point<T>::value>;

    template<typename T>
    using enable_if_float_t = typename enable_if_float<T>::type;

    template<typename T>
    using math_result_t = std::conditional_t<
      std::is_floating_point<T>::value,
      T,
      float_t
    >;

    //------------------------------------------------------------------------
    // Constants
    //------------------------------------------------------------------------

    /// The tolerance to use for floating-point equality
    static constexpr float_t default_tolerance = (float_t) 1e-6f;

    /// \brief Retrieves the value for the mathematical constant PI
    template<typename T>
    constexpr T pi() noexcept;

    /// \brief Retrieves the value for half of the mathematical constant PI
    template<typename T>
    constexpr T half_pi() noexcept;

    /// \brief Retrieves the value for twice the mathematical constant PI
    template<typename T>
    constexpr T two_pi() noexcept;

    //------------------------------------------------------------------------
    // Products
    //------------------------------------------------------------------------

    /// \brief Calculates the dot product between two arrays
    ///
    /// \param lhs the left array
    /// \param rhs the right array
    /// \return the dot product of the two arrays
    template<typename T, typename U, std::size_t N>
    constexpr std::common_type_t<T,U> dot( T(&lhs)[N], U(&rhs)[N] ) noexcept;

    //------------------------------------------------------------------------
    // Rounding
    //------------------------------------------------------------------------

    /// \brief Rounds the floating point value \p a
    ///
    /// \param a the floating point value
    /// \return the rounded float value
    template<typename Arithmetic>
    Arithmetic round( Arithmetic a ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Computes the smallest integer value not less than \p a
    ///
    /// \param a the floating point value
    /// \return the ceiling of \p a
    template<typename Arithmetic>
    Arithmetic ceil( Arithmetic a ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Computes the smallest integer value not less than \p a
    ///
    /// \param a the floating point value
    /// \return the ceiling of \p a
    template<typename Arithmetic>
    Arithmetic floor( Arithmetic a ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Truncates the arithmetic value \p a
    ///
    /// \param a the value to truncate
    /// \return the truncated value
    template<typename Arithmetic>
    Arithmetic trunc( Arithmetic a ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Calculates the modulo of \p num by \p den
    ///
    /// This function promotes the return value to the common type of
    /// \p num and \p den
    ///
    /// \param num the numerator
    /// \param den the denominator
    /// \return the modulo of \p num and \p den
    template<typename T, typename U>
    std::common_type_t<T,U> mod( T num, U den ) noexcept;

    //------------------------------------------------------------------------
    // Squares
    //------------------------------------------------------------------------

    /// \brief Squares the value of \p a
    ///
    /// \param a the value to square
    /// \return the square of \p a
    template<typename Arithmetic>
    constexpr Arithmetic sqr( Arithmetic a ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Computes the square-root of \p a
    ///
    /// \param a the value to square-root
    /// \return the square-root of \p a
    template<typename Arithmetic>
    math_result_t<Arithmetic> sqrt( Arithmetic a ) noexcept;

    //------------------------------------------------------------------------
    // Cubes
    //------------------------------------------------------------------------

    /// \brief Cubes the value of \p a
    ///
    /// \param a the value to cube
    /// \return the cube of \p a
    template<typename Arithmetic>
    constexpr math_result_t<Arithmetic> cube( Arithmetic a ) noexcept;

    //------------------------------------------------------------------------
    // Logarithms
    //------------------------------------------------------------------------

    /// \brief Computes the logarithm (base-10) of \p a
    ///
    /// \param a the arithmetic type to determine the logarithm
    /// \return the result of the logarithm
    template<typename Arithmetic>
    math_result_t<Arithmetic> log( Arithmetic a ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Computes the logarithm (base-2) of \p a
    ///
    /// \param a the arithmetic type to determine the logarithm
    /// \return the result of the logarithm
    template<typename Arithmetic>
    math_result_t<Arithmetic> log2( Arithmetic a ) noexcept;

    //------------------------------------------------------------------------
    // Absolute Values
    //------------------------------------------------------------------------

    /// \brief Absolute value function specialization for signed types
    ///
    /// \param x the signed value
    /// \return \p x the absolute value of \p x (\c |x| )
#ifndef BIT_DOXYGEN_BUILD
    template<typename Arithmetic, std::enable_if_t<std::is_signed<Arithmetic>::value>* = nullptr>
#else
    template<typename Arithmetic>
#endif
    constexpr Arithmetic abs( Arithmetic x ) noexcept;

    /// \brief Absolute value function specialization for unsigned types
    ///
    /// This function acts as a simple type-safe identity that returns the
    /// input value
    ///
    /// \param x the unsigned value
    /// \return \p x
#ifndef BIT_DOXYGEN_BUILD
    template<typename Arithmetic, std::enable_if_t<std::is_unsigned<Arithmetic>::value>* = nullptr>
#else
    template<typename Arithmetic>
#endif
    constexpr Arithmetic abs( Arithmetic x ) noexcept;

    //------------------------------------------------------------------------
    // Clamping
    //------------------------------------------------------------------------

    /// \brief Clamps a value between [\p min , \p max ]
    ///
    /// \param val the value to clamp
    /// \param max the max value
    /// \param min the min value
    /// \return the clamped value
    template<typename T, typename U, typename V>
    constexpr std::common_type_t<T,U,V>
      clamp( T val, U max, V min ) noexcept;

    /// \brief Clamps a floating value between \c [0,1]
    ///
    /// \param val the value to clamp
    /// \return the clamped value
    template<typename Float>
    constexpr Float saturate( Float val ) noexcept;

    //========================================================================
    // Floating Point Math
    //========================================================================

    //------------------------------------------------------------------------
    // Equality
    //------------------------------------------------------------------------

    /// \brief Determines relative equality between \p lhs and \p rhs relative
    ///        to \ref default_tolerance
    ///
    /// \param lhs the value on the left of the equation
    /// \param rhs the value on the right of the equation
    /// \return \c true if \p lhs is almost equal to \p rhs
    template<typename T, typename U>
    constexpr bool almost_equal( T lhs, U rhs ) noexcept;

    /// \brief Determines relative equality between \p lhs and \p rhs relative
    ///        to the specified \p tolerance
    ///
    /// \param lhs the value on the left of the equation
    /// \param rhs the value on the right of the equation
    /// \param tolerance the tolerance to use for comparison
    /// \return \c true if \p lhs is almost equal to \p rhs
    template<typename T, typename U, typename V>
    constexpr bool almost_equal( T lhs, U rhs, V tolerance ) noexcept;

    //------------------------------------------------------------------------
    // Finite
    //------------------------------------------------------------------------

    /// \brief Determines whether a given integral value \p f is a nan
    ///
    /// For non float-values, the entry is normalized to a \ref float_t
    ///
    /// \param f the value to check
    /// \return \c true if \p f is a \c nan
    template<typename Float>
    bool is_nan( Float f ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Determines whether a given integral value \p f is finite
    ///
    /// For non float-values, the entry is normalized to a \ref float_t
    ///
    /// \param f the value to check
    /// \return \c true if \p f is \c finite
    template<typename Float>
    bool is_finite( Float f ) noexcept;

    /// \brief Determines whether a given integral value \p f is infinite
    ///
    /// For non float-values, the entry is normalized to a \ref float_t
    ///
    /// \param f the value to check
    /// \return \c true if \p f is \c infinite
    template<typename Float>
    bool is_infinite( Float f ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Determines whether a given integral value \p f is normal
    ///
    /// For non float-values, the entry is normalized to a \ref float_t
    ///
    /// \param f the value to check
    /// \return \c true if \p f is \c normal
    template<typename Float>
    bool is_normal( Float f ) noexcept;

    /// \brief Determines whether a given integral value \p f is subnormal
    ///
    /// For non float-values, the entry is normalized to a \ref float_t
    ///
    /// \param f the value to check
    /// \return \c true if \p f is \c subnormal
    template<typename Float>
    bool is_subnormal( Float f ) noexcept;

  } // namespace math
} // namespace bit

#include "detail/math.inl"

#endif /* BIT_MATH_MATH_HPP */
