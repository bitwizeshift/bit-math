#ifndef BIT_MATH_DETAIL_TRANSFORM_INL
#define BIT_MATH_DETAIL_TRANSFORM_INL


//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline bit::math::transform::transform()
  noexcept
  : m_transform(mat4::identity),
    m_rotation{},
    m_translation(0.0,0.0,0.0),
    m_scale(1.0,1.0,1.0),
    m_is_dirty(false)
{

}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

inline void bit::math::transform::translate( float_t x, float_t y, float_t z )
  noexcept
{
  translate({x,y,z});
}

inline void bit::math::transform::translate( const vec3& translation )
  noexcept
{
  m_translation += translation;
  m_is_dirty = true;
}


inline void bit::math::transform::translate_x( float_t x )
  noexcept
{
  m_translation.x() += x;
  m_is_dirty = true;
}

inline void bit::math::transform::translate_y( float_t y )
  noexcept
{
  m_translation.y() += y;
  m_is_dirty = true;
}

inline void bit::math::transform::translate_z( float_t z )
  noexcept
{
  m_translation.z() += z;
  m_is_dirty = true;
}

//----------------------------------------------------------------------

inline void bit::math::transform::set_position( float_t x, float_t y, float_t z )
  noexcept
{
  set_position({x,y,z});
}

inline void bit::math::transform::set_position( const vec3& position )
  noexcept
{
  m_translation = position;
  m_is_dirty = true;
}


inline void bit::math::transform::set_position_x( float_t x )
  noexcept
{
  m_translation.x() = x;
  m_is_dirty = true;
}

inline void bit::math::transform::set_position_y( float_t y )
  noexcept
{
  m_translation.y() = y;
  m_is_dirty = true;
}

inline void bit::math::transform::set_position_z( float_t z )
  noexcept
{
  m_translation.z() = z;
  m_is_dirty = true;
}

//----------------------------------------------------------------------------

inline void bit::math::transform::rotate( radian yaw, radian pitch, radian roll )
  noexcept
{
  rotate( quaternion{ yaw, pitch, roll } );
}

inline void bit::math::transform::rotate( radian angle, const vec3& axis )
  noexcept
{
  rotate( quaternion{ angle, axis } );
}

inline void bit::math::transform::rotate( const quaternion& rotation )
  noexcept
{
  m_rotation += rotation;
  m_is_dirty = true;
}

inline void bit::math::transform::rotate_yaw( radian angle )
  noexcept
{
  rotate( quaternion{ angle, {}, {} } );
}

inline void bit::math::transform::rotate_pitch( radian angle )
  noexcept
{
  rotate( quaternion{ {}, angle, {} } );
}

inline void bit::math::transform::rotate_roll( radian angle )
  noexcept
{
  rotate( quaternion{ {}, {}, angle } );
}

//----------------------------------------------------------------------------

inline void bit::math::transform::set_rotation( radian yaw, radian pitch, radian roll )
  noexcept
{
  set_rotation( quaternion{ yaw, pitch, roll } );
}

inline void bit::math::transform::set_rotation( radian angle, const vec3& axis )
  noexcept
{
  set_rotation( quaternion{ angle, axis } );
}

inline void bit::math::transform::set_rotation( const quaternion& quaternion )
  noexcept
{
  m_rotation = quaternion;
  m_is_dirty = true;
}

inline void bit::math::transform::set_angle_roll( radian angle )
  noexcept
{
  set_rotation( quaternion{ angle, {}, {} } );
}

inline void bit::math::transform::set_angle_pitch( radian angle )
  noexcept
{
  set_rotation( quaternion{ {}, angle, {} } );
}

inline void bit::math::transform::set_angle_yaw( radian angle )
  noexcept
{
  set_rotation( quaternion{ {}, {}, angle } );
}

//----------------------------------------------------------------------------

inline void bit::math::transform::scale( float_t x, float_t y, float_t z )
  noexcept
{
  scale( {x,y,z} );
}

inline void bit::math::transform::scale( vec3 scale )
  noexcept
{
  m_scale += scale;
  m_is_dirty = true;
}


inline void bit::math::transform::scale_x( float_t scale )
  noexcept
{
  m_scale.x() += scale;
  m_is_dirty = true;
}

inline void bit::math::transform::scale_y( float_t scale )
  noexcept
{
  m_scale.y() += scale;
  m_is_dirty = true;
}

inline void bit::math::transform::scale_z( float_t scale )
  noexcept
{
  m_scale.z() += scale;
  m_is_dirty = true;

}

//----------------------------------------------------------------------

inline void bit::math::transform::set_scale( float_t x, float_t y, float_t z )
  noexcept
{
  set_scale( {x,y,z} );
}

inline void bit::math::transform::set_scale( vec3 scale )
  noexcept
{
  m_scale = scale;
  m_is_dirty = true;
}

inline void bit::math::transform::set_scale_x( float_t scale )
  noexcept
{
  m_scale.x() = scale;
  m_is_dirty = true;
}

inline void bit::math::transform::set_scale_y( float_t scale )
  noexcept
{
  m_scale.y() = scale;
  m_is_dirty = true;
}

inline void bit::math::transform::set_scale_z( float_t scale )
  noexcept
{
  m_scale.z() = scale;
  m_is_dirty = true;
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

inline const bit::math::vec3& bit::math::transform::scale()
  const noexcept
{
  return m_scale;
}

inline const bit::math::vec3& bit::math::transform::position()
  const noexcept
{
  return m_translation;
}

inline const bit::math::quaternion& bit::math::transform::rotation()
  const noexcept
{
  return m_rotation;
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::transform::scale_x()
  const noexcept
{
  return m_scale.x();
}

inline bit::math::float_t bit::math::transform::scale_y()
  const noexcept
{
  return m_scale.y();
}

inline bit::math::float_t bit::math::transform::scale_z()
  const noexcept
{
  return m_scale.z();
}

//----------------------------------------------------------------------------

inline bit::math::float_t bit::math::transform::x()
  const noexcept
{
  return m_translation.x();
}

inline bit::math::float_t bit::math::transform::y()
  const noexcept
{
  return m_translation.y();
}

inline bit::math::float_t bit::math::transform::z()
  const noexcept
{
  return m_translation.z();
}

//----------------------------------------------------------------------------

inline bit::math::radian bit::math::transform::roll()
  const noexcept
{
  return m_rotation.roll();
}

inline bit::math::radian bit::math::transform::pitch()
  const noexcept
{
  return m_rotation.pitch();
}

inline bit::math::radian bit::math::transform::yaw()
  const noexcept
{
  return m_rotation.yaw();
}

//----------------------------------------------------------------------------

inline const bit::math::mat4& bit::math::transform::matrix()
  const noexcept
{
  if( m_is_dirty ) update();
  return m_transform;
}

//----------------------------------------------------------------------------
// Private Member Functions
//----------------------------------------------------------------------------

inline void bit::math::transform::update()
  const noexcept
{
  auto rotation    = bit::math::mat4();
  auto translation = bit::math::mat4::identity;
  auto scale       = bit::math::mat4::identity;

  m_rotation.extract_rotation_matrix(&rotation);

  translation(3,0) = m_translation.x();
  translation(3,1) = m_translation.y();
  translation(3,2) = m_translation.z();

  scale(1,1) = m_scale.x();
  scale(2,2) = m_scale.y();
  scale(3,3) = m_scale.z();

  m_transform = translation * rotation * scale;
  m_is_dirty  = false;
}

#endif /* BIT_MATH_DETAIL_TRANSFORM_INL */
