#ifndef BIT_MATH_DETAIL_QUATERNION_INL
#define BIT_MATH_DETAIL_QUATERNION_INL

#ifndef BIT_MATH_QUATERNION_HPP
# error "quaternion.inl included without first including declaration header quaternion.hpp"
#endif

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline bit::math::quaternion::quaternion()
  noexcept
  : m_data{1,0,0,0}
{

}

//----------------------------------------------------------------------------

inline bit::math::quaternion::quaternion( radian angle,
                                          const vector_type& axis )
  noexcept
{
  from_angle_axis(angle,axis);
}

//----------------------------------------------------------------------------

inline bit::math::quaternion::quaternion( value_type x )
  noexcept
  : m_data{x,0,0,0}
{

}

inline bit::math::quaternion::quaternion( value_type x,
                                          value_type y,
                                          value_type z,
                                          value_type w )
  noexcept
  : m_data{x,y,z,w}
{

}

//----------------------------------------------------------------------------

inline bit::math::quaternion::quaternion( const vector_type& x_axis,
                                          const vector_type& y_axis,
                                          const vector_type& z_axis )
  noexcept
{
  from_rotation_matrix( matrix3_type{x_axis,y_axis,z_axis} );
}

inline bit::math::quaternion::quaternion( const matrix3_type& rot )
  noexcept
{
  from_rotation_matrix( rot );
}

inline bit::math::quaternion::quaternion( const matrix4_type& rot )
  noexcept
{
  from_rotation_matrix( rot );
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

inline bit::math::quaternion::size_type bit::math::quaternion::size()
  const noexcept
{
  return 4;
}

//----------------------------------------------------------------------------

inline bit::math::quaternion::reference bit::math::quaternion::w()
  noexcept
{
  return m_data[0];
}

inline bit::math::quaternion::const_reference bit::math::quaternion::w()
  const noexcept
{
  return m_data[0];
}

//----------------------------------------------------------------------------

inline bit::math::quaternion::reference bit::math::quaternion::x()
  noexcept
{
  return m_data[1];
}

inline bit::math::quaternion::const_reference bit::math::quaternion::x()
  const noexcept
{
  return m_data[1];
}

//----------------------------------------------------------------------------

inline bit::math::quaternion::reference bit::math::quaternion::y()
  noexcept
{
  return m_data[2];
}

inline bit::math::quaternion::const_reference bit::math::quaternion::y()
  const noexcept
{
  return m_data[2];
}

//----------------------------------------------------------------------------

inline bit::math::quaternion::reference bit::math::quaternion::z()
  noexcept
{
  return m_data[3];
}

inline bit::math::quaternion::const_reference bit::math::quaternion::z()
  const noexcept
{
  return m_data[3];
}

//----------------------------------------------------------------------------

inline bit::math::quaternion::pointer bit::math::quaternion::data()
  noexcept
{
  return m_data;
}

inline bit::math::quaternion::const_pointer bit::math::quaternion::data()
  const noexcept
{
  return m_data;
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

inline bit::math::quaternion::reference
  bit::math::quaternion::operator[]( index_type i )
  noexcept
{
  return m_data[i];
}

inline bit::math::quaternion::const_reference
  bit::math::quaternion::operator[]( index_type i )
  const noexcept
{
  return m_data[i];
}

//----------------------------------------------------------------------------

inline bit::math::quaternion::matrix3_type
  bit::math::quaternion::rotation_matrix()
  const noexcept
{
  auto mat = matrix3_type();
  extract_rotation_matrix(&mat);

  return mat;
}

inline std::tuple<bit::math::radian,bit::math::quaternion::vector_type>
  bit::math::quaternion::angle_axis()
  const noexcept
{
  auto rad = radian();
  auto vec = vector_type();

  extract_angle_axis(&rad,&vec);
  return std::make_pair(rad,vec);
}

inline std::tuple<bit::math::quaternion::vector_type,
                  bit::math::quaternion::vector_type,
                  bit::math::quaternion::vector_type>
  bit::math::quaternion::axes()
  const noexcept
{
  return std::make_tuple( x_axis(), y_axis(), z_axis() );
}

//----------------------------------------------------------------------------

inline bit::math::quaternion bit::math::quaternion::normalized()
  const noexcept
{
  return quaternion(*this).normalize();
}

inline bit::math::quaternion bit::math::quaternion::inverse()
  const noexcept
{
  return quaternion(*this).invert();
}

//----------------------------------------------------------------------------
// Unary Operators
//----------------------------------------------------------------------------

inline bit::math::quaternion bit::math::quaternion::operator+()
  const noexcept
{
  return (*this);
}

//----------------------------------------------------------------------------

inline bit::math::quaternion bit::math::quaternion::operator-()
  const noexcept
{
  return quaternion( -w(), -x(), -y(), -z() );
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

inline void bit::math::swap( quaternion& lhs, quaternion& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------

inline bit::math::quaternion::value_type
  bit::math::dot( const quaternion& lhs, const quaternion& rhs )
  noexcept
{
  return lhs.dot(rhs);
}

inline bit::math::quaternion::value_type
  bit::math::magnitude( const quaternion& x )
  noexcept
{
  return x.magnitude();
}

//------------------------------------------------------------------------

inline bit::math::quaternion
  bit::math::operator+( const quaternion& lhs, const quaternion& rhs )
  noexcept
{
  return quaternion(lhs)+=rhs;
}
inline bit::math::quaternion
  bit::math::operator-( const quaternion& lhs, const quaternion& rhs )
  noexcept
{
  return quaternion(lhs)-=rhs;
}

inline bit::math::quaternion
  bit::math::operator*( const quaternion& lhs, const quaternion& rhs )
  noexcept
{
  return quaternion(lhs)*=rhs;
}

inline bit::math::quaternion
  bit::math::operator/( const quaternion& lhs, const quaternion& rhs )
  noexcept
{
  return quaternion(lhs)/=rhs;
}

//------------------------------------------------------------------------

inline bit::math::quaternion
  bit::math::operator*( const quaternion& lhs, quaternion::value_type rhs )
  noexcept
{
  return quaternion(lhs)*=rhs;
}

inline bit::math::quaternion
  bit::math::operator*( quaternion::value_type lhs, const quaternion& rhs )
  noexcept
{
  return quaternion(rhs)*=lhs;
}

inline bit::math::quaternion
  bit::math::operator/( const quaternion& lhs, quaternion::value_type rhs )
  noexcept
{
  return quaternion(lhs)/=rhs;
}

//----------------------------------------------------------------------------

inline bool bit::math::operator == ( const quaternion& lhs,
                                     const quaternion& rhs )
  noexcept
{
  for(auto i=0; i<4;++i) {
    if(lhs[i]!=rhs[i]) return false;
  }
  return true;
}

inline bool bit::math::operator != ( const quaternion& lhs,
                                     const quaternion& rhs )
  noexcept
{
  return !(lhs==rhs);
}

//----------------------------------------------------------------------------

inline bool bit::math::almost_equal( const quaternion& lhs,
                                     const quaternion& rhs )
  noexcept
{
  for(auto i=0; i<4;++i) {
    if(!almost_equal(lhs[i],rhs[i])) return false;
  }
  return true;
}

template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>*>
inline bool bit::math::almost_equal( const quaternion& lhs,
                                     const quaternion& rhs,
                                     Arithmetic tolerance )
  noexcept
{
  for(auto i=0; i<4;++i) {
    if(!almost_equal(lhs[i],rhs[i], tolerance)) return false;
  }
  return true;
}

#endif /* BIT_MATH_DETAIL_QUATERNION_INL */
