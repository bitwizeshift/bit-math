#ifndef BIT_MATH_DETAIL_VECTOR_INL
#define BIT_MATH_DETAIL_VECTOR_INL

#ifndef BIT_MATH_VECTOR_HPP
# error "vector.inl included without first including declaration header vector.hpp"
#endif

//----------------------------------------------------------------------------
// Detail: Vector Casting
//----------------------------------------------------------------------------

namespace bit { namespace math { namespace detail {

template<typename T, typename U>
struct vector_caster<vector2<T>,vector2<U>>
{
  static constexpr vector2<T> cast( const vector2<U>& from )
    noexcept
  {
    return vector2<T>( from );
  }
};

template<typename T, typename U>
struct vector_caster<vector3<T>,vector2<U>>
{
  static constexpr vector3<T> cast( const vector2<U>& from )
    noexcept
  {
    return vector3<T>( from.x(), from.y(), T(0) );
  }
};

template<typename T, typename U>
struct vector_caster<vector4<T>,vector2<U>>
{
  static constexpr vector4<T> cast( const vector2<U>& from )
    noexcept
  {
    return vector4<T>( from.x(), from.y(), T(0), T(0) );
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct vector_caster<vector2<T>,vector3<U>>
{
  static constexpr vector2<T> cast( const vector3<U>& from )
    noexcept
  {
    return vector2<T>( from.x(), from.y() );
  }
};

template<typename T, typename U>
struct vector_caster<vector3<T>,vector3<U>>
{
  static constexpr vector3<T> cast( const vector3<U>& from )
    noexcept
  {
    return vector3<T>( from );
  }
};

template<typename T, typename U>
struct vector_caster<vector4<T>,vector3<U>>
{
  static constexpr vector4<T> cast( const vector3<U>& from )
    noexcept
  {
    return vector4<T>( from.x(), from.y(), from.z(), T(0) );
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct vector_caster<vector2<T>,vector4<U>>
{
  static constexpr vector2<T> cast( const vector4<U>& from )
    noexcept
  {
    return vector2<T>( from.x(), from.y() );
  }
};

template<typename T, typename U>
struct vector_caster<vector3<T>,vector4<U>>
{
  static constexpr vector3<T> cast( const vector4<U>& from )
    noexcept
  {
    return vector3<T>( from.x(), from.y(), from.z() );
  }
};

template<typename T, typename U>
struct vector_caster<vector4<T>,vector4<U>>
{
  static constexpr vector4<T> cast( const vector4<U>& from )
    noexcept
  {
    return vector4<T>( from );
  }
};

} } } // namespace bit::math::detail

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
