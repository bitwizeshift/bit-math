/*****************************************************************************
 * \file
 * \brief This header contains algorithms for simplex noise generation
 *****************************************************************************/

/*
  The MIT License (MIT)

  Bit Math Library.
  https://github.com/bitwizeshift/bit-math

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
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
