#ifndef BIT_MATH_DETAIL_CLAMPED_INL
#define BIT_MATH_DETAIL_CLAMPED_INL

#ifndef BIT_MATH_CLAMPED_HPP
# error "clamped.inl included without first including declaration header clamped.hpp"
#endif


//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::clamped<T>::clamped( const T& value )
  noexcept
  : m_value( value >= T(1) ? T(1) : value <= T(0) ? T(0) : value )
{

}

template<typename T>
inline constexpr bit::math::clamped<T>::clamped( T&& value )
  noexcept
  : m_value( value >= T(1) ? T(1) : value <= T(0) ? T(0) : std::move(value) )
{

}

//----------------------------------------------------------------------------

template<typename T>
template<typename U>
inline constexpr bit::math::clamped<T>::clamped( const clamped<U>& other )
  noexcept
  : m_value( other.m_value )
{
  // This can assume it's already clamped between [0..1]
}

template<typename T>
template<typename U>
inline constexpr bit::math::clamped<T>::clamped( clamped<U>&& other )
  noexcept
  : m_value( std::move(other.m_value) )
{
  // This can assume it's already clamped between [0..1]
}

//----------------------------------------------------------------------------
// Conversion
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::clamped<T>::operator T()
  const noexcept
{
  return m_value;
}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::clamped<T>&
  bit::math::clamped<T>::operator+=( const clamped& rhs )
  noexcept
{
  m_value = clamped(m_value + static_cast<T>(rhs));

  return (*this);
}

template<typename T>
template<typename U>
inline constexpr bit::math::clamped<T>&
  bit::math::clamped<T>::operator+=( U&& scalar )
  noexcept
{
  m_value = clamped(m_value + std::forward<U>(scalar));

  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::clamped<T>&
  bit::math::clamped<T>::operator-=( const clamped& rhs )
  noexcept
{
  m_value = clamped(m_value - static_cast<T>(rhs));

  return (*this);
}

template<typename T>
template<typename U>
inline constexpr bit::math::clamped<T>&
  bit::math::clamped<T>::operator-=( U&& scalar )
  noexcept
{
  m_value = clamped(m_value - std::forward<U>(scalar));

  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::clamped<T>&
  bit::math::clamped<T>::operator*=( const clamped& rhs )
  noexcept
{
  m_value = clamped(m_value * static_cast<T>(rhs));

  return (*this);
}

template<typename T>
template<typename U>
inline constexpr bit::math::clamped<T>&
  bit::math::clamped<T>::operator*=( U&& scalar )
  noexcept
{
  m_value = clamped(m_value * std::forward<U>(scalar));

  return (*this);
}

//----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::math::clamped<T>&
  bit::math::clamped<T>::operator/=( const clamped& rhs )
  noexcept
{
  m_value = clamped(m_value / static_cast<T>(rhs));

  return (*this);
}

template<typename T>
template<typename U>
inline constexpr bit::math::clamped<T>&
  bit::math::clamped<T>::operator/=( U&& scalar )
  noexcept
{
  m_value = clamped(m_value / std::forward<U>(scalar));

  return (*this);
}

//----------------------------------------------------------------------------
// Operators
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator+( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(lhs) += rhs);
}

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator+( T&& lhs, const clamped<U>& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(rhs) += std::forward<T>(lhs));
}

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator+( const clamped<T>& lhs, U&& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(lhs) += std::forward<U>(rhs));
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator-( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(lhs) -= rhs);
}

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator-( T&& lhs, const clamped<U>& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(rhs) -= std::forward<T>(lhs));
}

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator-( const clamped<T>& lhs, U&& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(lhs) -= std::forward<U>(rhs));
}
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator*( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(lhs) *= rhs);
}

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator*( T&& lhs, const clamped<U>& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(rhs) *= std::forward<T>(lhs));
}

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator*( const clamped<T>& lhs, U&& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(lhs) *= std::forward<U>(rhs));
}
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator/( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(lhs) /= rhs);
}

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator/( T&& lhs, const clamped<U>& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(rhs) /= std::forward<T>(lhs));
}

template<typename T, typename U>
inline constexpr bit::math::clamped<std::common_type_t<T,U>>
  bit::math::operator/( const clamped<T>& lhs, U&& rhs )
  noexcept
{
  return (clamped<std::common_type_t<T,U>>(lhs) /= std::forward<U>(rhs));
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool
  bit::math::operator==( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return static_cast<T>(lhs)==static_cast<U>(rhs);
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool
  bit::math::operator!=( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return static_cast<T>(lhs)!=static_cast<U>(rhs);
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool
  bit::math::operator<( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return static_cast<T>(lhs)<static_cast<U>(rhs);
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool
  bit::math::operator>( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return static_cast<T>(lhs)>static_cast<U>(rhs);
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool
  bit::math::operator<=( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return static_cast<T>(lhs)<=static_cast<U>(rhs);
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bool
  bit::math::operator>=( const clamped<T>& lhs, const clamped<U>& rhs )
  noexcept
{
  return static_cast<T>(lhs)>=static_cast<U>(rhs);
}
#endif /* BIT_MATH_DETAIL_CLAMPED_INL */
