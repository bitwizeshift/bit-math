#ifndef BIT_MATH_DETAIL_VECTOR_VECTOR2_INL
#define BIT_MATH_DETAIL_VECTOR_VECTOR2_INL

#ifndef BIT_MATH_DETAIL_VECTOR_VECTOR2_HPP
# error "vector2.inl included without first including declaration header vector2.hpp"
#endif

//----------------------------------------------------------------------------
// Public Constants
//----------------------------------------------------------------------------

template<typename T>
const bit::math::vector2<T> bit::math::vector2<T>::zero = {T(0),T(0)};

template<typename T>
const bit::math::vector2<T> bit::math::vector2<T>::unit_x = {T(1),T(0)};

template<typename T>
const bit::math::vector2<T> bit::math::vector2<T>::unit_y = {T(0),T(1)};

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::vector2<T>::vector2( value_type scalar )
  noexcept
  : m_data{scalar,scalar}
{

}

template<typename T>
inline bit::math::vector2<T>::vector2( value_type magnitude, radian direction )
  noexcept
  : m_data {
      static_cast<T>(magnitude * cos(direction)),
      static_cast<T>(magnitude * sin(direction))
    }
{

}

template<typename T>
inline constexpr bit::math::vector2<T>::vector2( value_type x, value_type y )
  noexcept
  : m_data{x,y}
{

}

template<typename T>
template<typename U>
inline constexpr bit::math::vector2<T>::vector2( const vector2<U>& other )
  noexcept
  : m_data {
      static_cast<T>(other.x()),
      static_cast<T>(other.y())
    }
{

}

template<typename T>
template<typename U>
inline constexpr bit::math::vector2<T>::vector2( vector2<U>&& other )
  noexcept
  : m_data {
      static_cast<T>(std::move(other.x())),
      static_cast<T>(std::move(other.y()))
    }
{

}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector2<T>::size_type
  bit::math::vector2<T>::size()
  const noexcept
{
  return 2;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector2<T>::reference
  bit::math::vector2<T>::x()
  noexcept
{
  return m_data[0];
}

template<typename T>
inline constexpr typename bit::math::vector2<T>::const_reference
  bit::math::vector2<T>::x()
  const noexcept
{
  return m_data[0];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector2<T>::reference
  bit::math::vector2<T>::y()
  noexcept
{
  return m_data[1];
}

template<typename T>
inline constexpr typename bit::math::vector2<T>::const_reference
  bit::math::vector2<T>::y()
  const noexcept
{
  return m_data[1];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector2<T>::pointer
  bit::math::vector2<T>::data()
  noexcept
{
  return m_data;
}

template<typename T>
inline constexpr typename bit::math::vector2<T>::const_pointer
  bit::math::vector2<T>::data()
  const noexcept
{
  return m_data;
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector2<T>::reference
  bit::math::vector2<T>::at( index_type n )
{
  if( n >= 2 || n < 0 ) throw std::out_of_range("bit::math::vector2<T>::at: index out of range");
  return m_data[n];
}

template<typename T>
inline constexpr typename bit::math::vector2<T>::const_reference
bit::math::vector2<T>::at( index_type n )
  const
{
  if( n >= 2 || n < 0 ) throw std::out_of_range("bit::math::vector2<T>::at: index out of range");
  return m_data[n];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector2<T>::reference
  bit::math::vector2<T>::operator[]( index_type n )
  noexcept
{
  return m_data[n];
}

template<typename T>
inline constexpr typename bit::math::vector2<T>::const_reference
bit::math::vector2<T>::operator[]( index_type n )
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
  bit::math::vector2<T>::dot( const vector2<U>& other )
  const noexcept
{
  return (x() * other.x()) + (y() * other.y());
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr std::common_type_t<T,U>
  bit::math::vector2<T>::cross( const vector2<U>& other )
  const noexcept
{
  return (x() * other.y()) - (y() * other.x());
}

//----------------------------------------------------------------------------

template<typename T>
inline typename bit::math::vector2<T>::value_type
  bit::math::vector2<T>::magnitude()
  const noexcept
{
  return sqrt( (x()*x()) + (y()*y()) );
}

template<typename T>
template<typename U>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::vector2<T>::midpoint( const vector2<U>& rhs )
  const noexcept
{
  return vector2<std::common_type_t<T,U>>(
    ((x() + rhs.x()) * 0.5f),
    ((y() + rhs.y()) * 0.5f)
  );
}

template<typename T>
template<typename U>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::vector2<T>::reflection( const vector2<U>& normal )
  const noexcept
{
  return vector2<std::common_type_t<T,U>>(
    *this - ((2 * dot(normal)) * normal)
  );
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::vector2<T>::projection( const vector2<U>& vector )
  const noexcept
{
  return vector2<std::common_type_t<T,U>>{
    (dot(vector) / dot(*this)) * vector
  };
}

template<typename T>
template<typename U>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::vector2<T>::rejection( const vector2<U>& vector )
  const noexcept
{
  return (*this) - projection( vector );
}


//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::vector2<T>
  bit::math::vector2<T>::perpendicular()
  const noexcept
{
  return vector2<T>( -y(), x() );
}


template<typename T>
inline bit::math::vector2<T>
  bit::math::vector2<T>::normalized()
  const noexcept
{
  const auto mag = magnitude();
  if( mag > 0 ){
    const auto mag_inv = 1.0 / mag;
    return vector2<T>( x() * mag_inv, y() * mag_inv );
  }
  return (*this);
}

template<typename T>
inline constexpr bit::math::vector2<T>
  bit::math::vector2<T>::inverse()
  const noexcept
{
  return vector2<T>( -x(), -y() );
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline bit::math::radian
  bit::math::vector2<T>::angle_between( const vector2<U>& other )
  const noexcept
{
  float_t mag_product = magnitude() * other.magnitude();

  if( almost_equal( mag_product, 0, default_tolerance ) ){
    mag_product = default_tolerance;
  }

  float_t f = dot(other) / mag_product;

  f = clamp<float_t>( f, -1.0, 1.0 );
  return arccos( f );
}

template<typename T>
template<typename U>
inline bit::math::radian
  bit::math::vector2<T>::angle_to( const vector2<U>& other )
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
inline constexpr void bit::math::vector2<T>::swap( vector2& other )
  noexcept
{
  using std::swap;

  swap(m_data[0],other.m_data[0]);
  swap(m_data[1],other.m_data[1]);
}

template<typename T>
inline constexpr bit::math::vector2<T>& bit::math::vector2<T>::normalize()
  noexcept
{
  const auto mag = magnitude();

  if( mag > 0 ){
    const auto mag_inv = 1.0 / mag;

    x() *= mag_inv;
    y() *= mag_inv;
  }

  return (*this);
}

template<typename T>
inline constexpr bit::math::vector2<T>& bit::math::vector2<T>::invert()
  noexcept
{
  x() = -x();
  y() = -y();

  return (*this);
}

//----------------------------------------------------------------------------
// Unary Operators
//----------------------------------------------------------------------------

template<typename T>
inline constexpr const bit::math::vector2<T>& bit::math::vector2<T>::operator+()
  const noexcept
{
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::vector2<T> bit::math::vector2<T>::operator-()
  const noexcept
{
  return vector2<T>{ -x(), -y() };
}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector2<T>&
  bit::math::vector2<T>::operator+=( const vector2<U>& rhs )
  noexcept
{
  x() += rhs.x();
  y() += rhs.y();
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector2<T>&
  bit::math::vector2<T>::operator-=( const vector2<U>& rhs )
  noexcept
{
  x() -= rhs.x();
  y() -= rhs.y();
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector2<T>&
  bit::math::vector2<T>::operator*=( U scalar )
  noexcept
{
  x() *= scalar;
  y() *= scalar;
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector2<T>&
  bit::math::vector2<T>::operator/=( U scalar )
  noexcept
{
  const auto inv = 1.0 / scalar;

  x() *= inv;
  y() *= inv;
  return (*this);
}

//----------------------------------------------------------------------------
// Free Operators
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::operator+( const vector2<T>& lhs, const vector2<U>& rhs )
  noexcept
{
  return vector2<std::common_type_t<T,U>>(lhs)+=rhs;
}

template<typename T, typename U>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::operator-( const vector2<T>& lhs, const vector2<U>& rhs )
  noexcept
{
  return vector2<std::common_type_t<T,U>>(lhs)-=rhs;
}

template<typename T, typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::operator*( const vector2<T>& lhs, U scalar )
  noexcept
{
  return vector2<std::common_type_t<T,U>>(lhs)*=scalar;
}

template<typename T, typename U, typename std::enable_if<std::is_arithmetic<T>::value>*>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::operator*( T scalar, const vector2<U>& lhs )
  noexcept
{
  return vector2<std::common_type_t<T,U>>(lhs)*=scalar;
}

template<typename T, typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::operator/( const vector2<T>& lhs, U scalar )
  noexcept
{
  return vector2<std::common_type_t<T,U>>(lhs)/=scalar;
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr std::common_type_t<T,U>
  bit::math::dot( const vector2<T>& lhs, const vector2<U>& rhs )
  noexcept
{
  return lhs.dot(rhs);
}

template<typename T>
typename bit::math::vector2<T>::value_type
  bit::math::magnitude( const vector2<T>& vec )
  noexcept
{
  return vec.magnitude();
}

template<typename T>
constexpr void bit::math::swap( vector2<T>& lhs, vector2<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::math::operator == ( const vector2<T>& lhs,
                                               const vector2<U>& rhs )
  noexcept
{
  for(auto i=0;i<2;++i) {
    if( lhs[i]!=rhs[i] ) return false;
  }
  return true;
}

template<typename T, typename U>
inline constexpr bool bit::math::operator != ( const vector2<T>& lhs,
                                               const vector2<U>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::math::almost_equal( const vector2<T>& lhs,
                                               const vector2<U>& rhs )
  noexcept
{
  for(auto i=0;i<2;++i) {
    if( !almost_equal(rhs[i],rhs[i]) ) return false;
  }
  return true;
}

template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>*>
inline constexpr bool bit::math::almost_equal( const vector2<T>& lhs,
                                               const vector2<U>& rhs,
                                               Arithmetic tolerance )
  noexcept
{
  for(auto i=0;i<2;++i) {
    if( !almost_equal(rhs[i],rhs[i],tolerance) ) return false;
  }
  return true;
}

#endif /* BIT_MATH_DETAIL_VECTOR_VECTOR2_INL */
