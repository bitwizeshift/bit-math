/**
 * \file quaternion.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

/*
 * Note: The mathematical logic in the quaternion class comes primarily
 *       from the OGRE3D Quaternion library. To avoid any accidental
 *       misrepresentation, the corresponding license is attached below:
 *
 * Copyright (c) 2000-2014 Torus Knot Software Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <bit/math/quaternion.hpp>

#include <stdexcept>

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

bit::math::quaternion::reference
  bit::math::quaternion::at( index_type n )
{
  if( n >= 4 || n < 0 )
    throw std::out_of_range("quaternion::at: index out of range");

  return m_data[n];
}

bit::math::quaternion::const_reference
  bit::math::quaternion::at( index_type n )
  const
{
  if( n >= 4 || n < 0 )
    throw std::out_of_range("quaternion::at: index out of range");

  return m_data[n];
}

//----------------------------------------------------------------------------

bit::math::vector3<bit::math::quaternion::value_type>
  bit::math::quaternion::x_axis()
  const noexcept
{
  const auto ty  = 2.0f * y();
  const auto tz  = 2.0f * z();
  const auto twy = ty * w();
  const auto twz = tz * w();
  const auto txy = ty * x();
  const auto txz = tz * x();
  const auto tyy = ty * y();
  const auto tzz = tz * z();

  return vector_type(1.0f - (tyy + tzz), txy + twz, txz - twy);
}

//----------------------------------------------------------------------------

bit::math::vector3<bit::math::quaternion::value_type>
  bit::math::quaternion::y_axis()
  const noexcept
{
  const auto tx  = 2.0f * x();
  const auto ty  = 2.0f * y();
  const auto tz  = 2.0f * z();
  const auto twx = tx * w();
  const auto twz = tz * w();
  const auto txx = tx * x();
  const auto txy = ty * x();
  const auto tyz = tz * y();
  const auto tzz = tz * z();

  return vector_type(txy - twz, 1.0f - (txx + tzz), tyz + twx);
}

//----------------------------------------------------------------------------

bit::math::vector3<bit::math::quaternion::value_type>
  bit::math::quaternion::z_axis()
  const noexcept
{
  const auto tx  = 2.0f * x();
  const auto ty  = 2.0f * y();
  const auto tz  = 2.0f * z();
  const auto twx = tx * w();
  const auto twy = ty * w();
  const auto txx = tx * x();
  const auto txz = tz * x();
  const auto tyy = ty * y();
  const auto tyz = tz * y();

  return vector_type(txz+twy, tyz-twx, 1.0f-(txx+tyy));
}

//----------------------------------------------------------------------------
// Extraction
//----------------------------------------------------------------------------

void bit::math::quaternion::extract_rotation_matrix( matrix3_type* rot )
  const noexcept
{
  const auto tx  = 2 * x();
  const auto ty  = 2 * y();
  const auto tz  = 2 * z();
  const auto twx = tx * w();
  const auto twy = ty * w();
  const auto twz = tz * w();
  const auto txx = tx * x();
  const auto txy = ty * x();
  const auto txz = tz * x();
  const auto tyy = ty * y();
  const auto tyz = tz * y();
  const auto tzz = tz * z();

  //--------------------------------------------------------------------------

  (*rot)(0,0) = 1.0 - (tyy + tzz);
  (*rot)(0,1) = txy - twz;
  (*rot)(0,2) = txz + twy;

  (*rot)(1,0) = txy + twz;
  (*rot)(1,1) = 1.0 - (txx + tzz);
  (*rot)(1,2) = tyz - twx;

  (*rot)(2,0) = txz - twy;
  (*rot)(2,1) = tyz + twx;
  (*rot)(2,2) = 1.0f - (txx + tyy);
}

//----------------------------------------------------------------------------

void bit::math::quaternion::extract_rotation_matrix( matrix4_type* rot )
  const noexcept
{
  const auto tx  = 2 * x();
  const auto ty  = 2 * y();
  const auto tz  = 2 * z();
  const auto twx = tx * w();
  const auto twy = ty * w();
  const auto twz = tz * w();
  const auto txx = tx * x();
  const auto txy = ty * x();
  const auto txz = tz * x();
  const auto tyy = ty * y();
  const auto tyz = tz * y();
  const auto tzz = tz * z();

  //--------------------------------------------------------------------------

  (*rot)(0,0) = 1.0 - (tyy + tzz);
  (*rot)(0,1) = txy - twz;
  (*rot)(0,2) = 0.0;
  (*rot)(0,3) = txz + twy;

  (*rot)(1,0) = txy + twz;
  (*rot)(1,1) = 1.0 - (txx + tzz);
  (*rot)(1,2) = 0.0;
  (*rot)(1,3) = tyz - twx;

  (*rot)(2,0) = 0.0;
  (*rot)(2,1) = 0.0;
  (*rot)(2,2) = 1.0;
  (*rot)(2,3) = 0.0;

  (*rot)(3,0) = txz - twy;
  (*rot)(3,1) = tyz + twx;
  (*rot)(3,2) = 0.0;
  (*rot)(3,3) = 1.0f - (txx + tyy);
}

//----------------------------------------------------------------------------

void bit::math::quaternion::extract_angle_axis( radian* angle,
                                                vector_type* axis )
  const noexcept
{
  const auto squared_length = x()*x() + y()*y() + z()*z();

  if( squared_length > 0.0 ){

    const auto inv_length = 1.0 / sqrt(squared_length);
    (*angle) = 2 * arccos( x() );
    axis->x() = x() * inv_length;
    axis->y() = y() * inv_length;
    axis->z() = z() * inv_length;

  }else{

    (*angle)  = radian(0.0);
    axis->x() = 1.0;
    axis->y() = 0.0;
    axis->z() = 0.0;

  }
}

void bit::math::quaternion::extract_angle_axis( degree* angle,
                                                vector_type* axis )
  const noexcept
{
  auto rad = radian();
  extract_angle_axis(&rad,axis);

  (*angle) = angle_cast<degree>(rad);
}

//----------------------------------------------------------------------------

void bit::math::quaternion::extract_axes( vector_type* x_axis,
                                          vector_type* y_axis,
                                          vector_type* z_axis )
  const noexcept
{
  auto mat = matrix3_type();
  extract_rotation_matrix(&mat);

  (*x_axis) = mat.row(0);
  (*y_axis) = mat.row(1);
  (*z_axis) = mat.row(2);

}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

void bit::math::quaternion::swap( quaternion& other )
  noexcept
{
  using std::swap;

  swap(m_data[0],other.m_data[0]);
  swap(m_data[1],other.m_data[1]);
  swap(m_data[2],other.m_data[2]);
  swap(m_data[3],other.m_data[3]);
}

bit::math::quaternion& bit::math::quaternion::normalize()
  noexcept
{
  const auto mag_inv = 1.0 / magnitude();

  for(auto i=0; i<4; ++i) {
    m_data[i] *= mag_inv;
  }
  return (*this);
}

bit::math::quaternion& bit::math::quaternion::invert()
  noexcept
{
  const auto mag = magnitude();
  if( mag > 0.0 ){
    const auto mag_inv = (1.0f) / mag;
    w() *=  mag_inv;
    x() *= -mag_inv;
    y() *= -mag_inv;
    z() *= -mag_inv;
  }else{
    // Return an invalid quaternion to signify that this is not invertable
    for(auto i=0; i<4; ++i) {
      m_data[i] = 0;
    }
  }
  return (*this);
}

//----------------------------------------------------------------------------
// Quantifiers
//----------------------------------------------------------------------------

bit::math::quaternion::value_type
  bit::math::quaternion::dot( const quaternion& rhs )
  const noexcept
{
  auto result = quaternion::value_type();
  for(auto i=0; i<4; ++i) {
    result += m_data[i] * rhs.m_data[i];
  }

  return result;
}

bit::math::quaternion::value_type bit::math::quaternion::magnitude()
  const noexcept
{
  return sqrt(dot(*this));
}

//----------------------------------------------------------------------------

bit::math::radian bit::math::quaternion::roll( reproject_axis_t reproject )
  const noexcept
{
  const auto ty  = 2 * y();
  const auto tz  = 2 * z();
  const auto twz = tz * w();
  const auto txy = ty * x();
  const auto tyy = ty * y();
  const auto tzz = tz * z();

  return arctan2(txy+twz, 1 - (tyy + tzz));
}

bit::math::radian bit::math::quaternion::roll()
  const noexcept
{
  return arctan2(2*(x()*y() + w()*z()), w()*w() + x()*x() - y()*y() - z()*z());
}

//----------------------------------------------------------------------------

bit::math::radian bit::math::quaternion::pitch( reproject_axis_t )
  const noexcept
{
  const auto tx  = 2 * x();
  const auto tz  = 2 * z();
  const auto twx = tx * w();
  const auto txx = tx * x();
  const auto tyz = tz * y();
  const auto tzz = tz * z();

  return arctan2(tyz + twx, 1 - (txx + tzz));
}

bit::math::radian bit::math::quaternion::pitch()
  const noexcept
{
  return arctan2(2*(y()*z() + w()*x()), w()*w() - x()*x() - y()*y() + z()*z());
}

//----------------------------------------------------------------------------

bit::math::radian bit::math::quaternion::yaw( reproject_axis_t )
  const noexcept
{
  const auto tx  = 2 * x();
  const auto ty  = 2 * y();
  const auto tz  = 2 * z();
  const auto twy = ty * w();
  const auto txx = tx * x();
  const auto txz = tz * x();
  const auto tyy = ty * y();

  return arctan2(txz + twy, 1 - (txx + tyy));

}

bit::math::radian bit::math::quaternion::yaw()
  const noexcept
{
  return arcsin(-2*(x()*z() - w()*y()));
}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

bit::math::quaternion&
  bit::math::quaternion::operator += ( const quaternion& rhs )
  noexcept
{
  for(auto i=0; i<4;++i) {
    m_data[i] += rhs[i];
  }

  return (*this);
}

bit::math::quaternion&
  bit::math::quaternion::operator -= ( const quaternion& rhs )
  noexcept
{
  for(auto i=0; i<4;++i) {
    m_data[i] -= rhs[i];
  }

  return (*this);
}

bit::math::quaternion&
  bit::math::quaternion::operator *= ( const quaternion& rhs )
  noexcept
{
  w() = w() * rhs.w() - x() * rhs.x() - y() * rhs.y() - z() * rhs.z();
  x() = w() * rhs.x() + x() * rhs.w() + y() * rhs.z() - z() * rhs.y();
  y() = w() * rhs.y() + y() * rhs.w() + z() * rhs.x() - x() * rhs.z();
  z() = w() * rhs.z() + z() * rhs.w() + x() * rhs.y() - y() * rhs.x();
  return (*this);
}

bit::math::quaternion&
  bit::math::quaternion::operator *= ( value_type rhs )
  noexcept
{
  for(auto i=0; i<4;++i) {
    m_data[i] *= rhs;
  }

  return (*this);
}

bit::math::quaternion&
  bit::math::quaternion::operator /= ( value_type rhs )
  noexcept
{
  const auto inv = 1.0 / rhs;

  for(auto i=0; i<4;++i) {
    m_data[i] *= inv;
  }

  return (*this);
}


bit::math::quaternion&
  bit::math::quaternion::operator /= ( const quaternion& rhs )
  noexcept
{
  (*this) *= rhs.inverse();

  return (*this);
}

//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

void bit::math::quaternion::from_angle_axis( radian angle,
                                             const vector_type& axis )
  noexcept
{
  const auto norm_axis = axis.normalized();

  auto half_angle = angle * 0.5f;
  auto result     = sin(half_angle);

  w() = cos( half_angle );
  x() = norm_axis.x() * result;
  y() = norm_axis.y() * result;
  z() = norm_axis.z() * result;
}

void bit::math::quaternion::from_rotation_matrix( const matrix3_type& rot )
  noexcept
{
  // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
  // article "Quaternion Calculus and Fast Animation".

  const auto trace = rot.trace();
  auto root = value_type();

  if(trace > 0.0){
    root = sqrt( trace + 1 );
    w() = 0.5 * root;
    root = 0.5 / root;
    x() = (rot(2,1) - rot(1,2)) * root;
    y() = (rot(0,2) - rot(2,0)) * root;
    z() = (rot(1,0) - rot(0,1)) * root;
  }else{
    static const index_type s_next[3] = { 1, 2, 0 };
    value_type* apk_quat[3] = { &x(), &y(), &z() };
    size_t i, j, k;

    i = 0;
    if ( rot(1,1) > rot(0,0) ){
      i = 1;
    }
    if ( rot(2,2) > rot(i,i) ){
      i = 2;
    }
    j = s_next[i];
    k = s_next[j];

    root = sqrt(rot(i,i) - rot(j,j) - rot(k,k) + 1.0);

    (*apk_quat[i]) = 0.5 * root;

    root = 0.5 / root;

    w() = (rot(k,j) - rot(j,k)) * root;
    (*apk_quat[j]) = (rot(j,i) + rot(i,j)) * root;
    (*apk_quat[k]) = (rot(k,i) + rot(i,k)) * root;
  }
}

void bit::math::quaternion::from_rotation_matrix( const matrix4_type& rot )
  noexcept
{
  from_rotation_matrix( matrix_cast<matrix3_type>(rot) );
}

//----------------------------------------------------------------------------

bit::math::quaternion::vector_type
  bit::math::operator * ( const quaternion& lhs,
                          const quaternion::vector_type& rhs )
  noexcept
{
  auto qvec = quaternion::vector_type(lhs.x(), lhs.y(), lhs.z());

  auto uv = qvec.cross(rhs);
  auto uuv = qvec.cross(uv);
  uv *= (2.0 * lhs.w());
  uuv *= 2.0;

  return (rhs + uv + uuv);
}

