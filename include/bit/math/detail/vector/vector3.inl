#ifndef BIT_MATH_DETAIL_VECTOR_VECTOR3_INL
#define BIT_MATH_DETAIL_VECTOR_VECTOR3_INL

//----------------------------------------------------------------------------
// Public Constants
//----------------------------------------------------------------------------

template<typename T>
const bit::math::vector3<T> bit::math::vector3<T>::zero = {T(0),T(0),T(0)};

template<typename T>
const bit::math::vector3<T> bit::math::vector3<T>::unit_x = {T(1),T(0),T(0)};

template<typename T>
const bit::math::vector3<T> bit::math::vector3<T>::unit_y = {T(0),T(1),T(0)};

template<typename T>
const bit::math::vector3<T> bit::math::vector3<T>::unit_z = {T(0),T(0),T(1)};

template<typename T>
const bit::math::vector3<T> bit::math::vector3<T>::neg_unit_x = {T(-1),T(0),T(0)};

template<typename T>
const bit::math::vector3<T> bit::math::vector3<T>::neg_unit_y = {T(0),T(-1),T(0)};

template<typename T>
const bit::math::vector3<T> bit::math::vector3<T>::neg_unit_z = {T(0),T(0),T(-1)};

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::vector3<T>::vector3( value_type scalar )
  noexcept
  : m_data{scalar,scalar,scalar}
{

}

template<typename T>
inline constexpr bit::math::vector3<T>::vector3( value_type x,
                                                 value_type y,
                                                 value_type z )
  noexcept
  : m_data{x,y,z}
{

}

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<T>::vector3( const vector3<U>& other )
  noexcept
  : m_data {
      static_cast<T>(other.x()),
      static_cast<T>(other.y()),
      static_cast<T>(other.z())
    }
{

}

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<T>::vector3( vector3<U>&& other )
  noexcept
  : m_data {
      static_cast<T>(std::move(other.x())),
      static_cast<T>(std::move(other.y())),
      static_cast<T>(std::move(other.z()))
    }
{

}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector3<T>::size_type
  bit::math::vector3<T>::size()
  const noexcept
{
  return 3;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector3<T>::reference
  bit::math::vector3<T>::x()
  noexcept
{
  return m_data[0];
}

template<typename T>
inline constexpr typename bit::math::vector3<T>::const_reference
  bit::math::vector3<T>::x()
  const noexcept
{
  return m_data[0];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector3<T>::reference
  bit::math::vector3<T>::y()
  noexcept
{
  return m_data[1];
}

template<typename T>
inline constexpr typename bit::math::vector3<T>::const_reference
  bit::math::vector3<T>::y()
  const noexcept
{
  return m_data[1];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector3<T>::reference
  bit::math::vector3<T>::z()
  noexcept
{
  return m_data[2];
}

template<typename T>
inline constexpr typename bit::math::vector3<T>::const_reference
  bit::math::vector3<T>::z()
  const noexcept
{
  return m_data[2];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector3<T>::pointer
  bit::math::vector3<T>::data()
  noexcept
{
  return m_data;
}

template<typename T>
inline constexpr typename bit::math::vector3<T>::const_pointer
  bit::math::vector3<T>::data()
  const noexcept
{
  return m_data;
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector3<T>::reference
  bit::math::vector3<T>::at( index_type n )
{
  if( n >= 3 || n < 0 ) throw std::out_of_range("bit::math::vector3<T>::at: index out of range");
  return m_data[n];
}

template<typename T>
inline constexpr typename bit::math::vector3<T>::const_reference
bit::math::vector3<T>::at( index_type n )
  const
{
  if( n >= 3 || n < 0 ) throw std::out_of_range("bit::math::vector3<T>::at: index out of range");
  return m_data[n];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector3<T>::reference
  bit::math::vector3<T>::operator[]( index_type n )
  noexcept
{
  return m_data[n];
}

template<typename T>
inline constexpr typename bit::math::vector3<T>::const_reference
bit::math::vector3<T>::operator[]( index_type n )
  const noexcept
{
  return m_data[n];
}

//----------------------------------------------------------------------------
// Quantifiers
//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr std::common_type_t<T,U>
  bit::math::vector3<T>::dot( const vector3<U>& other )
  const noexcept
{
  return (x() * other.x()) + (y() * other.y()) + (z() * other.z());
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::vector3<T>::cross( const vector3<U>& other )
  const noexcept
{
  return vector3<std::common_type_t<T,U>>(
    (y() * other.z() - z() * other.y()),
    (z() * other.x() - x() * other.z()),
    (x() * other.y() - y() * other.x())
  );
}

//----------------------------------------------------------------------------

template<typename T>
inline typename bit::math::vector3<T>::value_type
  bit::math::vector3<T>::magnitude()
  const noexcept
{
  return sqrt( (x()*x()) + (y()*y()) + (z()*z()) );
}

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::vector3<T>::midpoint( const vector3<U>& rhs )
  const noexcept
{
  return vector3<std::common_type_t<T,U>>(
    ((x() + rhs.x()) * 0.5f),
    ((y() + rhs.y()) * 0.5f),
    ((z() + rhs.z()) * 0.5f)
  );
}

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::vector3<T>::reflection( const vector3<U>& normal )
  const noexcept
{
  return vector3<std::common_type_t<T,U>>{
    *this - ((2 * dot(normal)) * normal)
  };
}

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::vector3<T>::projection( const vector3<U>& vector )
  const noexcept
{
  return vector3<std::common_type_t<T,U>>{
    (dot(vector) / dot(*this)) * vector
  };
}

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::vector3<T>::rejection( const vector3<U>& vector )
  const noexcept
{
  return (*this) - projection( vector );
}


template<typename T>
inline constexpr bit::math::vector3<T>
  bit::math::vector3<T>::perpendicular()
  const noexcept
{
  vector3<T> perp = cross( vector3<T>::unit_x );

  if( almost_equal( perp.magnitude(), 0 ) ) {
    perp = cross( vector3<T>::unit_y );
  }

  return perp.normalize();
}


template<typename T>
inline bit::math::vector3<T>
  bit::math::vector3<T>::normalized()
  const noexcept
{
  const auto mag = magnitude();
  if( mag > 0 ){
    const auto mag_inv = 1.0 / mag;
    return vector3<T>( x() * mag_inv, y() * mag_inv, z() * mag_inv );
  }
  return (*this);
}

template<typename T>
inline constexpr bit::math::vector3<T>
  bit::math::vector3<T>::inverse()
  const noexcept
{
  return vector3<T>( -x(), -y(), -z() );
}

template<typename T>
template<typename U>
bit::math::radian
  bit::math::vector3<T>::angle_between( const vector3<U>& other )
  const noexcept
{
  auto mag_product = magnitude() * other.magnitude();

  if( almost_equal( mag_product, 0, default_tolerance ) ){
    mag_product = default_tolerance;
  }

  auto f = dot(other) / mag_product;

  f = clamp( f, -1.0, 1.0 );
  return arccos( f );
}

template<typename T>
template<typename U>
bit::math::radian
  bit::math::vector3<T>::angle_to( const vector3<U>& other )
  const noexcept
{
  radian angle = angle_between( other );

  if( cross(other) < T(0) )
    return radian( two_pi<float_t>() ) - angle;

  return angle;
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::math::vector3<T>::swap( vector3& other )
  noexcept
{
  using std::swap;

  swap(m_data[0],other.m_data[0]);
  swap(m_data[1],other.m_data[1]);
  swap(m_data[2],other.m_data[2]);
}

template<typename T>
inline constexpr bit::math::vector3<T>& bit::math::vector3<T>::normalize()
  noexcept
{
  const auto mag = magnitude();

  if( mag > 0 ){
    const auto mag_inv = 1.0 / mag;

    x() *= mag_inv;
    y() *= mag_inv;
    z() *= mag_inv;
  }

  return (*this);
}

template<typename T>
inline constexpr bit::math::vector3<T>& bit::math::vector3<T>::invert()
  noexcept
{
  x() = -x();
  y() = -y();
  z() = -z();

  return (*this);
}

//----------------------------------------------------------------------------
// Unary Operators
//----------------------------------------------------------------------------

template<typename T>
inline constexpr const bit::math::vector3<T>& bit::math::vector3<T>::operator+()
  const noexcept
{
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::vector3<T> bit::math::vector3<T>::operator-()
  const noexcept
{
  return vector3<T>( -x(), -y(), -z() );
}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<T>&
  bit::math::vector3<T>::operator+=( const vector3<U>& rhs )
  noexcept
{
  x() += rhs.x();
  y() += rhs.y();
  z() += rhs.z();
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<T>&
  bit::math::vector3<T>::operator-=( const vector3<U>& rhs )
  noexcept
{
  x() -= rhs.x();
  y() -= rhs.y();
  z() -= rhs.z();
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<T>&
  bit::math::vector3<T>::operator*=( U&& scalar )
  noexcept
{
  x() *= scalar;
  y() *= scalar;
  z() *= scalar;
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector3<T>&
  bit::math::vector3<T>::operator/=( U&& scalar )
  noexcept
{
  const auto inv = 1.0 / scalar;

  x() *= inv;
  y() *= inv;
  z() *= inv;
  return (*this);
}

//----------------------------------------------------------------------------
// Free Operators
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::operator+( const vector3<T>& lhs, const vector3<U>& rhs )
  noexcept
{
  return vector3<std::common_type_t<T,U>>(lhs)+=rhs;
}

template<typename T, typename U>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::operator-( const vector3<T>& lhs, const vector3<U>& rhs )
  noexcept
{
  return vector3<std::common_type_t<T,U>>(lhs)-=rhs;
}

template<typename T, typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::operator*( const vector3<T>& lhs, U scalar )
  noexcept
{
  return vector3<std::common_type_t<T,U>>(lhs)*=scalar;
}

template<typename T, typename U, typename std::enable_if<std::is_arithmetic<T>::value>*>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::operator*( T scalar, const vector3<U>& lhs )
  noexcept
{
  return vector3<std::common_type_t<T,U>>(lhs)*=scalar;
}

template<typename T, typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::operator/( const vector3<T>& lhs, U scalar )
  noexcept
{
  return vector3<std::common_type_t<T,U>>(lhs)/=scalar;
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr std::common_type_t<T,U>
  bit::math::dot( const vector3<T>& lhs, const vector3<U>& rhs )
  noexcept
{
  return lhs.dot(rhs);
}

template<typename T, typename U>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::cross( const vector3<T>& lhs, const vector3<U>& rhs )
  noexcept
{
  return lhs.cross(rhs);
}

template<typename T>
typename bit::math::vector3<T>::value_type
  bit::math::magnitude( const vector3<T>& vec )
  noexcept
{
  return vec.magnitude();
}

template<typename T>
constexpr void bit::math::swap( vector3<T>& lhs, vector3<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::math::operator == ( const vector3<T>& lhs,
                                               const vector3<U>& rhs )
  noexcept
{
  for(auto i=0;i<3;++i) {
    if( lhs[i]!=rhs[i] ) return false;
  }
  return true;
}

template<typename T, typename U>
inline constexpr bool bit::math::operator != ( const vector3<T>& lhs,
                                               const vector3<U>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::math::almost_equal( const vector3<T>& lhs,
                                               const vector3<U>& rhs )
  noexcept
{
  for(auto i=0;i<3;++i) {
    if( !almost_equal(rhs[i],rhs[i]) ) return false;
  }
  return true;
}

template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>*>
inline constexpr bool bit::math::almost_equal( const vector3<T>& lhs,
                                               const vector3<U>& rhs,
                                               Arithmetic tolerance )
  noexcept
{
  for(auto i=0;i<3;++i) {
    if( !almost_equal(rhs[i],rhs[i],tolerance) ) return false;
  }
  return true;
}

#endif /* BIT_MATH_DETAIL_VECTOR_VECTOR3_INL */
