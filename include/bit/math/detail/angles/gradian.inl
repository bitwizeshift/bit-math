#ifndef BIT_MATH_DETAIL_ANGLES_GRADIAN_INL
#define BIT_MATH_DETAIL_ANGLES_GRADIAN_INL

#ifndef BIT_MATH_DETAIL_ANGLES_GRADIAN_HPP
# error "gradian.inl included without first including declaration header gradian.hpp"
#endif

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline constexpr bit::math::gradian::gradian()
  noexcept
  : m_angle(0)
{

}

inline constexpr bit::math::gradian::gradian( value_type angle )
  noexcept
  : m_angle(angle)
{

}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

inline constexpr bit::math::gradian::value_type
  bit::math::gradian::value()
  const noexcept
{
  return m_angle;
}

inline constexpr bit::math::gradian::value_type
  bit::math::gradian::revolutions()
  const noexcept
{
  return m_angle / value_type{400};
}

inline bit::math::gradian
  bit::math::gradian::constrained()
  const noexcept
{
  auto angle = mod(m_angle, value_type{400});

  if(angle < 0) angle += value_type{400};

  return gradian{ angle };
}

//----------------------------------------------------------------------------
// Mutators
//----------------------------------------------------------------------------

inline void bit::math::gradian::swap( gradian& other )
  noexcept
{
  using std::swap;

  swap(m_angle,other.m_angle);
}

//----------------------------------------------------------------------------
// Unary Operators
//----------------------------------------------------------------------------

constexpr bit::math::gradian bit::math::gradian::operator+()
  const noexcept
{
  return (*this);
}

constexpr bit::math::gradian bit::math::gradian::operator-()
  const noexcept
{
  return gradian(-m_angle);
}

//----------------------------------------------------------------------------
// Compound Assignment
//----------------------------------------------------------------------------

inline bit::math::gradian& bit::math::gradian::operator+=( const gradian& rhs )
  noexcept
{
  m_angle += rhs.m_angle;
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::gradian& bit::math::gradian::operator-=( const gradian& rhs )
  noexcept
{
  m_angle -= rhs.m_angle;
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::gradian& bit::math::gradian::operator*=( value_type rhs )
  noexcept
{
  m_angle *= rhs;
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::gradian& bit::math::gradian::operator/=( value_type rhs )
  noexcept
{
  m_angle /= rhs;
  return (*this);
}

//----------------------------------------------------------------------------
// Inline Operators
//----------------------------------------------------------------------------

inline constexpr bit::math::gradian
  bit::math::operator+( const gradian& lhs, const gradian& rhs )
  noexcept
{
  return gradian( lhs.value() + rhs.value() );
}

//----------------------------------------------------------------------------

inline constexpr bit::math::gradian
  bit::math::operator-( const gradian& lhs, const gradian& rhs )
  noexcept
{
  return gradian( lhs.value() - rhs.value() );
}

//----------------------------------------------------------------------------

inline constexpr bit::math::gradian
  bit::math::operator*( const gradian& lhs, gradian::value_type rhs )
  noexcept
{
  return gradian( lhs.value() * rhs );
}

inline constexpr bit::math::gradian
  bit::math::operator*( gradian::value_type lhs, const gradian& rhs )
  noexcept
{
  return gradian( rhs.value() * lhs );
}

//----------------------------------------------------------------------------

inline constexpr bit::math::gradian
  bit::math::operator/( const gradian& lhs, gradian::value_type rhs )
  noexcept
{
  return gradian( lhs.value() / rhs );
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

inline void bit::math::swap( gradian& lhs, gradian& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//------------------------------------------------------------------------
// Comparisons
//------------------------------------------------------------------------

inline constexpr bool bit::math::operator == ( const gradian& lhs,
                                               const gradian& rhs )
  noexcept
{
  return lhs.value() == rhs.value();
}

inline constexpr bool bit::math::operator != ( const gradian& lhs,
                                               const gradian& rhs )
  noexcept
{
  return !(lhs==rhs);
}

inline constexpr bool bit::math::operator < ( const gradian& lhs,
                                              const gradian& rhs )
  noexcept
{
  return lhs.value() < rhs.value();
}

inline constexpr bool bit::math::operator > ( const gradian& lhs,
                                              const gradian& rhs )
  noexcept
{
  return lhs.value() > rhs.value();
}

inline constexpr bool bit::math::operator <= ( const gradian& lhs,
                                               const gradian& rhs )
  noexcept
{
  return lhs.value() <= rhs.value();
}

inline constexpr bool bit::math::operator >= ( const gradian& lhs,
                                               const gradian& rhs )
  noexcept
{
  return lhs.value() >= rhs.value();
}

//----------------------------------------------------------------------------

inline constexpr bool bit::math::almost_equal( const gradian& lhs,
                                               const gradian& rhs )
  noexcept
{
  return almost_equal(lhs.value(),rhs.value());
}

template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>*>
inline constexpr bool bit::math::almost_equal( const gradian& lhs,
                                               const gradian& rhs,
                                               Arithmetic tolerance )
  noexcept
{
  return almost_equal(lhs,rhs,tolerance);
}

#endif /* BIT_MATH_DETAIL_ANGLES_GRADIAN_INL */
