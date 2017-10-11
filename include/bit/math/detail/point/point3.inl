#ifndef BIT_MATH_DETAIL_GEOMETRY_POINT_POINT3_INL
#define BIT_MATH_DETAIL_GEOMETRY_POINT_POINT3_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline constexpr bit::math::point3::point3()
  noexcept
  : m_data{0,0}
{

}

inline constexpr bit::math::point3::point3( value_type x, value_type y, value_type z )
  noexcept
  : m_data{x,y,z}
{

}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

template<typename T>
bit::math::point3& bit::math::point3::operator+=( const vector3<T>& rhs )
  noexcept
{
  for( auto i=0; i<3; ++i ) {
    m_data[i] += rhs[i];
  }
  return (*this);
}


template<typename T>
bit::math::point3& bit::math::point3::operator-=( const vector3<T>& rhs )
  noexcept
{
  for( auto i=0; i<3; ++i ) {
    m_data[i] += rhs[i];
  }
  return (*this);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

inline constexpr bit::math::point3::reference bit::math::point3::x()
  noexcept
{
  return m_data[0];
}

inline constexpr bit::math::point3::const_reference bit::math::point3::x()
  const noexcept
{
  return m_data[0];
}

//----------------------------------------------------------------------------

inline constexpr bit::math::point3::reference bit::math::point3::y()
  noexcept
{
  return m_data[1];
}

inline constexpr bit::math::point3::const_reference bit::math::point3::y()
  const noexcept
{
  return m_data[1];
}

//----------------------------------------------------------------------------

inline constexpr bit::math::point3::reference bit::math::point3::z()
  noexcept
{
  return m_data[2];
}

inline constexpr bit::math::point3::const_reference bit::math::point3::z()
  const noexcept
{
  return m_data[2];
}

//----------------------------------------------------------------------------

inline constexpr bit::math::point3::pointer bit::math::point3::data()
  noexcept
{
  return m_data;
}

inline constexpr bit::math::point3::const_pointer bit::math::point3::data()
  const noexcept
{
  return m_data;
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

inline void bit::math::point3::swap( point3& other )
  noexcept
{
  using std::swap;

  swap(m_data[0],other.m_data[0]);
  swap(m_data[1],other.m_data[1]);
  swap(m_data[2],other.m_data[2]);
}


inline constexpr bit::math::float_t bit::math::dot( const point3& lhs,
                                                    const point3& rhs )
  noexcept
{
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

inline constexpr bit::math::float_t bit::math::dot( const vec3& lhs,
                                                    const point3& rhs )
  noexcept
{
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

inline constexpr bit::math::float_t bit::math::dot( const point3& lhs,
                                                    const vec3& rhs )
  noexcept
{
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

//----------------------------------------------------------------------------
// Free Operators
//----------------------------------------------------------------------------

inline bit::math::vector3<float_t>
  bit::math::operator - ( const point3& lhs, const point3& rhs )
  noexcept
{
  return { lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z() };
}

template<typename T>
inline bit::math::point3
  bit::math::operator + ( const point3& lhs, const vector3<T>& rhs )
  noexcept
{
  return point3(lhs)+=rhs;
}

template<typename T>
inline bit::math::point3
  bit::math::operator - ( const point3& lhs, const vector3<T>& rhs )
  noexcept
{
  return point3(lhs)-=rhs;
}

//------------------------------------------------------------------------
// Free Functions
//------------------------------------------------------------------------

inline constexpr void  bit::math::swap( point3& lhs, point3& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//------------------------------------------------------------------------
// Comparisons
//------------------------------------------------------------------------

inline constexpr bool bit::math::operator==( const point3& lhs,
                                             const point3& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y(),lhs.z()) == std::tie(rhs.x(),rhs.y(),rhs.z());
}

inline constexpr bool bit::math::operator!=( const point3& lhs,
                                             const point3& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y(),lhs.z()) != std::tie(rhs.x(),rhs.y(),rhs.z());
}

inline constexpr bool bit::math::operator<=( const point3& lhs,
                                             const point3& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y(),lhs.z()) <= std::tie(rhs.x(),rhs.y(),rhs.z());
}

inline constexpr bool bit::math::operator>=( const point3& lhs,
                                             const point3& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y(),lhs.z()) >= std::tie(rhs.x(),rhs.y(),rhs.z());
}

inline constexpr bool bit::math::operator<( const point3& lhs,
                                            const point3& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y(),lhs.z()) < std::tie(rhs.x(),rhs.y(),rhs.z());
}

inline constexpr bool bit::math::operator>( const point3& lhs,
                                             const point3& rhs )
  noexcept
{
  return std::tie(lhs.x(),lhs.y(),lhs.z()) > std::tie(rhs.x(),rhs.y(),rhs.z());
}

//----------------------------------------------------------------------------

inline constexpr bool bit::math::almost_equal( const point3& lhs,
                                               const point3& rhs )
  noexcept
{
  return almost_equal( lhs.x(), rhs.x() ) &&
         almost_equal( lhs.y(), rhs.y() ) &&
         almost_equal( lhs.z(), rhs.z() );
}

template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>*>
inline constexpr bool bit::math::almost_equal( const point3& lhs,
                                               const point3& rhs,
                                               Arithmetic tolerance )
  noexcept
{
  return almost_equal( lhs.x(), rhs.x(), tolerance ) &&
         almost_equal( lhs.y(), rhs.y(), tolerance ) &&
         almost_equal( lhs.z(), rhs.z(), tolerance );
}

#endif /* BIT_MATH_DETAIL_GEOMETRY_POINT_POINT3_INL */
