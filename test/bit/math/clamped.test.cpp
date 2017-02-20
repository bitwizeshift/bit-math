/**
 * \file clamped.test.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#include <bit/math/clamped.hpp>

#include <catch.hpp>

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

TEST_CASE("clamped::clamped( const T& )", "[ctor]")
{
  SECTION("Clamps values above 0")
  {
    auto const c = bit::math::clamped<float>(1.5);

    REQUIRE( c == 1.0 );
  }

  SECTION("Clamps values below 0")
  {
    auto const c = bit::math::clamped<float>(-1.5);

    REQUIRE( c == 0.0 );
  }

  SECTION("Doesn't clamp values betwen (0,1)")
  {
    auto const c = bit::math::clamped<float>(0.5);

    REQUIRE( c == 0.5 );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("clamped::clamped( const clamped<U>& )", "[ctor]")
{
  SECTION("Constructs clamped from different type")
  {
    auto const a = bit::math::clamped<double>(0.25);
    auto const b = bit::math::clamped<float>(a);

    REQUIRE( a == b );
  }
}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

TEST_CASE("clamped::operator+=( const clamped& )", "[operators]")
{
  SECTION("Clamps values when the sum exceeds 1")
  {
    auto const a = bit::math::clamped<double>(0.75);
    auto b = bit::math::clamped<float>(0.75);

    b += a;

    REQUIRE( b == 1.0 );
  }

  SECTION("Doesn't clamp values when the sum is between 0 and 1")
  {
    auto const a = bit::math::clamped<double>(0.25);
    auto b = bit::math::clamped<float>(0.25);

    b += a;

    REQUIRE( b == 0.5 );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("clamped::operator-=( const clamped& )", "[operators]")
{
  SECTION("Doesn't clamp values when the difference is between 0 and 1")
  {

  }

  SECTION("Clamps values when the difference eludes 0")
  {

  }
}


//----------------------------------------------------------------------------

TEST_CASE("clamped::operator*=( const clamped& )", "[operators]")
{

}
