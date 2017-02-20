/**
 * \file matrix2.test.cpp
 *
 * \brief Unit tests for matrix2
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#include <bit/math/matrix.hpp>

#include <catch.hpp>

TEST_CASE("matrix2::matrix2()")
{
  auto mat1 = bit::math::matrix2<float>(
    {1,2},
    {3,4}
  );

  auto mat2 = bit::math::matrix2<float>(
    2, 0, 0, 2
  );

  mat1 *= mat2;

  REQUIRE( mat1(0,0) == 2.0f );
  REQUIRE( mat1(0,1) == 4.0f );
  REQUIRE( mat1(1,0) == 6.0f );
  REQUIRE( mat1(1,1) == 8.0f );
  REQUIRE( *(mat1.data()+2) == mat1(1,0) );
  REQUIRE(  (mat1.data()+2) == &mat1(1,0) );

}


