#ifndef BIT_MATH_DETAIL_ANGLES_DEGREE_INL
#define BIT_MATH_DETAIL_ANGLES_DEGREE_INL

#ifndef BIT_MATH_DETAIL_ANGLES_DEGREE_INL
# error "degree.inl included without first including declaration header degree.hpp"
#endif


//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline constexpr bit::math::degree::degree()
  noexcept
  : m_angle(0)
{

}

inline constexpr bit::math::degree::degree( value_type angle )
  noexcept
  : m_angle(angle)
{

}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

inline constexpr bit::math::degree::value_type
  bit::math::degree::value()
  const noexcept
{
  return m_angle;
}

inline constexpr bit::math::degree::value_type
  bit::math::degree::revolutions()
  const noexcept
{
  return m_angle / value_type{360};
}

inline bit::math::degree
  bit::math::degree::constrained()
  const noexcept
{
  auto angle = mod(m_angle, value_type{360});

  if(angle < 0) angle += value_type{360};

  return degree{ angle };
}

//----------------------------------------------------------------------------
// Mutators
//----------------------------------------------------------------------------

inline void bit::math::degree::swap( degree& other )
  noexcept
{
  using std::swap;

  swap(m_angle,other.m_angle);
}

//----------------------------------------------------------------------------
// Unary Operators
//----------------------------------------------------------------------------

constexpr bit::math::degree bit::math::degree::operator+()
  const noexcept
{
  return (*this);
}

constexpr bit::math::degree bit::math::degree::operator-()
  const noexcept
{
  return degree(-m_angle);
}

//----------------------------------------------------------------------------
// Compound Assignment
//----------------------------------------------------------------------------

inline bit::math::degree& bit::math::degree::operator+=( const degree& rhs )
  noexcept
{
  m_angle += rhs.m_angle;
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::degree& bit::math::degree::operator-=( const degree& rhs )
  noexcept
{
  m_angle -= rhs.m_angle;
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::degree& bit::math::degree::operator*=( value_type rhs )
  noexcept
{
  m_angle *= rhs;
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::degree& bit::math::degree::operator/=( value_type rhs )
  noexcept
{
  m_angle /= rhs;
  return (*this);
}

//----------------------------------------------------------------------------
// Inline Operators
//----------------------------------------------------------------------------

inline constexpr bit::math::degree
  bit::math::operator+( const degree& lhs, const degree& rhs )
  noexcept
{
  return degree( lhs.value() + rhs.value() );
}

//----------------------------------------------------------------------------

inline constexpr bit::math::degree
  bit::math::operator-( const degree& lhs, const degree& rhs )
  noexcept
{
  return degree( lhs.value() - rhs.value() );
}

//----------------------------------------------------------------------------

inline constexpr bit::math::degree
  bit::math::operator*( const degree& lhs, degree::value_type rhs )
  noexcept
{
  return degree( lhs.value() * rhs );
}

inline constexpr bit::math::degree
  bit::math::operator*( degree::value_type lhs, const degree& rhs )
  noexcept
{
  return degree( rhs.value() * lhs );
}

//----------------------------------------------------------------------------

inline constexpr bit::math::degree
  bit::math::operator/( const degree& lhs, degree::value_type rhs )
  noexcept
{
  return degree( lhs.value() / rhs );
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

inline void bit::math::swap( degree& lhs, degree& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//------------------------------------------------------------------------
// Comparisons
//------------------------------------------------------------------------

inline constexpr bool bit::math::operator == ( const degree& lhs,
                                               const degree& rhs )
  noexcept
{
  return lhs.value() == rhs.value();
}

inline constexpr bool bit::math::operator != ( const degree& lhs,
                                               const degree& rhs )
  noexcept
{
  return !(lhs==rhs);
}

inline constexpr bool bit::math::operator < ( const degree& lhs,
                                              const degree& rhs )
  noexcept
{
  return lhs.value() < rhs.value();
}

inline constexpr bool bit::math::operator > ( const degree& lhs,
                                              const degree& rhs )
  noexcept
{
  return lhs.value() > rhs.value();
}

inline constexpr bool bit::math::operator <= ( const degree& lhs,
                                               const degree& rhs )
  noexcept
{
  return lhs.value() <= rhs.value();
}

inline constexpr bool bit::math::operator >= ( const degree& lhs,
                                               const degree& rhs )
  noexcept
{
  return lhs.value() >= rhs.value();
}

//----------------------------------------------------------------------------

inline constexpr bool bit::math::almost_equal( const degree& lhs,
                                               const degree& rhs )
  noexcept
{
  return almost_equal(lhs.value(),rhs.value());
}

template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>*>
inline constexpr bool bit::math::almost_equal( const degree& lhs,
                                               const degree& rhs,
                                               Arithmetic tolerance )
  noexcept
{
  return almost_equal(lhs,rhs,tolerance);
}

#endif /* BIT_MATH_DETAIL_ANGLES_DEGREE_INL */
