#ifndef BIT_MATH_DETAIL_ANGLES_INL
#define BIT_MATH_DETAIL_ANGLES_INL

#ifndef BIT_MATH_ANGLES_HPP
# error "angles.inl included without first including declaration header angles.hpp"
#endif

//----------------------------------------------------------------------------
// Constant Expressions
//----------------------------------------------------------------------------

namespace bit {
  namespace math {
    namespace detail {
      constexpr auto deg_to_rad  = pi<float_t>() / float_t{180};
      constexpr auto deg_to_grad = float_t{400} / float_t{360};

      constexpr auto rad_to_deg  = float_t{180} / pi<float_t>();
      constexpr auto rad_to_grad = float_t{200} / pi<float_t>();

      constexpr auto grad_to_deg = float_t{360} / float_t{400};
      constexpr auto grad_to_rad = pi<float_t>() / float_t{200};
    } // namespace detail
  } // namespace math
} // namespace bit

//----------------------------------------------------------------------------
// Literals
//----------------------------------------------------------------------------

inline constexpr bit::math::radian
  bit::math::literals::angle_literals::operator""_rad( long double angle )
  noexcept
{
  return radian(angle);
}

//----------------------------------------------------------------------------

inline constexpr bit::math::gradian
  bit::math::literals::angle_literals::operator""_grad( long double angle )
  noexcept
{
  return gradian(angle);
}

//----------------------------------------------------------------------------

inline constexpr bit::math::degree
  bit::math::literals::angle_literals::operator""_deg( long double angle )
  noexcept
{
  return degree(angle);
}

//----------------------------------------------------------------------------
// Angle casting
//----------------------------------------------------------------------------

template<>
inline constexpr bit::math::degree
  bit::math::casts::angle_casts::angle_cast( radian from )
  noexcept
{
  return degree{ from.value() * detail::rad_to_deg };
}

template<>
inline constexpr bit::math::radian
  bit::math::casts::angle_casts::angle_cast( radian from )
  noexcept
{
  return from;
}

template<>
inline constexpr bit::math::gradian
  bit::math::casts::angle_casts::angle_cast( radian from )
  noexcept
{
  return gradian{ from.value() * detail::rad_to_grad };
}

//----------------------------------------------------------------------------

template<>
inline constexpr bit::math::degree
  bit::math::casts::angle_casts::angle_cast( gradian from )
  noexcept
{
  return degree{ from.value() * detail::grad_to_deg };
}

template<>
inline constexpr bit::math::radian
  bit::math::casts::angle_casts::angle_cast( gradian from )
  noexcept
{
  return radian{ from.value() * detail::grad_to_rad };
}

template<>
inline constexpr bit::math::gradian
  bit::math::casts::angle_casts::angle_cast( gradian from )
  noexcept
{
  return from;
}

//----------------------------------------------------------------------------

template<>
inline constexpr bit::math::degree
  bit::math::casts::angle_casts::angle_cast( degree from )
  noexcept
{
  return from;
}

template<>
inline constexpr bit::math::radian
  bit::math::casts::angle_casts::angle_cast( degree from )
  noexcept
{
  return radian{ from.value() * detail::deg_to_rad };
}

template<>
inline constexpr bit::math::gradian
  bit::math::casts::angle_casts::angle_cast( degree from )
  noexcept
{
  return gradian{ from.value() * detail::deg_to_grad };
}

//----------------------------------------------------------------------------
// Rounding
//----------------------------------------------------------------------------

inline bit::math::radian bit::math::round( radian angle )
  noexcept
{
  return radian{ std::round(angle.value()) };
}

inline bit::math::gradian bit::math::round( gradian angle )
  noexcept
{
  return gradian{ std::round(angle.value()) };
}

inline bit::math::degree bit::math::round( degree angle )
  noexcept
{
  return degree{ std::round(angle.value()) };
}


//----------------------------------------------------------------------------

inline bit::math::radian bit::math::ceil( radian angle )
  noexcept
{
  return radian( std::ceil(angle.value()) );
}


inline bit::math::gradian bit::math::ceil( gradian angle )
  noexcept
{
  return gradian( std::ceil(angle.value()) );
}

inline bit::math::degree bit::math::ceil( degree angle )
  noexcept
{
  return degree( std::ceil(angle.value()) );
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::floor( radian angle )
  noexcept
{
  return radian( std::floor(angle.value()) );
}

inline bit::math::gradian bit::math::floor( gradian angle )
  noexcept
{
  return gradian( std::floor(angle.value()) );
}

inline bit::math::degree bit::math::floor( degree angle )
  noexcept
{
  return degree( std::floor(angle.value()) );
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::trunc( radian angle )
  noexcept
{
  return radian( std::trunc(angle.value()) );
}

inline bit::math::gradian bit::math::trunc( gradian angle )
  noexcept
{
  return gradian( std::trunc(angle.value()) );
}
inline bit::math::degree bit::math::trunc( degree angle )
  noexcept
{
  return degree( std::trunc(angle.value()) );
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::mod( radian num, radian den )
  noexcept
{
  return radian( std::fmod(num.value(),den.value() ) );
}

inline bit::math::gradian bit::math::mod( gradian num, gradian den )
  noexcept
{
  return gradian( std::fmod(num.value(),den.value() ) );
}

inline bit::math::degree bit::math::mod( degree num, degree den )
  noexcept
{
  return degree( std::fmod(num.value(),den.value() ) );
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::abs( radian angle )
  noexcept
{
  return radian( std::abs(angle.value()) );
}

inline bit::math::gradian bit::math::abs( gradian angle )
  noexcept
{
  return gradian( std::abs(angle.value()) );
}

inline bit::math::degree bit::math::abs( degree angle )
  noexcept
{
  return degree( std::abs(angle.value()) );
}

//----------------------------------------------------------------------------
// Trig
//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::runtime::cos( radian rad )
  noexcept
{
  return std::cos( rad.value() );
}

inline bit::math::float_t bit::math::runtime::cos( gradian grad )
  noexcept
{
  return runtime::cos( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::runtime::cos( degree deg )
  noexcept
{
  return runtime::cos( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::runtime::cos( float_t rad )
  noexcept
{
  return runtime::cos( radian(rad) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::runtime::sin( radian rad )
  noexcept
{
  return std::sin( rad.value() );
}

inline bit::math::float_t bit::math::runtime::sin( gradian grad )
  noexcept
{
  return runtime::sin( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::runtime::sin( degree deg )
  noexcept
{
  return runtime::sin( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::runtime::sin( float_t rad )
  noexcept
{
  return runtime::sin( radian(rad) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::runtime::tan( radian rad )
  noexcept
{
  return std::tan( rad.value() );
}

inline bit::math::float_t bit::math::runtime::tan( gradian grad )
  noexcept
{
  return runtime::tan( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::runtime::tan( degree deg )
  noexcept
{
  return runtime::tan( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::runtime::tan( float_t rad )
  noexcept
{
  return runtime::tan( radian(rad) );
}

//----------------------------------------------------------------------------
// Inverse Trig
//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::runtime::sec( radian rad )
  noexcept
{
  return (1.0) / runtime::cos(rad);
}

inline bit::math::float_t bit::math::runtime::sec( gradian grad )
  noexcept
{
  return runtime::sec( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::runtime::sec( degree deg )
  noexcept
{
  return runtime::sec( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::runtime::sec( float_t rad )
  noexcept
{
  return runtime::sec( radian(rad) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::runtime::csc( radian rad )
  noexcept
{
  return (1.0) / runtime::sin(rad);
}

inline bit::math::float_t bit::math::runtime::csc( gradian grad )
  noexcept
{
  return runtime::csc( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::runtime::csc( degree deg )
  noexcept
{
  return runtime::csc( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::runtime::csc( float_t rad )
  noexcept
{
  return runtime::csc( radian(rad) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::runtime::cot( radian rad )
  noexcept
{
  return (1.0) / runtime::tan(rad);
}

inline bit::math::float_t bit::math::runtime::cot( gradian grad )
  noexcept
{
  return runtime::cot( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::runtime::cot( degree deg )
  noexcept
{
  return runtime::cot( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::runtime::cot( float_t rad )
  noexcept
{
  return runtime::cot( radian(rad) );
}

//----------------------------------------------------------------------------
// Cached Trigonometry
//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::cached::sin( radian rad )
  noexcept
{
  return detail::sin_lookup( rad.value() );
}

inline bit::math::float_t bit::math::cached::sin( gradian grad )
  noexcept
{
  return cached::sin( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::cached::sin( degree deg )
  noexcept
{
  return cached::sin( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::cached::sin( float_t rad )
  noexcept
{
  return cached::sin( radian(rad) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::cached::cos( radian rad )
  noexcept
{
  return detail::sin_lookup( rad.value() - half_pi<float_t>() );
}

inline bit::math::float_t bit::math::cached::cos( gradian grad )
  noexcept
{
  return cached::cos( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::cached::cos( degree deg )
  noexcept
{
  return cached::cos( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::cached::cos( float_t rad )
  noexcept
{
  return cached::cos( radian(rad) );
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::cached::tan( radian rad )
  noexcept
{
  return (cached::sin( rad ) / cached::cos( rad ));
}

inline bit::math::float_t bit::math::cached::tan( gradian grad )
  noexcept
{
  return cached::tan( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::cached::tan( degree deg )
  noexcept
{
  return cached::tan( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::cached::tan( float_t rad )
  noexcept
{
  return cached::tan( radian(rad) );
}

//------------------------------------------------------------------------

inline bit::math::float_t bit::math::cached::sec( radian rad )
  noexcept
{
  return (1.0) / cached::cos(rad);
}

inline bit::math::float_t bit::math::cached::sec( gradian grad )
  noexcept
{
  return cached::sec( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::cached::sec( degree deg )
  noexcept
{
  return cached::sec( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::cached::sec( float_t rad )
  noexcept
{
  return cached::sec( radian(rad) );
}

//------------------------------------------------------------------------

inline bit::math::float_t bit::math::cached::csc( radian rad )
  noexcept
{
  return (1.0) / cached::sin(rad);
}

inline bit::math::float_t bit::math::cached::csc( gradian grad )
  noexcept
{
  return cached::csc( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::cached::csc( degree deg )
  noexcept
{
  return cached::csc( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::cached::csc( float_t rad )
  noexcept
{
  return cached::csc( radian(rad) );
}

//------------------------------------------------------------------------

inline bit::math::float_t bit::math::cached::cot( radian rad )
  noexcept
{
  return (1.0) / cached::tan(rad);
}

inline bit::math::float_t bit::math::cached::cot( gradian grad )
  noexcept
{
  return cached::cot( angle_cast<radian>(grad) );
}

inline bit::math::float_t bit::math::cached::cot( degree deg )
  noexcept
{
  return cached::cot( angle_cast<radian>(deg) );
}

inline bit::math::float_t bit::math::cached::cot( float_t rad )
  noexcept
{
  return cached::cot( radian(rad) );
}

//----------------------------------------------------------------------------
// Inverse Trigonometry
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

#endif /* BIT_MATH_DETAIL_ANGLES_INL */
