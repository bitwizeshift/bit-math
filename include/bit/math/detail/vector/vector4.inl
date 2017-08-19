#ifndef BIT_MATH_DETAIL_VECTOR_VECTOR4_INL
#define BIT_MATH_DETAIL_VECTOR_VECTOR4_INL

#ifndef BIT_MATH_DETAIL_VECTOR_VECTOR4_HPP
# error "vector4.inl included without first including declaration header vector4.hpp"
#endif

//----------------------------------------------------------------------------
// Public Constants
//----------------------------------------------------------------------------

template<typename T>
const bit::math::vector4<T> bit::math::vector4<T>::zero = {T(0),T(0),T(0),T(0)};

template<typename T>
const bit::math::vector4<T> bit::math::vector4<T>::unit_x = {T(1),T(0),T(0),T(0)};

template<typename T>
const bit::math::vector4<T> bit::math::vector4<T>::unit_y = {T(0),T(1),T(0),T(0)};

template<typename T>
const bit::math::vector4<T> bit::math::vector4<T>::unit_z = {T(0),T(0),T(1),T(0)};

template<typename T>
const bit::math::vector4<T> bit::math::vector4<T>::unit_w = {T(0),T(0),T(0),T(1)};

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::vector4<T>::vector4( value_type scalar )
  noexcept
  : m_data{scalar,scalar,scalar,scalar}
{

}

template<typename T>
inline constexpr bit::math::vector4<T>::vector4( value_type x,
                                                 value_type y,
                                                 value_type z,
                                                 value_type w )
  noexcept
  : m_data{x,y,z,w}
{

}

template<typename T>
template<typename U>
inline constexpr bit::math::vector4<T>::vector4( const vector4<U>& other )
  noexcept
  : m_data {
      static_cast<T>(other.x()),
      static_cast<T>(other.y()),
      static_cast<T>(other.z()),
      static_cast<T>(other.w())
    }
{

}

template<typename T>
template<typename U>
inline constexpr bit::math::vector4<T>::vector4( vector4<U>&& other )
  noexcept
  : m_data{
      static_cast<T>(std::move(other.x())),
      static_cast<T>(std::move(other.y())),
      static_cast<T>(std::move(other.z())),
      static_cast<T>(std::move(other.w()))
    }
{

}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector4<T>::size_type
  bit::math::vector4<T>::size()
  const noexcept
{
  return 4;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector4<T>::reference
  bit::math::vector4<T>::x()
  noexcept
{
  return m_data[0];
}

template<typename T>
inline constexpr typename bit::math::vector4<T>::const_reference
  bit::math::vector4<T>::x()
  const noexcept
{
  return m_data[0];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector4<T>::reference
  bit::math::vector4<T>::y()
  noexcept
{
  return m_data[1];
}

template<typename T>
inline constexpr typename bit::math::vector4<T>::const_reference
  bit::math::vector4<T>::y()
  const noexcept
{
  return m_data[1];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector4<T>::reference
  bit::math::vector4<T>::z()
  noexcept
{
  return m_data[2];
}

template<typename T>
inline constexpr typename bit::math::vector4<T>::const_reference
  bit::math::vector4<T>::z()
  const noexcept
{
  return m_data[2];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector4<T>::reference
  bit::math::vector4<T>::w()
  noexcept
{
  return m_data[3];
}

template<typename T>
inline constexpr typename bit::math::vector4<T>::const_reference
  bit::math::vector4<T>::w()
  const noexcept
{
  return m_data[3];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector4<T>::pointer
  bit::math::vector4<T>::data()
  noexcept
{
  return m_data;
}

template<typename T>
inline constexpr typename bit::math::vector4<T>::const_pointer
  bit::math::vector4<T>::data()
  const noexcept
{
  return m_data;
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector4<T>::reference
  bit::math::vector4<T>::at( index_type n )
{
  if( n >= 4 || n < 0 ) throw std::out_of_range("bit::math::vector4<T>::at: index out of range");
  return m_data[n];
}

template<typename T>
inline constexpr typename bit::math::vector4<T>::const_reference
bit::math::vector4<T>::at( index_type n )
  const
{
  if( n >= 4 || n < 0 ) throw std::out_of_range("bit::math::vector4<T>::at: index out of range");
  return m_data[n];
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::vector4<T>::reference
  bit::math::vector4<T>::operator[]( index_type n )
  noexcept
{
  return m_data[n];
}

template<typename T>
inline constexpr typename bit::math::vector4<T>::const_reference
bit::math::vector4<T>::operator[]( index_type n )
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
  bit::math::vector4<T>::dot( const vector4<U>& other )
  const noexcept
{
  // Use a loop to suggest vectorized math
  auto sum = std::common_type_t<T,U>(0);

  for( auto i = 0; i < 4; ++i ) {
    sum += m_data[i] * other.m_data[i];
  }

  return sum;
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector4<std::common_type_t<T,U>>
  bit::math::vector4<T>::cross( const vector4<U>& other )
  const noexcept
{
  return vector4<std::common_type_t<T,U>>(
    (y() * other.z() - z() * other.y()),
    (z() * other.x() - x() * other.z()),
    (x() * other.y() - y() * other.x()),
    0
  );
}

//----------------------------------------------------------------------------

template<typename T>
inline typename bit::math::vector4<T>::value_type
  bit::math::vector4<T>::magnitude()
  const noexcept
{
  return sqrt( dot(*this) );
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector4<std::common_type_t<T,U>>
  bit::math::vector4<T>::midpoint( const vector4<U>& rhs )
  const noexcept
{
  return vector4<std::common_type_t<T,U>>(
    ((x() + rhs.x()) * 0.5f),
    ((y() + rhs.y()) * 0.5f),
    ((z() + rhs.z()) * 0.5f),
    ((w() + rhs.w()) * 0.5f)
  );
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector4<std::common_type_t<T,U>>
  bit::math::vector4<T>::projection( const vector4<U>& vector )
  const noexcept
{
  return vector4<std::common_type_t<T,U>>{
    (dot(vector) / dot(*this)) * vector
  };
}

template<typename T>
template<typename U>
inline constexpr bit::math::vector4<std::common_type_t<T,U>>
  bit::math::vector4<T>::rejection( const vector4<U>& vector )
  const noexcept
{
  return (*this) - projection( vector );
}

//----------------------------------------------------------------------------

template<typename T>
inline bit::math::vector4<T>
  bit::math::vector4<T>::normalized()
  const noexcept
{
  const value_type mag = magnitude();

  if( mag > 0 )
  {
    const auto mag_inv = 1.0 / mag;

    return vector4<T>(
      x() * mag_inv,
      y() * mag_inv,
      z() * mag_inv,
      w() * mag_inv
    );
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::vector4<T>
  bit::math::vector4<T>::inverse()
  const noexcept
{
  return vector4<T>{ -x(), -y(), -z(), -w() };
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::math::vector4<T>::swap( vector4& other )
  noexcept
{
  using std::swap;

  swap(m_data[0],other.m_data[0]);
  swap(m_data[1],other.m_data[1]);
  swap(m_data[2],other.m_data[2]);
  swap(m_data[3],other.m_data[3]);
}

template<typename T>
inline constexpr bit::math::vector4<T>& bit::math::vector4<T>::normalize()
  noexcept
{
  const value_type mag = magnitude();

  if( mag > 0 )
  {
    const auto mag_inv = 1.0 / mag;

    x() *= mag_inv;
    y() *= mag_inv;
    z() *= mag_inv;
    w() *= mag_inv;
  }

  return (*this);
}

template<typename T>
inline constexpr bit::math::vector4<T>& bit::math::vector4<T>::invert()
  noexcept
{
  x() = -x();
  y() = -y();
  z() = -z();
  w() = -w();

  return (*this);
}

//----------------------------------------------------------------------------
// Unary Operators
//----------------------------------------------------------------------------

template<typename T>
inline constexpr const bit::math::vector4<T>& bit::math::vector4<T>::operator+()
  const noexcept
{
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::vector4<T> bit::math::vector4<T>::operator-()
  const noexcept
{
  return vector4<T>{ -x(), -y(), -z(), -w() };
}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector4<T>&
  bit::math::vector4<T>::operator+=( const vector4<U>& rhs )
  noexcept
{
  for(auto i = 0; i < 4; ++i) {
    m_data[i] += rhs[i];
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::vector4<T>&
  bit::math::vector4<T>::operator-=( const vector4<U>& rhs )
  noexcept
{
  for(auto i = 0; i < 4; ++i) {
    m_data[i] -= rhs[i];
  }

  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector4<T>&
  bit::math::vector4<T>::operator*=( U scalar )
  noexcept
{
  for(auto i = 0; i < 4; ++i) {
    m_data[i] *= scalar;
  }

  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector4<T>&
  bit::math::vector4<T>::operator/=( U scalar )
  noexcept
{
  const auto inv = (1.0 / scalar);

  for(auto i = 0; i < 4; ++i) {
    m_data[i] *= inv;
  }

  return (*this);
}

//----------------------------------------------------------------------------
// Free Operators
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector4<std::common_type_t<T,U>>
  bit::math::operator+( const vector4<T>& lhs, const vector4<U>& rhs )
  noexcept
{
  return vector4<std::common_type_t<T,U>>(lhs)+=rhs;
}

template<typename T, typename U>
inline constexpr bit::math::vector4<std::common_type_t<T,U>>
  bit::math::operator-( const vector4<T>& lhs, const vector4<U>& rhs )
  noexcept
{
  return vector4<std::common_type_t<T,U>>(lhs)-=rhs;
}

template<typename T, typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector4<std::common_type_t<T,U>>
  bit::math::operator*( const vector4<T>& lhs, U scalar )
  noexcept
{
  return vector4<std::common_type_t<T,U>>(lhs)*=scalar;
}

template<typename T, typename U, typename std::enable_if<std::is_arithmetic<T>::value>*>
inline constexpr bit::math::vector4<std::common_type_t<T,U>>
  bit::math::operator*( T scalar, const vector4<U>& lhs )
  noexcept
{
  return vector4<std::common_type_t<T,U>>(lhs)*=scalar;
}

template<typename T, typename U, typename std::enable_if<std::is_arithmetic<U>::value>*>
inline constexpr bit::math::vector4<std::common_type_t<T,U>>
  bit::math::operator/( const vector4<T>& lhs, U scalar )
  noexcept
{
  return vector4<std::common_type_t<T,U>>(lhs)/=scalar;
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr std::common_type_t<T,U>
  bit::math::dot( const vector4<T>& lhs, const vector4<U>& rhs )
  noexcept
{
  return lhs.dot(rhs);
}

template<typename T>
typename bit::math::vector4<T>::value_type
  bit::math::magnitude( const vector4<T>& vec )
  noexcept
{
  return vec.magnitude();
}

template<typename T>
constexpr void bit::math::swap( vector4<T>& lhs, vector4<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::math::operator == ( const vector4<T>& lhs,
                                               const vector4<U>& rhs )
  noexcept
{
  for(auto i=0;i<4;++i) {
    if( lhs[i]!=rhs[i] ) return false;
  }
  return true;
}

template<typename T, typename U>
inline constexpr bool bit::math::operator != ( const vector4<T>& lhs,
                                               const vector4<U>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::math::almost_equal( const vector4<T>& lhs,
                                               const vector4<U>& rhs )
  noexcept
{
  for(auto i=0;i<4;++i) {
    if( !almost_equal(rhs[i],rhs[i]) ) return false;
  }
  return true;
}

template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>*>
inline constexpr bool bit::math::almost_equal( const vector4<T>& lhs,
                                               const vector4<U>& rhs,
                                               Arithmetic tolerance )
  noexcept
{
  for(auto i=0;i<4;++i) {
    if( !almost_equal(rhs[i],rhs[i],tolerance) ) return false;
  }
  return true;
}

#endif /* BIT_MATH_DETAIL_VECTOR_VECTOR4_INL */
