/**
 * \file angles.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_ANGLES_HPP
#define BIT_MATH_ANGLES_HPP

#include "math.hpp"

#include "detail/angles/radian.hpp"
#include "detail/angles/degree.hpp"

namespace bit {
  namespace math {

    //------------------------------------------------------------------------
    // Literals
    //------------------------------------------------------------------------

    inline namespace literals {

      constexpr radian operator""_rad( long double angle ) noexcept;

      constexpr degree operator""_deg( long double angle ) noexcept;

    } // inline namespace literals

    //------------------------------------------------------------------------
    // Casting
    //------------------------------------------------------------------------

    inline namespace casts {

      /// \brief Performs a cast between angle types
      ///
      /// \tparam To the angle type to cast to
      /// \param from the angle to cast from
      /// \return the casted angle
      template<typename To, typename From>
      constexpr To angle_cast( From from ) noexcept;

      /// \brief Identity angle cast
      ///
      /// \tparam To the type to cast to
      /// \param from the angle to cast
      /// \return itself
      template<>
      constexpr radian angle_cast( radian angle ) noexcept;

      /// \brief Identity angle cast
      ///
      /// \tparam To the type to cast to
      /// \param from the angle to cast
      /// \return itself
      template<>
      constexpr degree angle_cast( degree angle ) noexcept;

      /// \brief Casts a \ref degree \p angle to a \ref radian
      ///
      /// \param angle the degree to cast to radians
      /// \return the angle in radians
      template<>
      constexpr radian angle_cast( degree angle ) noexcept;

      /// \brief Casts a \ref radian \p angle to a \ref degree
      ///
      /// \param angle the radian to cast to degrees
      /// \return the angle in degrees
      template<>
      constexpr degree angle_cast( radian angle ) noexcept;

    } // inline namespace casts

    //------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------

    radian round( radian rad ) noexcept;
    degree round( degree deg ) noexcept;

    radian trunc( radian rad ) noexcept;
    degree trunc( degree deg ) noexcept;

    radian ceil( radian rad ) noexcept;
    degree ceil( degree deg ) noexcept;

    radian floor( radian rad ) noexcept;
    degree floor( degree deg ) noexcept;

    radian abs( radian rad ) noexcept;
    degree abs( degree deg ) noexcept;

    //------------------------------------------------------------------------
    // Trig
    //------------------------------------------------------------------------

    namespace detail {

      float_t sin_lookup( float_t angle ) noexcept;

      float_t tan_lookup( float_t angle ) noexcept;

    } // namespace detail

    float_t cos( radian rad ) noexcept;
    float_t cos( degree deg ) noexcept;

    float_t sin( radian rad ) noexcept;
    float_t sin( degree deg ) noexcept;

    float_t tan( radian rad ) noexcept;
    float_t tan( degree deg ) noexcept;

    //------------------------------------------------------------------------

    float_t sec( radian rad ) noexcept;
    float_t sec( degree deg ) noexcept;

    float_t csc( radian rad ) noexcept;
    float_t csc( degree deg ) noexcept;

    float_t cot( radian rad ) noexcept;
    float_t cot( degree deg ) noexcept;

    //------------------------------------------------------------------------

    radian arccos( float_t f ) noexcept;
    radian arcsin( float_t f ) noexcept;
    radian arctan( float_t f ) noexcept;
    radian arctan2( float_t f1, float_t f2 ) noexcept;

    //------------------------------------------------------------------------
    // Table Trig
    //------------------------------------------------------------------------

    float_t tcos( radian rad ) noexcept;
    float_t tcos( degree deg ) noexcept;

    float_t tsin( radian rad ) noexcept;
    float_t tsin( degree deg ) noexcept;

    float_t ttan( radian rad ) noexcept;
    float_t ttan( degree deg ) noexcept;

    //------------------------------------------------------------------------
    // Inverse Table Trig
    //------------------------------------------------------------------------

    float_t tcot( radian rad ) noexcept;
    float_t tcot( degree deg ) noexcept;

    float_t tsec( radian rad ) noexcept;
    float_t tsec( degree deg ) noexcept;

    float_t tcsc( radian rad ) noexcept;
    float_t tcsc( degree deg ) noexcept;

  } // namespace math
} // namespace bit

#include "detail/angles.inl"

#endif /* BIT_MATH_ANGLES_HPP */
