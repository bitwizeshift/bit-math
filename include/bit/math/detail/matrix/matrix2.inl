#ifndef BIT_MATH_DETAIL_MATRIX_MATRIX2_INL
#define BIT_MATH_DETAIL_MATRIX_MATRIX2_INL


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
      other.m_matrix[0], other.m_matrix[1],
      other.m_matrix[2], other.m_matrix[3]
    }
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::matrix2<T>::matrix2( matrix2<U>&& other )
  noexcept
  : m_matrix {
      other.m_matrix[0], other.m_matrix[1],
      other.m_matrix[2], other.m_matrix[3]
    }
{

}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::reference
  bit::math::matrix2<T>::at( index_type c, index_type r )
{
  if( c >=2 || c < 0 || r >=2 || r < 0 )
    throw std::out_of_range("matrix2::at: index out of range");
  return get(c,r);
}


template<typename T>
inline constexpr typename bit::math::matrix2<T>::const_reference
  bit::math::matrix2<T>::at( index_type c, index_type r )
  const
{
  if( c >=2 || c < 0 || r >=2 || r < 0 )
    throw std::out_of_range("matrix2::at: index out of range");
  return get(c,r);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix_proxy<T>
  bit::math::matrix2<T>::operator[]( index_type c )
  noexcept
{
  return matrix_proxy<T>( get_row(c) );
}


template<typename T>
inline constexpr typename bit::math::matrix_proxy<const T>
  bit::math::matrix2<T>::operator[]( index_type c )
  const noexcept
{
  return matrix_proxy<const T>( get_row(c) );
}

template<typename T>
inline constexpr bit::math::vector2<T>
  bit::math::matrix2<T>::row( index_type r )
  const noexcept
{
  return vector2<T>{ get(0,r), get(1,r) };
}

template<typename T>
inline constexpr bit::math::vector2<T>
  bit::math::matrix2<T>::column( index_type c )
  const noexcept
{
  return vector2<T>{ get(c,0), get(c,1) };
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::size_type
  bit::math::matrix2<T>::size()
  const noexcept
{
  return 4;
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::pointer
  bit::math::matrix2<T>::data()
  noexcept
{
  return m_matrix;
}

template<typename T>
inline constexpr typename bit::math::matrix2<T>::const_pointer
  bit::math::matrix2<T>::data()
  const noexcept
{
  return m_matrix;
}

//----------------------------------------------------------------------------
// Quantifiers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::value_type
  bit::math::matrix2<T>::determinant()
  const noexcept
{
  return (m_matrix[0] * m_matrix[3]) - (m_matrix[1] * m_matrix[2]);
}

template<typename T>
inline constexpr typename bit::math::matrix2<T>::value_type
  bit::math::matrix2<T>::trace()
  const noexcept
{
  return (m_matrix[0] + m_matrix[3]);
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
    m_matrix[3]  * inv_det, -m_matrix[2] * inv_det,
    -m_matrix[1] * inv_det, m_matrix[0]  * inv_det
  );
}

template<typename T>
inline constexpr bit::math::matrix2<T>
  bit::math::matrix2<T>::transposed()
  const noexcept
{
  return matrix2<T> {
    m_matrix[0], m_matrix[2],
    m_matrix[1], m_matrix[3]
  };
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
constexpr bit::math::vector2<std::common_type_t<T,U>>
  bit::math::matrix2<T>::combine( const vector2<U>& vec )
  const noexcept
{
  return vector2<std::common_type_t<T,U>>(
    vec.x() * m_matrix[0] + vec.y() * m_matrix[1],
    vec.x() * m_matrix[2] + vec.y() * m_matrix[3]
  );
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
inline constexpr void bit::math::matrix2<T>::swap( matrix2<T>& other )
  noexcept
{
  using std::swap;
  for(auto i=0; i < 4; ++i) {
    swap(m_matrix[i],other.m_matrix[i]);
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

  swap(m_matrix[1],m_matrix[2]);
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
  for(auto i=0; i < 4; ++i) {
    m_matrix[i] += rhs.m_matrix[i];
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix2<T>&
  bit::math::matrix2<T>::operator-=(const matrix2<U>& rhs)
  noexcept
{
  for(auto i=0; i < 4; ++i) {
    m_matrix[i] -= rhs.m_matrix[i];
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix2<T>&
  bit::math::matrix2<T>::operator*=(const matrix2<U>& rhs)
  noexcept
{
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix2<T>&
  bit::math::matrix2<T>::operator*=(U scalar)
  noexcept
{
  for(auto i=0; i < 4; ++i) {
    m_matrix[i] *= scalar;
  }
  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
bit::math::matrix2<T>&
  bit::math::matrix2<T>::operator/=(U scalar)
  noexcept
{
  auto inv = (1.0) / scalar;

  for(auto i=0; i < 4; ++i) {
    m_matrix[i] *= inv;
  }
  return (*this);
}

//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::pointer
  bit::math::matrix2<T>::get_row( index_type c )
  noexcept
{
  return (m_matrix + (2 * c));
}


template<typename T>
inline constexpr typename bit::math::matrix2<T>::const_pointer
  bit::math::matrix2<T>::get_row( index_type c )
  const noexcept
{
  return (m_matrix + (2 * c));
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr typename bit::math::matrix2<T>::reference
  bit::math::matrix2<T>::get( index_type c, index_type r )
  noexcept
{
  return *(m_matrix + (2 * c) + r);
}

template<typename T>
inline constexpr typename bit::math::matrix2<T>::const_reference
  bit::math::matrix2<T>::get( index_type c, index_type r )
  const noexcept
{
  return *(m_matrix + (2 * c) + r);
}


//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

template<typename T>
inline void bit::math::swap( matrix2<T>& lhs, matrix2<T>& rhs )
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


#endif /* BIT_MATH_DETAIL_MATRIX_MATRIX2_INL */
