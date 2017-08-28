/**
 * \file math.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#include <bit/math/angles.hpp>

#include <cassert>
#include <array>

//----------------------------------------------------------------------
// Public Static Members
//----------------------------------------------------------------------

const bit::math::degree
  bit::math::degree::revolution = degree(360);
const bit::math::degree
  bit::math::degree::half_revolution = degree(180);
const bit::math::degree
  bit::math::degree::quarter_revolution = degree(90);

const bit::math::degree
  bit::math::degree::neg_revolution = degree(-360);
const bit::math::degree
  bit::math::degree::neg_half_revolution = degree(-180);
const bit::math::degree
  bit::math::degree::neg_quarter_revolution = degree(-90);

//----------------------------------------------------------------------

const bit::math::radian
  bit::math::radian::revolution = radian( two_pi<bit::math::radian::value_type>() );
const bit::math::radian
  bit::math::radian::half_revolution = radian( pi<bit::math::radian::value_type>() );
const bit::math::radian
  bit::math::radian::quarter_revolution = radian( half_pi<bit::math::radian::value_type>() );

const bit::math::radian
  bit::math::radian::neg_revolution = radian( -two_pi<bit::math::radian::value_type>() );
const bit::math::radian
  bit::math::radian::neg_half_revolution = radian( -pi<bit::math::radian::value_type>() );
const bit::math::radian
  bit::math::radian::neg_quarter_revolution = radian( -half_pi<bit::math::radian::value_type>() );

//----------------------------------------------------------------------

const bit::math::gradian
  bit::math::gradian::revolution = gradian(400);
const bit::math::gradian
  bit::math::gradian::half_revolution = gradian(200);
const bit::math::gradian
  bit::math::gradian::quarter_revolution = gradian(100);

const bit::math::gradian
  bit::math::gradian::neg_revolution = gradian(-400);
const bit::math::gradian
  bit::math::gradian::neg_half_revolution = gradian(-200);
const bit::math::gradian
  bit::math::gradian::neg_quarter_revolution = gradian(-100);

#if BIT_MATH_CACHED_TRIG
# ifndef BIT_MATH_TRIG_TABLE_SIZE
#   define BIT_MATH_TRIG_TABLE_SIZE 1024
# endif
# ifndef BIT_MATH_INVERSE_TRIG_TABLE_SIZE
#   define BIT_MATH_INVERSE_TRIG_TABLE_SIZE 1024
# endif
# if BIT_MATH_TRIG_TABLE_SIZE <= 0
#   error "BIT_MATH_TRIG_TABLE_SIZE must be > 0"
# endif
# if BIT_MATH_INVERSE_TRIG_TABLE_SIZE <= 0
#   error "BIT_MATH_TRIG_TABLE_SIZE must be > 0"
# endif

// This is acquired from an externally generated *.cpp file
// through cmake.
namespace bit {
  namespace math {

    extern const std::array<float_t,BIT_MATH_TRIG_TABLE_SIZE> g_sin_table;

  } // namespace math
} // namespace bit

namespace {

  //--------------------------------------------------------------------------
  // Constants
  //--------------------------------------------------------------------------

  using sin_table_t = std::array<bit::math::float_t,BIT_MATH_TRIG_TABLE_SIZE>;

  const sin_table_t g_sin_table = {};

  constexpr auto g_table_size = BIT_MATH_TRIG_TABLE_SIZE;

  constexpr auto g_trig_factor = g_table_size / bit::math::two_pi<bit::math::float_t>();

} // anonymous namespace
#endif

//----------------------------------------------------------------------------
// Trig Lookups
//----------------------------------------------------------------------------

bit::math::float_t bit::math::cached::detail::sin_lookup( float_t angle )
  noexcept
{
#if BIT_MATH_CACHED_TRIG
  auto i = std::ptrdiff_t();

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
