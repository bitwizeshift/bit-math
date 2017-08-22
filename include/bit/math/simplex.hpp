/**
 * \file simplex.hpp
 *
 * \brief This header contains algorithms for simplex noise generation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_SIMPLEX_HPP
#define BIT_MATH_SIMPLEX_HPP

// bit::map library
#include "vector.hpp" // bit::math::vector2, bit::math::vector3

#include <cassert> // assert

namespace bit {
  namespace math {
    namespace simplex {

      //----------------------------------------------------------------------
      // Raw Noise
      //----------------------------------------------------------------------

      /// \brief Generates 2-dimensional raw simplex noise
      ///
      /// \param x the x-coordinate
      /// \param y the y-coordinate
      /// \return the result of the raw noise
      float_t raw_noise( float_t x, float_t y ) noexcept;

      /// \brief Generates 3-dimensional raw simplex noise
      ///
      /// \param x the x-coordinate
      /// \param y the y-coordinate
      /// \param z the z-coordinate
      /// \return the result of the raw noise
      float_t raw_noise( float_t x, float_t y, float_t z ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Generates 2-dimensional raw simplex noise
      ///
      /// \param pos the 2-dimensional vector position
      /// \return the result of the raw noise
      float_t raw_noise( const vec2& pos ) noexcept;

      /// \brief Generates 3-dimensional raw simplex noise
      ///
      /// \param pos the 3-dimensional vector position
      /// \return the result of the raw noise
      float_t raw_noise( const vec3& pos ) noexcept;

      //----------------------------------------------------------------------
      // Raw Scaled Noise
      //----------------------------------------------------------------------

      float_t scaled_raw_noise( float_t low,
                                float_t high,
                                float_t x,
                                float_t y ) noexcept;

      float_t scaled_raw_noise( float_t low,
                                float_t high,
                                float_t x,
                                float_t y,
                                float_t z ) noexcept;

      //----------------------------------------------------------------------

      float_t scaled_raw_noise( float_t low, float_t high,
                                const vec2& pos ) noexcept;

      float_t scaled_raw_noise( float_t low, float_t high,
                                const vec3& pos ) noexcept;

      //----------------------------------------------------------------------
      // Octave Noise
      //----------------------------------------------------------------------

      float_t octave_noise( float_t octaves,
                            float_t persistence,
                            float_t scale,
                            float_t x,
                            float_t y ) noexcept;

      float_t octave_noise( float_t octaves,
                            float_t persistence,
                            float_t scale,
                            float_t x,
                            float_t y,
                            float_t z ) noexcept;

      //----------------------------------------------------------------------

      float_t octave_noise( float_t octaves,
                            float_t persistence,
                            float_t scale,
                            const vec2& pos ) noexcept;

      float_t octave_noise( float_t octaves,
                            float_t persistence,
                            float_t scale,
                            const vec3& pos ) noexcept;

      //----------------------------------------------------------------------
      // Scaled Octave Noise
      //----------------------------------------------------------------------

      float_t scaled_octave_noise( float_t octaves,
                                   float_t persistence,
                                   float_t scale,
                                   float_t low,
                                   float_t high,
                                   float_t x,
                                   float_t y ) noexcept;

      float_t scaled_octave_noise( float_t octaves,
                                   float_t persistence,
                                   float_t scale,
                                   float_t low,
                                   float_t high,
                                   float_t x,
                                   float_t y,
                                   float_t z ) noexcept;

      //----------------------------------------------------------------------

      float_t scaled_octave_noise( float_t octaves,
                                   float_t persistence,
                                   float_t scale,
                                   float_t low,
                                   float_t high,
                                   const vec2& pos ) noexcept;

      float_t scaled_octave_noise( float_t octaves,
                                   float_t persistence,
                                   float_t scale,
                                   float_t low,
                                   float_t high,
                                   const vec3& pos ) noexcept;

    } // namespace simplex
  } // namespace math
} // namespace bit

//----------------------------------------------------------------------------
// Raw Noise
//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::raw_noise( const vec2& pos )
  noexcept
{
  return raw_noise( pos.x(), pos.y() );
}

//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::raw_noise( const vec3& pos )
  noexcept
{
  return raw_noise( pos.x(), pos.y(), pos.z() );
}

//----------------------------------------------------------------------------
// Raw Scaled Noise
//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::scaled_raw_noise( float_t low, float_t high,
                                        float_t x, float_t y )
  noexcept
{
  assert( low < high && "Low must be less than high" );

  const auto c1 = ((high - low) * 0.5);
  const auto c2 = ((high + low) * 0.5);
  return c1 * raw_noise(x, y) + c2;
}

//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::scaled_raw_noise( float_t low, float_t high,
                                        float_t x, float_t y, float_t z )
  noexcept
{
  assert( low < high && "Low must be less than high" );

  const auto c1 = ((high - low) * 0.5);
  const auto c2 = ((high + low) * 0.5);
  return c1 * raw_noise(x, y, z) + c2;
}

//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::scaled_raw_noise( float_t low, float_t high,
                                        const vec2& pos )
  noexcept
{
  return scaled_raw_noise( low, high, pos.x(), pos.y() );
}

//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::scaled_raw_noise( float_t low, float_t high,
                                        const vec3& pos )
  noexcept
{
  return scaled_raw_noise( low, high, pos.x(), pos.y(), pos.z() );
}

//----------------------------------------------------------------------------
// Octave Noise
//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::octave_noise( float_t octaves,
                                    float_t persistence,
                                    float_t scale,
                                    const vec2& pos )
  noexcept
{
  return octave_noise( octaves, persistence, scale, pos.x(), pos.y() );
}

//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::octave_noise( float_t octaves,
                                    float_t persistence,
                                    float_t scale,
                                    const vec3& pos )
  noexcept
{
  return octave_noise( octaves, persistence, scale, pos.x(), pos.y(), pos.z() );
}

//----------------------------------------------------------------------------
// Scaled Octave Noise
//----------------------------------------------------------------------------


inline bit::math::float_t
  bit::math::simplex::scaled_octave_noise( float_t octaves,
                                           float_t persistence,
                                           float_t scale,
                                           float_t low,
                                           float_t high,
                                           float_t x,
                                           float_t y )
  noexcept
{
  assert( low < high && "Low must be less than high" );

  const auto c1 = ((high - low) * 0.5);
  const auto c2 = ((high + low) * 0.5);
  return c1 * octave_noise( octaves, persistence, scale, x, y ) + c2;
}

//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::scaled_octave_noise( float_t octaves,
                                           float_t persistence,
                                           float_t scale,
                                           float_t low,
                                           float_t high,
                                           float_t x,
                                           float_t y,
                                           float_t z )
  noexcept
{
  assert( low < high && "Low must be less than high" );

  const auto c1 = ((high - low) * 0.5);
  const auto c2 = ((high + low) * 0.5);
  return c1 * octave_noise( octaves, persistence, scale, x, y, z ) + c2;
}

//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::scaled_octave_noise( float_t octaves,
                                           float_t persistence,
                                           float_t scale,
                                           float_t low,
                                           float_t high,
                                           const vec2& pos )
  noexcept
{
  return scaled_octave_noise( octaves, persistence, scale,
                              low, high, pos.x(), pos.y() );
}

//----------------------------------------------------------------------------

inline bit::math::float_t
  bit::math::simplex::scaled_octave_noise( float_t octaves,
                                           float_t persistence,
                                           float_t scale,
                                           float_t low,
                                           float_t high,
                                           const vec3& pos )
  noexcept
{
  return scaled_octave_noise( octaves, persistence, scale,
                              low, high, pos.x(), pos.y(), pos.z() );
}


#endif /* BIT_MATH_SIMPLEX_HPP */
