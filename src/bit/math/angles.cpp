/**
 * \file math.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#include <bit/math/angles.hpp>

#include <cassert>

#ifndef BIT_MATH_TRIG_TABLE_SIZE
# define BIT_MATH_TRIG_TABLE_SIZE 4096
#endif

#define BIT_MATH_UNUSED(...) ((void) __VA_ARGS__)

namespace {

  //--------------------------------------------------------------------------
  // Constants
  //--------------------------------------------------------------------------
#ifdef BIT_MATH_CACHED_TRIG

  static bit::math::float_t g_sin_table[BIT_MATH_TRIG_TABLE_SIZE];
  static bit::math::float_t g_tan_table[BIT_MATH_TRIG_TABLE_SIZE];

#endif
#ifdef BIT_MATH_CACHED_INVERSE_TRIG

  static bit::math::float_t g_arcsin_table[BIT_MATH_TRIG_TABLE_SIZE];
  static bit::math::float_t g_arctan_table[BIT_MATH_TRIG_TABLE_SIZE];

#endif

  static const bit::math::float_t g_trig_factor = BIT_MATH_TRIG_TABLE_SIZE / bit::math::two_pi<float_t>();

  static const bit::math::float_t* calculate_trig_tables() noexcept;

  static const void* const g_table_ptr = calculate_trig_tables();

  //--------------------------------------------------------------------------
  // Free Functions
  //--------------------------------------------------------------------------

  // todo: Complete trig table mathematics
  const bit::math::float_t* calculate_trig_tables()
    noexcept
  {
#if !(defined(BIT_MATH_CACHED_TRIG) && defined(BIT_MATH_CACHED_INVERSE_TRIG))
    return nullptr;
#else
    for( std::size_t i=0; i < BIT_MATH_TRIG_TABLE_SIZE; ++i )
    {
# ifdef BIT_MATH_CACHED_TRIG

      bit::math::float_t angle
        = (bit::math::two_pi<float_t>() * i) / bit::math::float_t{BIT_MATH_TRIG_TABLE_SIZE};
      g_sin_table[i] = std::sin(angle);
      g_tan_table[i] = std::tan(angle);

# endif // BIT_MATH_CACHED_TRIG
# ifdef BIT_MATH_CACHED_INVERSE_TRIG

      // Create some input...
# endif // BIT_MATH_CACHED_INVERSE_TRIG
    }
    return g_sin_table;
#endif
  }
} // anonymous namespace

//----------------------------------------------------------------------------
// Trig Lookups
//----------------------------------------------------------------------------

bit::math::float_t bit::math::detail::sin_lookup( float_t angle )
  noexcept
{
#ifdef BIT_MATH_CACHED_TRIG
  BIT_MATH_UNUSED(g_table_ptr);

  std::ptrdiff_t i;

  if( angle >= 0 ){
    i = int(angle * g_trig_factor) % BIT_MATH_TRIG_TABLE_SIZE;
  } else {
    i = BIT_MATH_TRIG_TABLE_SIZE - (int(-angle * g_trig_factor) % BIT_MATH_TRIG_TABLE_SIZE) - 1;
  }
  return g_sin_table[i];
#else
  assert(false && "table-lookup not defined");
  return 0; // fake return statement to suppress warnings
#endif
}

//----------------------------------------------------------------------------

bit::math::float_t bit::math::detail::tan_lookup( float_t angle )
  noexcept
{
#ifdef BIT_MATH_CACHED_TRIG
  BIT_MATH_UNUSED(g_table_ptr);

  std::ptrdiff_t i = int(angle * g_trig_factor) % BIT_MATH_TRIG_TABLE_SIZE;
  return g_tan_table[i];
#else
  assert(false && "table-lookup not defined");
  return 0; // fake return statement to suppress warnings
#endif
}

