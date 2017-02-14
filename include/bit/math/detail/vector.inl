#ifndef BIT_MATH_DETAIL_VECTOR_INL
#define BIT_MATH_DETAIL_VECTOR_INL

#ifndef BIT_MATH_VECTOR_HPP
# error "vector.inl included without first including declaration header vector.hpp"
#endif

//----------------------------------------------------------------------------
// Detail: Vector Casting
//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::vector_caster<bit::math::vector2<T>,bit::math::vector2<U>>
{
  static constexpr bit::math::vector2<T> cast( const bit::math::vector2<U>& from )
    noexcept
  {
    return vector2<T>( from );
  }
};

template<typename T, typename U>
struct bit::math::detail::vector_caster<bit::math::vector3<T>,bit::math::vector2<U>>
{
  static constexpr bit::math::vector3<T> cast( const bit::math::vector2<U>& from )
    noexcept
  {
    return vector3<T>( from.x(), from.y(), T(0) );
  }
};

template<typename T, typename U>
struct bit::math::detail::vector_caster<bit::math::vector4<T>,bit::math::vector2<U>>
{
  static constexpr bit::math::vector4<T> cast( const bit::math::vector2<U>& from )
    noexcept
  {
    return vector4<T>( from.x(), from.y(), T(0), T(0) );
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::vector_caster<bit::math::vector2<T>,bit::math::vector3<U>>
{
  static constexpr bit::math::vector2<T> cast( const bit::math::vector3<U>& from )
    noexcept
  {
    return vector2<T>( from.x(), from.y() );
  }
};

template<typename T, typename U>
struct bit::math::detail::vector_caster<bit::math::vector3<T>,bit::math::vector3<U>>
{
  static constexpr bit::math::vector3<T> cast( const bit::math::vector3<U>& from )
    noexcept
  {
    return vector3<T>( from );
  }
};

template<typename T, typename U>
struct bit::math::detail::vector_caster<bit::math::vector4<T>,bit::math::vector3<U>>
{
  static constexpr bit::math::vector4<T> cast( const bit::math::vector3<U>& from )
    noexcept
  {
    return vector4<T>( from.x(), from.y(), from.z(), T(0) );
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::vector_caster<bit::math::vector2<T>,bit::math::vector4<U>>
{
  static constexpr bit::math::vector2<T> cast( const bit::math::vector4<U>& from )
    noexcept
  {
    return vector2<T>( from.x(), from.y() );
  }
};

template<typename T, typename U>
struct bit::math::detail::vector_caster<bit::math::vector3<T>,bit::math::vector4<U>>
{
  static constexpr bit::math::vector3<T> cast( const bit::math::vector4<U>& from )
    noexcept
  {
    return vector3<T>( from.x(), from.y(), from.z() );
  }
};

template<typename T, typename U>
struct bit::math::detail::vector_caster<bit::math::vector4<T>,bit::math::vector4<U>>
{
  static constexpr bit::math::vector4<T> cast( const bit::math::vector4<U>& from )
    noexcept
  {
    return vector4<T>( from );
  }
};

//----------------------------------------------------------------------------
// Vector Casting
//----------------------------------------------------------------------------

template<typename To, typename From>
inline constexpr To bit::math::casts::vector_cast( const From& from )
  noexcept
{
  return bit::math::detail::vector_caster<To,From>::cast(from);
}

#endif /* BIT_MATH_DETAIL_VECTOR_INL */
