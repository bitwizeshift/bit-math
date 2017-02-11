/**
 * \file math.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_MATH_HPP
#define BIT_MATH_MATH_HPP

#include <cmath>
#include <type_traits>
#include <utility>

namespace bit {
  namespace math {

    //------------------------------------------------------------------------
    // Types
    //------------------------------------------------------------------------

#ifdef BIT_MATH_DOUBLE_PRECISION
    using float_t = double;
#else
    using float_t = float;
#endif


    template<typename T>
    using enable_if_float = std::enable_if<std::is_floating_point<T>::value>;

    template<typename T>
    using enable_if_float_t = typename enable_if_float<T>::type;

    //------------------------------------------------------------------------
    // Constants
    //------------------------------------------------------------------------

    /// The tolerance to use for floating-point equality
    static const float_t default_tolerance = 0.0;

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
    // Conversion
    //------------------------------------------------------------------------

    /// \brief Calculates the dot product between two arrays
    ///
    /// \param lhs the left array
    /// \param rhs the right array
    /// \return the dot product of the two arrays
    template<typename T, typename U, size_t N>
    constexpr auto dot( T (&lhs)[N], U (&rhs)[N] ) noexcept
      -> std::common_type_t<T,U>;

    //------------------------------------------------------------------------
    // Rounding
    //------------------------------------------------------------------------

    /// \brief Rounds the floating point value \p f
    ///
    /// \param f the floating point value
    /// \return the rounded float value
    float round( float f ) noexcept;

    /// \copydoc round( float )
    double round( double f ) noexcept;

    /// \copydoc round( float )
    long double trunc( long double f ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Computes the smallest integer value not less than \p f
    ///
    /// \param f the floating point value
    /// \return the ceiling of \p f
    float ceil( float f ) noexcept;

    /// \copydoc ceil( float )
    double ceil( double f ) noexcept;

    /// \copydoc ceil( float )
    long double ceil( long double f ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Computes the smallest integer value not less than \p f
    ///
    /// \param f the floating point value
    /// \return the ceiling of \p f
    float floor( float f ) noexcept;

    /// \copydoc floor( float )
    double floor( double f ) noexcept;

    /// \copydoc floor( float )
    long double floor( long double f ) noexcept;

    //------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------

    /// \brief Calculates the absolute value of \p f
    ///
    /// \param f the value to calculate
    /// \return the absolute value of \p f
    float abs( float f ) noexcept;

    /// \copydoc abs( float )
    double abs( double f ) noexcept;

    /// \copydoc abs( float )
    long double abs( long double f ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Squares the value of \p f
    ///
    /// \param f the value to square
    /// \return the square of \p f
    constexpr float sqr( float f ) noexcept;

    /// \copydoc sqr( float )
    constexpr double sqr( double f ) noexcept;

    /// \copydoc sqr( float )
    constexpr long double sqr( long double f ) noexcept;

    //------------------------------------------------------------------------

    float sqrt( float f ) noexcept;

    /// \copydoc sqrt( float )
    double sqrt( double f ) noexcept;

    /// \copydoc sqrt( float )
    long double sqrt( long double f ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    auto mod( T num, U den ) noexcept -> std::common_type_t<T,U>;

    //------------------------------------------------------------------------

    float log( float f ) noexcept;

    /// \copydoc log( float )
    double log( double f ) noexcept;

    /// \copydoc log( float )
    long double log( long double f ) noexcept;

    //------------------------------------------------------------------------

    float log2( float f ) noexcept;

    /// \copydoc log2( float )
    double log2( double f ) noexcept;

    /// \copydoc log2( float )
    long double log2( long double f ) noexcept;

    /// \brief Clamps a value between [\p min , \p max ]
    ///
    /// \param val the value to clamp
    /// \param max the max value
    /// \param min the min value
    /// \return the clamped value
    template<typename T, typename U, typename V>
    constexpr auto clamp( T val, U max, V min ) noexcept
      -> std::common_type_t<T,U,V>;

    /// \brief Clamps a floating value between \c [0,1]
    ///
    /// \param val the value to clamp
    /// \return the clamped value
    constexpr float saturate( float val ) noexcept;

    /// \copydoc saturate( float )
    constexpr double saturate( double val ) noexcept;

    /// \copydoc saturate( float )
    constexpr long double saturate( long double val ) noexcept;

    //------------------------------------------------------------------------
    // Trig Functions
    //------------------------------------------------------------------------

    //------------------------------------------------------------------------
    // Table Trig Functions
    //------------------------------------------------------------------------

    //------------------------------------------------------------------------
    // Equality
    //------------------------------------------------------------------------

    template<typename T, typename U, typename V>
    constexpr bool almost_equal( T lhs, U rhs, V tolerance = default_tolerance ) noexcept;

  } // namespace math
} // namespace bit


//----------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------

template<typename T>
inline constexpr T bit::math::pi()
  noexcept
{
  return 3.14159265358979323846264338327950288419716939937510;
}

template<typename T>
inline constexpr T bit::math::two_pi()
  noexcept
{
  return 2 * pi<T>();
}

template<typename T>
inline constexpr T bit::math::half_pi()
  noexcept
{
  return 0.5 * pi<T>();
}

//----------------------------------------------------------------------------
// Rounding
//----------------------------------------------------------------------------

inline float bit::math::log2( float f )
  noexcept;

/// \copydoc log2( float )
inline double bit::math::log2( double f )
  noexcept;

/// \copydoc log2( float )
inline long double bit::math::log2( long double f )
  noexcept;


//----------------------------------------------------------------------------
// Clamping
//----------------------------------------------------------------------------

template<typename T, typename U, typename V>
inline constexpr std::common_type_t<T,U,V> bit::math::clamp( T val, U max, V min )
  noexcept
{
  return ((val < min) ? min : ((val > max) ? max : val));
}

//----------------------------------------------------------------------------

inline constexpr float bit::math::saturate( float val )
  noexcept
{
  return clamp( val, 1.0f, 0.0f );
}


inline constexpr double bit::math::saturate( double val )
  noexcept
{
  return clamp( val, 1.0, 0.0 );
}


inline constexpr long double bit::math::saturate( long double val )
  noexcept
{
  return clamp( val, 1.0l, 0.0l );
}

//----------------------------------------------------------------------------
// Equality
//----------------------------------------------------------------------------

template<typename T, typename U, typename V>
inline constexpr bool bit::math::almost_equal( T lhs, U rhs, V tolerance )
  noexcept
{
  return abs(lhs - rhs) <= tolerance;
}



#endif /* BIT_MATH_MATH_HPP */
