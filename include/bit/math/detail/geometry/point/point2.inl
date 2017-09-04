#ifndef BIT_MATH_DETAIL_POINT_POINT2_INL
#define BIT_MATH_DETAIL_POINT_POINT2_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline constexpr bit::math::point2::point2()
  noexcept
  : m_data{0,0}
{

}

inline constexpr bit::math::point2::point2( value_type x, value_type y )
  noexcept
  : m_data{x,y}
{

}


//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

template<typename T>
bit::math::point2& bit::math::point2::operator+=( const vector2<T>& rhs )
  noexcept
{
  for( auto i=0; i<2; ++i ) {
    m_data[i] += rhs[i];
  }
  return (*this);
}


template<typename T>
bit::math::point2& bit::math::point2::operator-=( const vector2<T>& rhs )
  noexcept
{
  for( auto i=0; i<2; ++i ) {
    m_data[i] -= rhs[i];
  }
  return (*this);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

inline constexpr bit::math::point2::reference bit::math::point2::x()
  noexcept
{
  return m_data[0];
}

inline constexpr bit::math::point2::const_reference bit::math::point2::x()
  const noexcept
{
  return m_data[0];
}

//----------------------------------------------------------------------------

inline constexpr bit::math::point2::reference bit::math::point2::y()
  noexcept
{
  return m_data[1];
}

inline constexpr bit::math::point2::const_reference bit::math::point2::y()
  const noexcept
{
  return m_data[1];
}

//----------------------------------------------------------------------------

inline constexpr bit::math::point2::pointer bit::math::point2::data()
  noexcept
{
  return m_data;
}

inline constexpr bit::math::point2::const_pointer bit::math::point2::data()
  const noexcept
{
  return m_data;
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

inline void bit::math::point2::swap( point2& other )
  noexcept
{
  using std::swap;

  swap(m_data[0],other.m_data[0]);
  swap(m_data[1],other.m_data[1]);
}

//----------------------------------------------------------------------------
// Free Operators
//----------------------------------------------------------------------------

inline bit::math::vector2<float_t>
  bit::math::operator - ( const point2& lhs, const point2& rhs )
  noexcept
{
  return { lhs.x() - rhs.x(), lhs.y() - rhs.y() };
}

template<typename T>
inline bit::math::point2
  bit::math::operator + ( const point2& lhs, const vector2<T>& rhs )
  noexcept
{
  return point2(lhs)+=rhs;
}

template<typename T>
inline bit::math::point2
  bit::math::operator - ( const point2& lhs, const vector2<T>& rhs )
  noexcept
{
  return point2(lhs)-=rhs;
}

//------------------------------------------------------------------------
// Free Functions
//------------------------------------------------------------------------

inline constexpr void  bit::math::swap( point2& lhs, point2& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//------------------------------------------------------------------------
// Comparisons
//------------------------------------------------------------------------

inline constexpr bool bit::math::operator==( const point2& lhs,
                                             const point2& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y()) == std::tie(rhs.x(),rhs.y());
}

inline constexpr bool bit::math::operator!=( const point2& lhs,
                                             const point2& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y()) != std::tie(rhs.x(),rhs.y());
}

inline constexpr bool bit::math::operator<=( const point2& lhs,
                                             const point2& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y()) <= std::tie(rhs.x(),rhs.y());
}

inline constexpr bool bit::math::operator>=( const point2& lhs,
                                             const point2& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y()) >= std::tie(rhs.x(),rhs.y());
}

inline constexpr bool bit::math::operator<( const point2& lhs,
                                            const point2& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y()) < std::tie(rhs.x(),rhs.y());
}

inline constexpr bool bit::math::operator>( const point2& lhs,
                                             const point2& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y()) > std::tie(rhs.x(),rhs.y());
}

//----------------------------------------------------------------------------

inline constexpr bool bit::math::almost_equal( const point2& lhs,
                                               const point2& rhs )
  noexcept
{
  return almost_equal( lhs.x(), rhs.x() ) &&
         almost_equal( lhs.y(), rhs.y() );
}

template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>*>
inline constexpr bool bit::math::almost_equal( const point2& lhs,
                                               const point2& rhs,
                                               Arithmetic tolerance )
  noexcept
{
  return almost_equal( lhs.x(), rhs.x(), tolerance ) &&
         almost_equal( lhs.y(), rhs.y(), tolerance );
}

#endif /* BIT_MATH_DETAIL_POINT_POINT2_INL */
