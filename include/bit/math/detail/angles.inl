#ifndef BIT_MATH_DETAIL_ANGLES_INL
#define BIT_MATH_DETAIL_ANGLES_INL

//----------------------------------------------------------------------------
// Literals
//----------------------------------------------------------------------------

inline constexpr bit::math::radian
  bit::math::literals::operator""_rad( long double angle )
  noexcept
{
  return radian(angle);
}

//----------------------------------------------------------------------------

inline constexpr bit::math::degree
  bit::math::literals::operator""_deg( long double angle )
  noexcept
{
  return degree(angle);
}

//----------------------------------------------------------------------------
// Angle casting
//----------------------------------------------------------------------------

template<>
inline constexpr bit::math::radian bit::math::casts::angle_cast( radian from )
  noexcept
{
  return from;
}

template<>
inline constexpr bit::math::degree bit::math::casts::angle_cast( degree from )
  noexcept
{
  return from;
}

namespace bit {
  namespace math {
    namespace detail {
      constexpr auto deg_to_rad = pi<float_t>() / float_t{180};
      constexpr auto rad_to_deg = float_t{180} / pi<float_t>();
    }
  }
}

template<>
inline constexpr bit::math::radian bit::math::casts::angle_cast( degree angle )
  noexcept
{

  return radian{ angle.value() * detail::deg_to_rad };
}

template<>
inline constexpr bit::math::degree bit::math::casts::angle_cast( radian angle )
  noexcept
{
  return degree{ angle.value() * detail::rad_to_deg };
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

inline bit::math::radian bit::math::round( radian angle )
  noexcept
{
  return radian{ round(angle.value()) };
}

inline bit::math::degree bit::math::round( degree angle )
  noexcept
{
  return degree{ round(angle.value()) };
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::trunc( radian angle )
  noexcept
{
  return radian( trunc(angle.value()) );
}

inline bit::math::degree bit::math::trunc( degree angle )
  noexcept
{
  return degree( trunc(angle.value()) );
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::ceil( radian angle )
  noexcept
{
  return radian( ceil(angle.value()) );
}

inline bit::math::degree bit::math::ceil( degree angle )
  noexcept
{
  return degree( ceil(angle.value()) );
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::floor( radian angle )
  noexcept
{
  return radian( floor(angle.value()) );
}

inline bit::math::degree bit::math::floor( degree angle )
  noexcept
{
  return degree( floor(angle.value()) );
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::abs( radian angle )
  noexcept
{
  return radian( abs(angle.value()) );
}

inline bit::math::degree bit::math::abs( degree angle )
  noexcept
{
  return degree( abs(angle.value()) );
}

//----------------------------------------------------------------------------
// Trig
//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::cos( radian rad )
  noexcept
{
  return std::cos( rad.value() );
}

inline bit::math::float_t bit::math::cos( degree deg )
  noexcept
{
  return cos( angle_cast<radian>(deg) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::sin( radian rad )
  noexcept
{
  return std::sin( rad.value() );
}

inline bit::math::float_t bit::math::sin( degree deg )
  noexcept
{
  return sin( angle_cast<radian>(deg) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::tan( radian rad )
  noexcept
{
  return std::tan( rad.value() );
}

inline bit::math::float_t bit::math::tan( degree deg )
  noexcept
{
  return tan( angle_cast<radian>(deg) );
}

//----------------------------------------------------------------------------
// Inverse Trig
//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::sec( radian rad )
  noexcept
{
  return (1.0) / cos(rad);
}

inline bit::math::float_t bit::math::sec( degree deg )
  noexcept
{
  return (1.0) / cos(deg);
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::csc( radian rad )
  noexcept
{
  return (1.0) / sin(rad);
}

inline bit::math::float_t bit::math::csc( degree deg )
  noexcept
{
  return (1.0) / sin(deg);
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::cot( radian rad )
  noexcept
{
  return (1.0) / tan(rad);
}

inline bit::math::float_t bit::math::cot( degree deg )
  noexcept
{
  return (1.0) / tan(deg);
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::arccos( float_t f )
  noexcept
{
  return radian{ std::acos(f) };
}

inline bit::math::radian bit::math::arcsin( float_t f )
  noexcept
{
  return radian{ std::asin(f) };
}

inline bit::math::radian bit::math::arctan( float_t f )
  noexcept
{
  return radian{ std::atan(f) };
}

inline bit::math::radian bit::math::arctan2( float_t f1, float_t f2 )
  noexcept
{
  return radian{ std::atan2(f1,f2) };
}

//----------------------------------------------------------------------------
// Table Trig
//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::tsin( radian rad )
  noexcept
{
  return detail::sin_lookup( rad.value() );
}

inline bit::math::float_t bit::math::tsin( degree deg )
  noexcept
{
  return tsin( angle_cast<radian>(deg) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::tcos( radian rad )
  noexcept
{
  return detail::sin_lookup( rad.value() - half_pi<float_t>() );
}

inline bit::math::float_t bit::math::tcos( degree deg )
  noexcept
{
  return tcos( angle_cast<radian>(deg) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::ttan( radian rad )
  noexcept
{
  return detail::tan_lookup( rad.value() );
}

inline bit::math::float_t bit::math::ttan( degree deg )
  noexcept
{
  return ttan( angle_cast<radian>(deg) );
}

//------------------------------------------------------------------------
// Inverse Table Trig
//------------------------------------------------------------------------

inline bit::math::float_t bit::math::tsec( radian rad )
  noexcept
{
  return (1.0) / tcos(rad);
}

inline bit::math::float_t bit::math::tsec( degree deg )
  noexcept
{
  return (1.0) / tcos(deg);
}

//------------------------------------------------------------------------

inline bit::math::float_t bit::math::tcsc( radian rad )
  noexcept
{
  return (1.0) / tsin(rad);
}

inline bit::math::float_t bit::math::tcsc( degree deg )
  noexcept
{
  return (1.0) / tsin(deg);
}

//------------------------------------------------------------------------

inline bit::math::float_t bit::math::tcot( radian rad )
  noexcept
{
  return (1.0) / ttan(rad);
}

inline bit::math::float_t bit::math::tcot( degree deg )
  noexcept
{
  return (1.0) / ttan(deg);
}

#endif /* BIT_MATH_DETAIL_ANGLES_INL */
