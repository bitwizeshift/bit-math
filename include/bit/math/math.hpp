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
    std::common_type_t<T,U>
      mod( T num, U den ) noexcept;

    namespace detail {

      template<typename T>
      struct mod_dispatch;

    } // namespace detail

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
    constexpr float saturate( Float val ) noexcept;

    //------------------------------------------------------------------------
    // Trig Functions
    //------------------------------------------------------------------------

    //------------------------------------------------------------------------
    // Table Trig Functions
    //------------------------------------------------------------------------

    //------------------------------------------------------------------------
    // Equality
    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr bool almost_equal( T lhs, U rhs ) noexcept;

    template<typename T, typename U, typename V>
    constexpr bool almost_equal( T lhs, U rhs, V tolerance ) noexcept;

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
// Square-root
//----------------------------------------------------------------------------

template<typename T, typename U>
inline std::common_type_t<T,U> bit::math::mod( T num, U den )
  noexcept
{
  return std::fmod<std::common_type_t<T,U>>(num,den);
}

inline float bit::math::sqrt( float f )
  noexcept
{
  return std::sqrt(f);
}

//----------------------------------------------------------------------------

inline double bit::math::sqrt( double f )
  noexcept
{
  return std::sqrt(f);
}

//----------------------------------------------------------------------------

inline long double bit::math::sqrt( long double f )
  noexcept
{
  return std::sqrt(f);
}

//----------------------------------------------------------------------------
// Logarithms
//----------------------------------------------------------------------------

inline float bit::math::log2( float f )
  noexcept;

//----------------------------------------------------------------------------

inline double bit::math::log2( double f )
  noexcept;

//----------------------------------------------------------------------------

inline long double bit::math::log2( long double f )
  noexcept;

//----------------------------------------------------------------------------
// Absolute Values
//----------------------------------------------------------------------------

template<typename Arithmetic,std::enable_if_t<std::is_signed<Arithmetic>::value>*>
inline constexpr Arithmetic bit::math::abs( Arithmetic x )
  noexcept
{
  return ((x < 0) ? -x : x);
}

template<typename Arithmetic,std::enable_if_t<std::is_unsigned<Arithmetic>::value>*>
inline constexpr Arithmetic bit::math::abs( Arithmetic x )
  noexcept
{
  return x;
}

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

template<typename Float>
inline constexpr float bit::math::saturate( Float val )
  noexcept
{
  return clamp( val, static_cast<Float>(1), static_cast<Float>(0) );
}

//----------------------------------------------------------------------------
// Equality
//----------------------------------------------------------------------------

template<typename T, typename U, typename V>
inline constexpr bool bit::math::almost_equal( T lhs, U rhs, V tolerance )
  noexcept
{
  auto tmp = (lhs - rhs);
  return (((tmp < 0) ? -tmp : tmp) <= tolerance);
}

template<typename T, typename U>
inline constexpr bool bit::math::almost_equal( T lhs, U rhs )
  noexcept
{
  return almost_equal(lhs,rhs,default_tolerance);
}



#endif /* BIT_MATH_MATH_HPP */
