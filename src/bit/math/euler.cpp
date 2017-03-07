#include <bit/math/euler.hpp>

//----------------------------------------------------------------------------
// Extraction
//----------------------------------------------------------------------------

void bit::math::euler::extract_rotation_matrix( matrix3_type* rot )
  const noexcept
{
  const auto cosy = cos(m_yaw);
  const auto siny = sin(m_yaw);

  const auto sinp = sin(m_pitch);
  const auto cosp = cos(m_pitch);

  const auto sinr = sin(m_roll);
  const auto cosr = cos(m_roll);

  (*rot)(0,0) = (cosy * cosp);
  (*rot)(0,1) = (-cosy * sinp * sinr) - (siny * cosr);
  (*rot)(0,2) = (-cosy * sinp * cosr) + (siny * sinr);

  (*rot)(1,0) = (siny * cosp);
  (*rot)(1,1) = (-siny * sinp * sinr) + (cosy * cosr);
  (*rot)(1,2) = (-siny * sinp * cosr) - (cosy * sinr);

  (*rot)(2,0) = sinp;
  (*rot)(2,1) = (cosp * sinr);
  (*rot)(2,2) = (cosp * sinr);
}

void bit::math::euler::extract_rotation_matrix( matrix4_type* rot )
  const noexcept
{
  const auto cosy = cos(m_yaw);
  const auto siny = sin(m_yaw);

  const auto sinp = sin(m_pitch);
  const auto cosp = cos(m_pitch);

  const auto sinr = sin(m_roll);
  const auto cosr = cos(m_roll);

  (*rot)(0,0) = (cosy * cosp);
  (*rot)(0,1) = (-cosy * sinp * sinr) - (siny * cosr);
  (*rot)(0,2) = 0.0;
  (*rot)(0,3) = (-cosy * sinp * cosr) + (siny * sinr);

  (*rot)(1,0) = (siny * cosp);
  (*rot)(1,1) = (-siny * sinp * sinr) + (cosy * cosr);
  (*rot)(1,2) = 0.0;
  (*rot)(1,3) = (-siny * sinp * cosr) - (cosy * sinr);

  (*rot)(2,0) = 0.0;
  (*rot)(2,1) = 0.0;
  (*rot)(2,2) = 1.0;
  (*rot)(2,3) = 0.0;

  (*rot)(3,0) = sinp;
  (*rot)(3,1) = (cosp * sinr);
  (*rot)(3,2) = 0.0;
  (*rot)(3,3) = (cosp * sinr);
}

void bit::math::euler::extract_direction( vector_type* vec )
  const noexcept
{
  const auto cosy = cos(m_yaw);
  const auto siny = sin(m_yaw);

  const auto sinp = sin(m_pitch);
  const auto cosp = cos(m_pitch);

  const auto sinr = sin(m_roll);
  const auto cosr = cos(m_roll);

  vec->x() = (-cosy * sinp * sinr) - (siny * cosr);
  vec->y() = (-siny * sinp * sinr) + (cosy * cosr);
  vec->z() = ( cosp * sinr);
}

//----------------------------------------------------------------------------

void bit::math::euler::extract_axis( vector_type* forward,
                                     vector_type* right,
                                     vector_type* up )
  const noexcept
{
  auto q = quaternion(m_yaw,m_pitch,m_roll);

  (*forward) = (q * vector_type::neg_unit_z);
  (*right)   = (q * vector_type::unit_x);
  (*up)      = (q * vector_type::unit_y);
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

bit::math::euler& bit::math::euler::clamp( radian yaw, radian pitch, radian roll )
  noexcept
{
  clamp_angle(&m_yaw,yaw);
  clamp_angle(&m_pitch,pitch);
  clamp_angle(&m_roll,roll);

  return (*this);
}

//----------------------------------------------------------------------------

bit::math::euler& bit::math::euler::clamp_yaw( radian limit )
  noexcept
{
  clamp_angle(&m_yaw,limit);

  return (*this);
}

bit::math::euler& bit::math::euler::clamp_pitch( radian limit )
  noexcept
{
  clamp_angle(&m_pitch,limit);

  return (*this);
}

bit::math::euler& bit::math::euler::clamp_roll( radian limit )
  noexcept
{
  clamp_angle(&m_roll,limit);

  return (*this);
}

//----------------------------------------------------------------------------

void bit::math::euler::swap( euler& other )
  noexcept
{
  using std::swap;

  swap(m_yaw,other.m_yaw);
  swap(m_pitch,other.m_pitch);
  swap(m_roll,other.m_roll);
}

bit::math::euler& bit::math::euler::normalize()
  noexcept
{
  wrap_angle(&m_yaw);
  wrap_angle(&m_pitch);
  wrap_angle(&m_roll);
  return (*this);
}

bit::math::euler& bit::math::euler::rotate( radian roll,
                                            radian pitch,
                                            radian yaw )
  noexcept
{
  m_roll  += roll;
  m_pitch += pitch;
  m_yaw   += yaw;
  return (*this);
}

//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

void bit::math::euler::clamp_angle( radian* angle, radian clamp )
  noexcept
{
  if( (*angle) > clamp ) {
     (*angle) = clamp;
  } else if( (*angle) < -clamp ) {
     (*angle) = -clamp;
  }
}

void bit::math::euler::wrap_angle( radian* angle )
  noexcept
{
  const auto rad = radian(*angle);

  auto r = angle->value();

  if( rad < radian::neg_half_revolution ) {
    r = std::fmod( r, -two_pi<float_t>() );

    if( rad < radian::neg_half_revolution ) {
      (*angle) += radian::half_revolution;
    }
  } else if( rad > radian::half_revolution ) {
    r = std::fmod( r, two_pi<float_t>() );

    if( rad > radian::half_revolution ) {
      (*angle) -= radian::half_revolution;
    }
  }
}

//----------------------------------------------------------------------------

void bit::math::euler::from_quaternion( const quaternion& q )
  noexcept
{
  auto mat = matrix3_type();
  q.extract_rotation_matrix(&mat);

  from_rotation_matrix(mat);
}

//----------------------------------------------------------------------------

void bit::math::euler::from_rotation_matrix( const matrix3_type& rot )
  noexcept
{
  m_pitch = arcsin( -rot(1,2) );

  if( m_pitch < radian::quarter_revolution ) {
    if( m_pitch > radian::neg_quarter_revolution ) {
      m_yaw  = arctan2( rot(0,2), rot(2,2) );
      m_roll = arctan2( rot(1,0), rot(1,1) );
    } else { // not a unique solution
      auto ry = arctan2( -rot(0,1), rot(0,0) );

      m_roll  = radian(0.0);
      m_yaw   = m_roll - ry;
    }
  } else { // not a unique solution
    auto ry = arctan2( -rot(0,1), rot(0,0) );

    m_roll  = radian(0.0);
    m_yaw   = ry - m_roll;
  }
}

void bit::math::euler::from_rotation_matrix( const matrix4_type& rot )
  noexcept
{
  m_pitch = arcsin( -rot(1,3) );

  if( m_pitch < radian::quarter_revolution ) {
    if( m_pitch > radian::neg_quarter_revolution ) {
      m_yaw  = arctan2( rot(0,3), rot(3,3) );
      m_roll = arctan2( rot(1,0), rot(1,1) );
    } else { // not a unique solution
      auto ry = arctan2( -rot(0,1), rot(0,0) );

      m_roll  = radian(0.0);
      m_yaw   = m_roll - ry;
    }
  } else { // not a unique solution
    auto ry = arctan2( -rot(0,1), rot(0,0) );

    m_roll  = radian(0.0);
    m_yaw   = ry - m_roll;
  }
}

//----------------------------------------------------------------------------
// Free Functions
//----------------------------------------------------------------------------

void bit::math::swap( euler& lhs, euler& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Operators
//----------------------------------------------------------------------------

bit::math::quaternion bit::math::operator * ( const euler& lhs, const euler& rhs )
  noexcept
{
  return quaternion( lhs.yaw(), lhs.pitch(), lhs.roll() ) *
         quaternion( rhs.yaw(), rhs.pitch(), rhs.roll() );
}
