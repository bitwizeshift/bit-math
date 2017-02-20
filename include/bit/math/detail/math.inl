#ifndef BIT_MATH_DETAIL_MATH_INL
#define BIT_MATH_DETAIL_MATH_INL

#ifndef BIT_MATH_MATH_HPP
# error "math.inl included without first including declaration header math.hpp"
#endif

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
// Products
//----------------------------------------------------------------------------

template<typename T, typename U, std::size_t N>
inline constexpr std::common_type_t<T,U>
  bit::math::dot( T(&lhs)[N], U(&rhs)[N] )
  noexcept
{
  // Hopefully compilers are smart enough to vectorize the following loop
  auto result = std::common_type_t<T,U>(0);
  for( auto i = 0; i < N; ++i ) {
    result += (lhs[i] * rhs[i]);
  }
  return result;
}

//----------------------------------------------------------------------------
// Rounding
//----------------------------------------------------------------------------

template<typename Arithmetic>
inline Arithmetic bit::math::round( Arithmetic a )
  noexcept
{
  return std::round( a );
}

//----------------------------------------------------------------------------

template<typename Arithmetic>
inline Arithmetic bit::math::ceil( Arithmetic a )
  noexcept
{
  return std::ceil( a );
}

//----------------------------------------------------------------------------

template<typename Arithmetic>
inline Arithmetic bit::math::floor( Arithmetic a )
  noexcept
{
  return std::floor( a );
}

//----------------------------------------------------------------------------

template<typename Arithmetic>
inline Arithmetic bit::math::trunc( Arithmetic a )
  noexcept
{
  return std::trunc( a );
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline std::common_type_t<T,U> bit::math::mod( T num, U den )
  noexcept
{
  return std::fmod<std::common_type_t<T,U>>(num,den);
}

//----------------------------------------------------------------------------
// Squares
//----------------------------------------------------------------------------

template<typename Arithmetic>
inline constexpr Arithmetic bit::math::sqr( Arithmetic a )
  noexcept
{
  return (a*a);
}

//----------------------------------------------------------------------------

template<typename Arithmetic>
inline bit::math::math_result_t<Arithmetic> bit::math::sqrt( Arithmetic a )
  noexcept
{
  return std::sqrt(a);
}

//----------------------------------------------------------------------------
// Cubes
//----------------------------------------------------------------------------

template<typename Arithmetic>
constexpr bit::math::math_result_t<Arithmetic> bit::math::cube( Arithmetic a )
  noexcept
{
  return(a*a*a);
}


//----------------------------------------------------------------------------
// Logarithms
//----------------------------------------------------------------------------

template<typename Arithmetic>
inline bit::math::math_result_t<Arithmetic> bit::math::log( Arithmetic a )
  noexcept
{
  return std::log( a );
}

//----------------------------------------------------------------------------

template<typename Arithmetic>
inline bit::math::math_result_t<Arithmetic> bit::math::log2( Arithmetic a )
  noexcept
{
  return std::log2( a );
}

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
inline constexpr std::common_type_t<T,U,V>
  bit::math::clamp( T val, U max, V min )
  noexcept
{
  return ((val < min) ? min : ((val > max) ? max : val));
}

//----------------------------------------------------------------------------

template<typename Float>
inline constexpr Float bit::math::saturate( Float val )
  noexcept
{
  return clamp( val, static_cast<Float>(1), static_cast<Float>(0) );
}

//============================================================================
// Floating Point Math
//============================================================================

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

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::math::almost_equal( T lhs, U rhs )
  noexcept
{
  return almost_equal(lhs,rhs,default_tolerance);
}

//----------------------------------------------------------------------------
// Finite
//----------------------------------------------------------------------------

template<typename Float>
inline bool bit::math::is_nan( Float f )
  noexcept
{
  return std::isnan( f );
}

//----------------------------------------------------------------------------

template<typename Float>
inline bool bit::math::is_finite( Float f )
  noexcept
{
  return std::isfinite(f);
}


template<typename Float>
inline bool bit::math::is_infinite( Float f )
  noexcept
{
  return std::isinf( f );
}

//----------------------------------------------------------------------------

template<typename Float>
inline bool bit::math::is_normal( Float f )
  noexcept
{
  return std::isnormal( f );
}

template<typename Float>
inline bool bit::math::is_subnormal( Float f )
  noexcept
{
  return std::fpclassify(f) == FP_SUBNORMAL;
}

#endif /* BIT_MATH_DETAIL_MATH_INL */
