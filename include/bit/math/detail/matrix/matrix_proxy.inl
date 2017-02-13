#ifndef BIT_MATH_DETAIL_MATRIX_MATRIX_PROXY_INL
#define BIT_MATH_DETAIL_MATRIX_MATRIX_PROXY_INL

template<typename T>
inline constexpr bit::math::matrix_proxy<T>::matrix_proxy( T* ptr )
  noexcept
  : m_data(ptr)
{

}

template<typename T>
inline constexpr typename bit::math::matrix_proxy<T>::reference
  bit::math::matrix_proxy<T>::operator[]( index_type row )
  const noexcept
{
  return m_data[row];
}
#endif /* BIT_MATH_DETAIL_MATRIX_MATRIX_PROXY_INL */
