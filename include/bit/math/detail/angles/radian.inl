#ifndef BIT_MATH_DETAIL_ANGLES_RADIAN_INL
#define BIT_MATH_DETAIL_ANGLES_RADIAN_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline constexpr bit::math::radian::radian()
  noexcept
  : m_angle(0)
{

}

inline constexpr bit::math::radian::radian( radian::value_type angle )
  noexcept
  : m_angle(angle)
{

}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

inline constexpr bit::math::radian::value_type bit::math::radian::value()
  const noexcept
{
  return m_angle;
}

inline constexpr bit::math::radian::value_type bit::math::radian::revolutions()
  const noexcept
{
  return m_angle / two_pi<value_type>();
}

inline bit::math::radian bit::math::radian::constrained()
  const noexcept
{
  auto angle = mod(m_angle, two_pi<value_type>());

  if(angle < 0) angle += two_pi<value_type>();

  return radian( value_type(angle) );
}

//----------------------------------------------------------------------------
// Mutators
//----------------------------------------------------------------------------

inline void bit::math::radian::swap( radian& other )
  noexcept
{
  using std::swap;

  swap(m_angle,other.m_angle);
}

//----------------------------------------------------------------------------
// Compound Assignment
//----------------------------------------------------------------------------

inline bit::math::radian& bit::math::radian::operator+=( const radian& rhs )
  noexcept
{
  m_angle += rhs.m_angle;
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::radian& bit::math::radian::operator-=( const radian& rhs )
  noexcept
{
  m_angle -= rhs.m_angle;
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::radian& bit::math::radian::operator*=( value_type rhs )
  noexcept
{
  m_angle *= rhs;
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::radian& bit::math::radian::operator/=( value_type rhs )
  noexcept
{
  m_angle /= rhs;
  return (*this);
}

//----------------------------------------------------------------------------
// Inline Operators
//----------------------------------------------------------------------------

inline constexpr bit::math::radian
  bit::math::operator+( const radian& lhs, const radian& rhs )
  noexcept
{
  return radian( lhs.value() + rhs.value() );
}

//----------------------------------------------------------------------------

inline constexpr bit::math::radian
  bit::math::operator-( const radian& lhs, const radian& rhs )
  noexcept
{
  return radian( lhs.value() - rhs.value() );
}

//----------------------------------------------------------------------------

inline constexpr bit::math::radian
  bit::math::operator*( const radian& lhs, radian::value_type rhs )
  noexcept
{
  return radian( lhs.value() * rhs );
}

//----------------------------------------------------------------------------

inline constexpr bit::math::radian
  bit::math::operator/( const radian& lhs, radian::value_type rhs )
  noexcept
{
  return radian( lhs.value() / rhs );
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

inline void bit::math::swap( radian& lhs, radian& rhs )
  noexcept
{
  lhs.swap(rhs);
}

#endif /* BIT_MATH_DETAIL_ANGLES_RADIAN_INL */
