#ifndef BIT_MATH_DETAIL_MATRIX_INL
#define BIT_MATH_DETAIL_MATRIX_INL

#ifndef BIT_MATH_MATRIX_HPP
# error "matrix.inl included without first including declaration header matrix.hpp"
#endif

//----------------------------------------------------------------------------
// Casts
//----------------------------------------------------------------------------

template<typename To, typename From>
inline constexpr To bit::math::casts::matrix_cast(const From& from)
{
  return detail::matrix_caster<To,From>::cast(from);
}

//----------------------------------------------------------------------------
// matrix2 -> matrixN
//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::matrix_caster<bit::math::matrix2<T>, bit::math::matrix2<U>>
{
  static constexpr bit::math::matrix2<T> cast( const bit::math::matrix2<U>& rhs )
    noexcept
  {
    return matrix2<T>(rhs);
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::matrix_caster<bit::math::matrix3<T>, bit::math::matrix2<U>>
{
  static constexpr bit::math::matrix3<T> cast( const bit::math::matrix2<U>& rhs )
    noexcept
  {
    return matrix3<T>( rhs(0,0), rhs(0,1), T(0),
                       rhs(1,0), rhs(1,1), T(0),
                       T(0),     T(0),     T(1) );
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::matrix_caster<bit::math::matrix4<T>, bit::math::matrix2<U>>
{
  static constexpr bit::math::matrix4<T> cast( const bit::math::matrix2<U>& rhs )
    noexcept
  {
    return matrix3<T>( rhs(0,0), rhs(0,1), T(0), T(0),
                       rhs(1,0), rhs(1,1), T(0), T(0),
                       T(0),     T(0),     T(1), T(0),
                       T(0),     T(0),     T(0), T(1) );
  }
};

//----------------------------------------------------------------------------
// matrix3 -> matrixN
//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::matrix_caster<bit::math::matrix2<T>, bit::math::matrix3<U>>
{
  static constexpr bit::math::matrix2<T> cast( const bit::math::matrix3<U>& rhs )
    noexcept
  {
    return matrix2<T>( rhs(0,0), rhs(0,1),
                       rhs(1,0), rhs(1,1) );
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::matrix_caster<bit::math::matrix3<T>, bit::math::matrix3<U>>
{
  static constexpr bit::math::matrix3<T> cast( const bit::math::matrix3<U>& rhs )
    noexcept
  {
    return matrix3<T>(rhs);
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::matrix_caster<bit::math::matrix4<T>, bit::math::matrix3<U>>
{
  static constexpr bit::math::matrix4<T> cast( const bit::math::matrix3<U>& rhs )
    noexcept
  {
    return matrix4<T>( rhs(0,0), rhs(0,1), T(0), rhs(0,2),
                       rhs(1,0), rhs(1,1), T(0), rhs(1,2),
                       T(0),     T(0),     T(1), T(0),
                       rhs(2,0), rhs(2,1), T(0), rhs(2,2) );
  }
};

//----------------------------------------------------------------------------
// matrix4 -> matrixN
//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::matrix_caster<bit::math::matrix2<T>, bit::math::matrix4<U>>
{
  static constexpr bit::math::matrix2<T> cast( const bit::math::matrix4<U>& rhs )
    noexcept
  {
    return matrix2<T>( rhs(0,0), rhs(0,1),
                       rhs(1,0), rhs(1,1) );
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::matrix_caster<bit::math::matrix3<T>, bit::math::matrix4<U>>
{
  static constexpr bit::math::matrix3<T> cast( const bit::math::matrix4<U>& rhs )
    noexcept
  {
    return matrix3<T>( rhs(0,0), rhs(0,1), rhs(0,3),
                       rhs(1,0), rhs(1,1), rhs(1,3),
                       rhs(3,0), rhs(3,1), rhs(3,3) );
  }
};

//----------------------------------------------------------------------------

template<typename T, typename U>
struct bit::math::detail::matrix_caster<bit::math::matrix4<T>, bit::math::matrix4<U>>
{
  static constexpr bit::math::matrix4<T> cast( const bit::math::matrix4<U>& rhs )
    noexcept
  {
    return matrix4<T>(rhs);
  }
};

#endif /* BIT_MATH_DETAIL_MATRIX_INL */
