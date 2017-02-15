/**
 * \file matrix.cpp
 *
 * \brief Implementation file for the matrix headers
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/math/matrix.hpp>

#ifdef BIT_MATH_DOUBLE_PRECISION

template class bit::math::matrix2<double>;
template class bit::math::matrix3<double>;
template class bit::math::matrix4<double>;

#else

template class bit::math::matrix2<float>;
template class bit::math::matrix3<float>;
template class bit::math::matrix4<float>;

#endif


