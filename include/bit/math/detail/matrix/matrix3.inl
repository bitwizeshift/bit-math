#ifndef BIT_MATH_DETAIL_MATRIX_MATRIX3_INL
#define BIT_MATH_DETAIL_MATRIX_MATRIX3_INL

//----------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------

template<typename T>
const bit::math::matrix3<T> bit::math::matrix3<T>::identity
  = { {T(1), T(0), T(0)},
      {T(0), T(1), T(0)},
      {T(0), T(0), T(1)} };

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix3<T>::matrix3( const vector3<T>& v0,
                                                 const vector3<T>& v1,
                                                 const vector3<T>& v2 )
  noexcept
  : m_matrix {
      {v0.x(), v0.y(), v0.z()},
      {v1.x(), v1.y(), v1.z()},
      {v2.x(), v2.y(), v2.z()}
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix3<T>::matrix3( const value_type(&array)[9] )
  noexcept
  : m_matrix {
      {array[0], array[1], array[2]},
      {array[3], array[4], array[5]},
      {array[6], array[7], array[8]}
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix3<T>::matrix3( const value_type(&array)[3][3] )
  noexcept
  : m_matrix {
      {array[0][0], array[0][1], array[0][2]},
      {array[1][0], array[1][1], array[1][2]},
      {array[2][0], array[2][1], array[2][2]}
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix3<T>::matrix3( value_type m00, value_type m01, value_type m02,
                                                 value_type m10, value_type m11, value_type m12,
                                                 value_type m20, value_type m21, value_type m22 )
  noexcept
  : m_matrix {
      {m00, m01, m02},
      {m10, m11, m12},
      {m20, m21, m22}
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::matrix3<T>::matrix3( const matrix3<U>& other )
  noexcept
  : m_matrix {
      {other.m_matrix[0][0], other.m_matrix[0][1], other.m_matrix[0][2]},
      {other.m_matrix[1][0], other.m_matrix[1][1], other.m_matrix[1][2]},
      {other.m_matrix[2][0], other.m_matrix[2][1], other.m_matrix[2][2]}
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::matrix3<T>::matrix3( matrix3<U>&& other )
  noexcept
  : m_matrix {
      {std::move(other.m_matrix[0][0]), std::move(other.m_matrix[0][1]), std::move(other.m_matrix[0][2])},
      {std::move(other.m_matrix[1][0]), std::move(other.m_matrix[1][1]), std::move(other.m_matrix[1][2])},
      {std::move(other.m_matrix[2][0]), std::move(other.m_matrix[2][1]), std::move(other.m_matrix[2][2])}
    }
{

}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix3<T>::reference
  bit::math::matrix3<T>::at( index_type r, index_type c )
{
  if( c >=columns || c < 0 || r >=rows || r < 0 )
    throw std::out_of_range("matrix3::at: index out of range");
  return get(r,c);
}


template<typename T>
inline constexpr typename bit::math::matrix3<T>::const_reference
  bit::math::matrix3<T>::at( index_type r, index_type c )
  const
{
  if( c >=columns || c < 0 || r >=rows || r < 0 )
    throw std::out_of_range("matrix3::at: index out of range");
  return get(r,c);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix3<T>::reference
  bit::math::matrix3<T>::operator()( index_type r, index_type c )
  noexcept
{
  return get(r,c);
}


template<typename T>
inline constexpr typename bit::math::matrix3<T>::const_reference
  bit::math::matrix3<T>::operator()( index_type r, index_type c )
  const noexcept
{
  return get(r,c);
}

template<typename T>
inline constexpr bit::math::vector3<T>
  bit::math::matrix3<T>::row( index_type r )
  const noexcept
{
  return vector3<T>{ get(r,0), get(r,1), get(r,2) };
}

template<typename T>
inline constexpr bit::math::vector3<T>
  bit::math::matrix3<T>::column( index_type c )
  const noexcept
{
  return vector3<T>{ get(0,c), get(1,c), get(2,c) };
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix3<T>::size_type
  bit::math::matrix3<T>::size()
  const noexcept
{
  return rows*columns;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix3<T>::pointer
  bit::math::matrix3<T>::data()
  noexcept
{
  return std::addressof(get(0,0));
}

template<typename T>
inline constexpr typename bit::math::matrix3<T>::const_pointer
  bit::math::matrix3<T>::data()
  const noexcept
{
  return std::addressof(get(0,0));
}

//----------------------------------------------------------------------------
// Quantifiers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix3<T>::value_type
  bit::math::matrix3<T>::determinant()
  const noexcept
{
  return (get(0,0)*get(1,1)*get(2,2)) -
         (get(0,0)*get(1,2)*get(2,1)) -
         (get(0,1)*get(1,0)*get(2,2)) +
         (get(0,1)*get(1,2)*get(2,0)) +
         (get(0,2)*get(1,0)*get(2,1)) -
         (get(0,2)*get(1,1)*get(2,0));
}

template<typename T>
inline constexpr typename bit::math::matrix3<T>::value_type
  bit::math::matrix3<T>::trace()
  const noexcept
{
  return (get(0,0) + get(1,1) + get(2,2));
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix3<T>
  bit::math::matrix3<T>::inverse()
  const noexcept
{
  const auto det = determinant();

  if( det == value_type(0) ) return matrix3<T>::identity;

  const auto inv_det = (1.0 / det);
  return matrix3<T>(
    (get(1,1)*get(2,2) - get(1,2)*get(2,1)) * inv_det,
    (get(1,2)*get(2,0) - get(1,0)*get(2,2)) * inv_det,
    (get(1,0)*get(2,1) - get(1,1)*get(2,0)) * inv_det,

    (get(0,2)*get(2,1) - get(0,1)*get(2,2)) * inv_det,
    (get(0,0)*get(2,2) - get(0,2)*get(2,0)) * inv_det,
    (get(0,1)*get(2,0) - get(0,0)*get(2,1)) * inv_det,

    (get(0,1)*get(1,2) - get(0,2)*get(1,1)) * inv_det,
    (get(0,2)*get(1,0) - get(0,0)*get(1,2)) * inv_det,
    (get(0,0)*get(1,1) - get(0,1)*get(1,0)) * inv_det
  );
}

template<typename T>
inline constexpr bit::math::matrix3<T>
  bit::math::matrix3<T>::transposed()
  const noexcept
{
  return matrix3<T> {
    get(0,0), get(1,0), get(2,0),
    get(0,1), get(1,1), get(2,1),
    get(0,2), get(1,2), get(2,2)
  };
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::matrix3<T>::combine( const vector3<U>& vec )
  const noexcept
{
  auto result = vector3<std::common_type_t<T,U>>();

  for( auto r = 0; r < columns; ++r ) {
    auto sum = std::common_type_t<T,U>(0);

    for( auto c = 0; c < rows; ++c ) {
      sum += vec[c] * get(r,c);
    }
    result[r] = sum;
  }
  return result;
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::math::matrix3<T>::swap( matrix3<T>& other )
  noexcept
{
  using std::swap;

  for( auto r = 0; r < rows; ++r ) {
    for( auto c = 0; c < columns; ++c ) {
      swap(get(r,c),other.get(r,c));
    }
  }
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix3<T>& bit::math::matrix3<T>::invert()
  noexcept
{
  (*this) = inverse();
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix3<T>& bit::math::matrix3<T>::transpose()
  noexcept
{
  using std::swap;

  for( auto r = 0; r < rows; ++r ) {
    for( auto c = 0; c < r; ++c ) {
      if( r != c ) {
        swap(get(r,c),get(c,r));
      }
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline bit::math::matrix3<T>&
  bit::math::matrix3<T>::operator+=( const matrix3<U>& rhs )
  noexcept
{
  for( auto r = 0; r < rows; ++r) {
    for( auto c = 0; c < columns; ++c ) {
      get(r,c) += rhs.get(r,c);
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix3<T>&
  bit::math::matrix3<T>::operator-=(const matrix3<U>& rhs)
  noexcept
{
  for( auto r = 0; r < rows; ++r) {
    for( auto c = 0; c < columns; ++c ) {
      get(r,c) -= rhs.get(r,c);
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix3<T>&
  bit::math::matrix3<T>::operator*=(const matrix3<U>& rhs)
  noexcept
{
  value_type result[rows][columns];

  for( auto r = 0; r < rows; ++r ) {
    for( auto c = 0; c < columns; ++c ) {

      auto sum = std::common_type_t<T,U>(0);

      for( auto i = 0; i < rows; ++i ) {
        sum += (get(i,c) * rhs.get(r,i));
      }
      result[r][c] = sum;
    }
  }

  // Copy result in
  for( auto i = 0; i < rows; ++i ) {
    for( auto j = 0; j < columns; ++j ) {
      get(i,j) = result[i][j];
    }
  }

  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix3<T>&
  bit::math::matrix3<T>::operator*=(U scalar)
  noexcept
{
  for( auto r = 0; r < rows; ++r ) {
    for( auto c = 0; c < columns; ++c ) {
      get(r,c) *= scalar;
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix3<T>&
  bit::math::matrix3<T>::operator/=( U scalar )
  noexcept
{
  auto inv = (1.0) / scalar;

  for( auto r = 0; r < rows; ++r ) {
    for( auto c = 0; c < columns; ++c ) {
      get(r,c) *= inv;
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix3<T>::reference
  bit::math::matrix3<T>::get( index_type r, index_type c )
  noexcept
{
  return m_matrix[r][c];
}

template<typename T>
inline constexpr typename bit::math::matrix3<T>::const_reference
  bit::math::matrix3<T>::get( index_type r, index_type c )
  const noexcept
{
  return m_matrix[r][c];
}


//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::math::swap( matrix3<T>& lhs, matrix3<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Free Operators
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::matrix3<std::common_type_t<T,U>>
  bit::math::operator+( const matrix3<T>& lhs, const matrix3<U>& rhs )
  noexcept
{
  return matrix3<std::common_type_t<T,U>>(lhs)+=rhs;
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::matrix3<std::common_type_t<T,U>>
  bit::math::operator-( const matrix3<T>& lhs, const matrix3<U>& rhs )
  noexcept
{
  return matrix3<std::common_type_t<T,U>>(lhs)-=rhs;
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::matrix3<std::common_type_t<T,U>>
  bit::math::operator*( const matrix3<T>& lhs, const matrix3<U>& rhs )
  noexcept
{
  return matrix3<std::common_type_t<T,U>>(lhs)*=rhs;
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector3<std::common_type_t<T,U>>
  bit::math::operator*( const vector3<T>& lhs, const matrix3<U>& rhs )
  noexcept
{
  return rhs.combine(lhs);
}

//------------------------------------------------------------------------

template<typename T, typename U, std::enable_if_t<std::is_arithmetic<T>::value>*>
constexpr bit::math::matrix3<std::common_type_t<T,U>>
  bit::math::operator*( T lhs, const matrix3<U>& rhs )
  noexcept
{
  return matrix3<std::common_type_t<T,U>>(rhs) *= lhs;
}

//------------------------------------------------------------------------

template<typename T, typename U, std::enable_if_t<std::is_arithmetic<U>::value>*>
constexpr bit::math::matrix3<std::common_type_t<T,U>>
  bit::math::operator*( const matrix3<T>& lhs, U rhs )
  noexcept
{
  return matrix3<std::common_type_t<T,U>>(lhs) *= rhs;
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::math::operator == ( const matrix3<T>& lhs,
                                               const matrix3<U>& rhs )
  noexcept
{
  for(auto r=0;r<matrix3<T>::rows;++r) {
    for(auto c=0;c<matrix3<T>::columns;++c) {
      if( lhs(r,c)!=rhs(r,c) ) return false;
    }
  }
  return true;
}

template<typename T, typename U>
inline constexpr bool bit::math::operator != ( const matrix3<T>& lhs,
                                               const matrix3<U>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool bit::math::almost_equal( const matrix3<T>& lhs,
                                               const matrix3<U>& rhs )
  noexcept
{
  for(auto r=0;r<matrix3<T>::rows;++r) {
    for(auto c=0;c<matrix3<T>::columns;++c) {
      if( !almost_equal(rhs(r,c),rhs(r,c)) ) return false;
    }
  }
  return true;
}

template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>*>
inline constexpr bool bit::math::almost_equal( const matrix3<T>& lhs,
                                               const matrix3<U>& rhs,
                                               Arithmetic tolerance )
  noexcept
{
  for(auto r=0;r<matrix3<T>::rows;++r) {
    for(auto c=0;c<matrix3<T>::columns;++c) {
      if( !almost_equal(rhs(r,c),rhs(r,c), tolerance) ) return false;
    }
  }
  return true;
}
#endif /* BIT_MATH_DETAIL_MATRIX_MATRIX3_INL */
