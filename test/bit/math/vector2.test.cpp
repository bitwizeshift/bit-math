/**
 * \file vector2.test.cpp
 *
 * \brief Unit tests for vector2
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#include <bit/math/vector.hpp>

#include "../../catch.hpp"

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

TEST_CASE("vector2::vector2<T>( value_type, value_type )", "[ctor]")
{
  auto x = 3.14f;
  auto y = 1.57f;
  auto vec = bit::math::vector2<float>{x,y};

  SECTION("Initializes x and y components")
  {
    SECTION("x contains specified x value")
    {
      REQUIRE( vec.x() == x );
    }
    SECTION("y contains specified y value")
    {
      REQUIRE( vec.y() == y );
    }
  }
}

TEST_CASE("vector2::vector2<T>( const vector2<U>& )" "[ctor]")
{
  auto x = 3.14f;
  auto y = 1.57f;
  auto vec = bit::math::vector2<float>{x,y};

  auto vec2 = bit::math::vector2<int>{vec};

  SECTION("Initializes x and y components")
  {
    SECTION("x contains specified x value")
    {
      REQUIRE( vec2.x() == (int) x );
    }
    SECTION("y contains specified y value")
    {
      REQUIRE( vec2.y() == (int) y );
    }
  }
}

TEST_CASE("vector2::vector2<T>( vector2<U>&& )", "[ctor]")
{
  auto x = 3.14f;
  auto y = 1.57f;
  auto vec = bit::math::vector2<float>{x,y};

  auto vec2 = bit::math::vector2<int>{ std::move(vec) };

  SECTION("Initializes x and y components")
  {
    SECTION("x contains specified x value")
    {
      REQUIRE( vec2.x() == (int) x );
    }
    SECTION("y contains specified y value")
    {
      REQUIRE( vec2.y() == (int) y );
    }
  }
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

TEST_CASE("vector2::size()", "[observers]")
{
  auto vec = bit::math::vector2<float>(0,0);

  SECTION("Has size 2")
  {
    REQUIRE( vec.size() == 2 );
  }
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

TEST_CASE("vector2::at( index_type )", "[observers]")
{
  auto vec = bit::math::vector2<int>(42,1024);

  SECTION("Throws when out of range")
  {
    SECTION("Index < 0")
    {
      REQUIRE_THROWS_AS(vec.at(-1),std::logic_error);
    }
    SECTION("Index > size()")
    {
      REQUIRE_THROWS_AS(vec.at(vec.size()),std::logic_error);
    }
  }
  SECTION("Retrieves entry at index")
  {
    SECTION("Index 0 retrieves x()")
    {
      REQUIRE( vec[0] == vec.x() );
    }
    SECTION("Index 1 retrieves y()")
    {
      REQUIRE( vec[1] == vec.y() );
    }
  }
}

TEST_CASE("vector2::operator[]( index_type )", "[observers]")
{
  auto vec = bit::math::vector2<int>(42,1024);

  SECTION("Retrieves entry at index")
  {
    SECTION("Index 0 retrieves x()")
    {
      REQUIRE( vec[0] == vec.x() );
    }
    SECTION("Index 1 retrieves y()")
    {
      REQUIRE( vec[1] == vec.y() );
    }
  }
}

//----------------------------------------------------------------------------
// Quantifiers
//----------------------------------------------------------------------------

TEST_CASE("vector2::dot( vector2<U> )", "[quantifiers]")
{
  auto vec1 = bit::math::vector2<float>{ 1.0, 2.0 };
  auto vec2 = bit::math::vector2<int>{ 2, 1 };

  SECTION("Dot product returns sub of multiples")
  {
    REQUIRE( vec1.dot(vec2) == 4.0f );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("vector2::cross( vector2<U> )", "[quantifiers]")
{
  auto vec1 = bit::math::vector2<float>{ 1.0, 2.0 };
  auto vec2 = bit::math::vector2<int>{ 1, 2 };

  SECTION("Cross product returns 0 for perpendicular vectors")
  {
    REQUIRE( vec1.cross(vec2) == 0.0f );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("vector2::magnitude()", "[quantifiers]")
{
  // pythagorean triple (3,4,5)
  auto vec1 = bit::math::vector2<float>{ 3.0, 4.0 };

  SECTION("Dot product returns sub of multiples")
  {
    REQUIRE( vec1.magnitude() == 5.0f );
  }
}
