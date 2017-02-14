#ifndef BIT_MATH_DETAIL_MATRIX_MATRIX2_INL
#define BIT_MATH_DETAIL_MATRIX_MATRIX2_INL

// inl sanity check
#ifndef BIT_MATH_DETAIL_MATRIX_MATRIX2_HPP
# error "matrix2.inl included without first including declaration header matrix2.hpp"
#endif

//----------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------

template<typename T>
const bit::math::matrix2<T> bit::math::matrix2<T>::identity
  = bit::math::matrix2<T>(T(1), T(0), T(0), T(1));

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix2<T>::matrix2( const vector2<T>& v0,
                                                 const vector2<T>& v1 )
  noexcept
  : m_matrix {
      v0.x(), v0.y(),
      v1.x(), v1.y()
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix2<T>::matrix2( const value_type(&array)[4] )
  noexcept
  : m_matrix {
      array[0], array[1],
      array[2], array[3]
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix2<T>::matrix2( const value_type(&array)[2][2] )
  noexcept
  : m_matrix {
      array[0][0], array[0][1],
      array[1][0], array[1][1]
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix2<T>::matrix2( value_type m00, value_type m01,
                                                 value_type m10, value_type m11 )
  noexcept
  : m_matrix {
      m00, m01,
      m10, m11
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::matrix2<T>::matrix2( const matrix2<U>& other )
  noexcept
  : m_matrix {
      other.m_matrix[0][0], other.m_matrix[0][1],
      other.m_matrix[1][0], other.m_matrix[1][1]
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::matrix2<T>::matrix2( matrix2<U>&& other )
  noexcept
  : m_matrix {
      std::move(other.m_matrix[0][0]), std::move(other.m_matrix[0][1]),
      std::move(other.m_matrix[1][0]), std::move(other.m_matrix[1][1])
    }
{

}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::reference
  bit::math::matrix2<T>::at( index_type r, index_type c )
{
  if( c >=2 || c < 0 || r >=2 || r < 0 )
    throw std::out_of_range("matrix2::at: index out of range");
  return get(r,c);
}


template<typename T>
inline constexpr typename bit::math::matrix2<T>::const_reference
  bit::math::matrix2<T>::at( index_type r, index_type c )
  const
{
  if( c >=2 || c < 0 || r >=2 || r < 0 )
    throw std::out_of_range("matrix2::at: index out of range");
  return get(r,c);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::reference
  bit::math::matrix2<T>::operator()( index_type r, index_type c )
  noexcept
{
  return get(r,c);
}


template<typename T>
inline constexpr typename bit::math::matrix2<T>::const_reference
  bit::math::matrix2<T>::operator()( index_type r, index_type c )
  const noexcept
{
  return get(r,c);
}

template<typename T>
inline constexpr bit::math::vector2<T>
  bit::math::matrix2<T>::row( index_type r )
  const noexcept
{
  return vector2<T>{ get(r,0), get(r,1) };
}

template<typename T>
inline constexpr bit::math::vector2<T>
  bit::math::matrix2<T>::column( index_type c )
  const noexcept
{
  return vector2<T>{ get(0,c), get(1,c) };
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::size_type
  bit::math::matrix2<T>::size()
  const noexcept
{
  return rows*columns;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::pointer
  bit::math::matrix2<T>::data()
  noexcept
{
  return std::addressof(get(0,0));
}

template<typename T>
inline constexpr typename bit::math::matrix2<T>::const_pointer
  bit::math::matrix2<T>::data()
  const noexcept
{
  return std::addressof(get(0,0));
}

//----------------------------------------------------------------------------
// Quantifiers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::value_type
  bit::math::matrix2<T>::determinant()
  const noexcept
{
  return (get(0,0) * get(1,1)) - (get(0,1) * get(1,0));
}

template<typename T>
inline constexpr typename bit::math::matrix2<T>::value_type
  bit::math::matrix2<T>::trace()
  const noexcept
{
  return (get(0,0) + get(1,1));
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix2<T>
  bit::math::matrix2<T>::inverse()
  const noexcept
{
  const auto det = determinant();

  if( det == value_type(0) ) return matrix2<T>::identity;

  const auto inv_det = (1.0 / det);
  return matrix2<T>(
     get(1,1) * inv_det, -get(1,0) * inv_det,
    -get(0,1) * inv_det,  get(0,0) * inv_det
  );
}

template<typename T>
inline constexpr bit::math::matrix2<T>
  bit::math::matrix2<T>::transposed()
  const noexcept
{
  return matrix2<T> {
    get(0,0), get(1,0),
    get(0,1), get(1,1)
  };
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::matrix2<T>::combine( const vector2<U>& vec )
  const noexcept
{
  auto result = vector2<std::common_type_t<T,U>>();

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
inline constexpr void bit::math::matrix2<T>::swap( matrix2<T>& other )
  noexcept
{
  using std::swap;
  for( auto r=0; r < rows; ++r ) {
    for( auto c=0; c < columns; ++c ) {
      swap(get(r,c),other.get(r,c));
    }
  }
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix2<T>& bit::math::matrix2<T>::invert()
  noexcept
{
  (*this) = inverse();
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::matrix2<T>& bit::math::matrix2<T>::transpose()
  noexcept
{
  using std::swap;

  swap(get(0,1),get(1,0));
  return (*this);
}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline bit::math::matrix2<T>&
  bit::math::matrix2<T>::operator+=( const matrix2<U>& rhs )
  noexcept
{
  for( auto r=0; r < rows; ++r) {
    for( auto c=0; c < columns; ++c ) {
      get(r,c) += rhs.get(r,c);
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix2<T>&
  bit::math::matrix2<T>::operator-=( const matrix2<U>& rhs )
  noexcept
{
  for( auto r=0; r < rows; ++r) {
    for( auto c=0; c < columns; ++c ) {
      get(r,c) -= rhs.get(r,c);
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix2<T>&
  bit::math::matrix2<T>::operator*=( const matrix2<U>& rhs )
  noexcept
{
  value_type result[rows][columns];

  for( auto r = 0; r < rows; ++r ) {
    for( auto c = 0; c < columns; ++c ) {

      auto sum = std::common_type_t<T,U>(0);

      for( auto r2 = 0; r2 < rows; ++r2 ) {
        sum += (get(r2,c) * rhs.get(r,r2));
      }
      result[r][c] = sum;
    }
  }

  // Copy result in
  for( auto i = 0; i < rows; ++i ) {
    for( auto j =0; j < columns; ++j ) {
      get(i,j) = result[i][j];
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix2<T>&
  bit::math::matrix2<T>::operator*=( U scalar )
  noexcept
{
  for( auto r=0; r < rows; ++r ) {
    for( auto c=0; c < columns; ++c ) {
      get(r,c) *= scalar;
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix2<T>&
  bit::math::matrix2<T>::operator/=( U scalar )
  noexcept
{
  auto inv = (1.0) / scalar;

  for( auto r=0; r < rows; ++r ) {
    for( auto c=0; c < columns; ++c ) {
      get(r,c) *= inv;
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::reference
  bit::math::matrix2<T>::get( index_type r, index_type c )
  noexcept
{
  return m_matrix[r][c];
}

template<typename T>
inline constexpr typename bit::math::matrix2<T>::const_reference
  bit::math::matrix2<T>::get( index_type r, index_type c )
  const noexcept
{
  return m_matrix[r][c];
}


//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::math::swap( matrix2<T>& lhs, matrix2<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Free Operators
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::matrix2<std::common_type_t<T,U>>
  bit::math::operator+( const matrix2<T>& lhs, const matrix2<U>& rhs )
  noexcept
{
  return matrix2<std::common_type_t<T,U>>(lhs)+=rhs;
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::matrix2<std::common_type_t<T,U>>
  bit::math::operator-( const matrix2<T>& lhs, const matrix2<U>& rhs )
  noexcept
{
  return matrix2<std::common_type_t<T,U>>(lhs)-=rhs;
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::matrix2<std::common_type_t<T,U>>
  bit::math::operator*( const matrix2<T>& lhs, const matrix2<U>& rhs )
  noexcept
{
  return matrix2<std::common_type_t<T,U>>(lhs)*=rhs;
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::operator*( const vector2<T>& lhs, const matrix2<U>& rhs )
  noexcept
{
  return rhs.combine(lhs);
}

//------------------------------------------------------------------------

template<typename T, typename U, std::enable_if_t<std::is_arithmetic<T>::value>*>
constexpr bit::math::matrix2<std::common_type_t<T,U>>
  bit::math::operator*( T lhs, const matrix2<U>& rhs )
  noexcept
{
  return matrix2<std::common_type_t<T,U>>(rhs) *= lhs;
}

//------------------------------------------------------------------------

template<typename T, typename U, std::enable_if_t<std::is_arithmetic<U>::value>*>
constexpr bit::math::matrix2<std::common_type_t<T,U>>
  bit::math::operator*( const matrix2<T>& lhs, U rhs )
  noexcept
{
  return matrix2<std::common_type_t<T,U>>(lhs) *= rhs;
}


#endif /* BIT_MATH_DETAIL_MATRIX_MATRIX2_INL */
