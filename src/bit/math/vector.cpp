/**
 * \file vector.cpp
 *
 * \brief Implementation file for the vector headers
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/math/vector.hpp>

#ifdef BIT_MATH_DOUBLE_PRECISION

template class bit::math::vector2<double>;
template class bit::math::vector3<double>;
template class bit::math::vector4<double>;

#else

template class bit::math::vector2<float>;
template class bit::math::vector3<float>;
template class bit::math::vector4<float>;

#endif
