/**
 * \file vector.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_VECTOR_HPP
#define BIT_MATH_VECTOR_HPP

#include <utility>
#include <stdexcept>
#include <cstddef>
#include <cstdint>

#include "math.hpp"
#include "angles.hpp"

#include "detail/vector/vector2.hpp"
#include "detail/vector/vector3.hpp"
#include "detail/vector/vector4.hpp"

namespace bit {
  namespace math {

    template<typename T>
    class vector2;

    template<typename T>
    class vector3;

    template<typename T>
    class vector4;

    template<typename To, typename From>
    To vector_cast( const From& from );

    template<typename T, typename U>
    constexpr vector2<T> vector_cast( const vector2<U>& from ) noexcept;

    template<typename T, typename U>
    constexpr vector3<T> vector_cast( const vector3<U>& from ) noexcept;

    template<typename T, typename U>
    constexpr vector2<T> vector_cast( const vector3<U>& from ) noexcept;

    template<typename T, typename U>
    constexpr vector4<T> vector_cast( const vector4<U>& from ) noexcept;

    template<typename T, typename U>
    constexpr vector3<T> vector_cast( const vector4<U>& from ) noexcept;

    template<typename T, typename U>
    constexpr vector2<T> vector_cast( const vector4<U>& from ) noexcept;

  } // namespace math
} // namespace bit

//----------------------------------------------------------------------------
// Vector Casting
//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector2<T>
  bit::math::vector_cast( const vector2<U>& from )
  noexcept
{
  return vector2<T>{ from };
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector3<T>
  bit::math::vector_cast( const vector3<U>& from )
  noexcept
{
  return vector2<T>{ from };
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector2<T>
  bit::math::vector_cast( const vector3<U>& from )
  noexcept
{
  return vector2<T>{ from.x(), from.y() };
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector4<T>
  bit::math::vector_cast( const vector4<U>& from )
  noexcept
{
  return vector4<T>{ from };
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector3<T>
  bit::math::vector_cast( const vector4<U>& from )
  noexcept
{
  return vector3<T>{ from.x(), from.y(), from.z() };
}

//----------------------------------------------------------------------------

template<typename T, typename U>
inline constexpr bit::math::vector2<T>
  bit::math::vector_cast( const vector4<U>& from )
  noexcept
{
  return vector2<T>{ from.x(), from.y() };
}


#endif /* BIT_MATH_VECTOR_HPP */
