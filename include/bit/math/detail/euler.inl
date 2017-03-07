#ifndef BIT_MATH_DETAIL_EULER_INL
#define BIT_MATH_DETAIL_EULER_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline constexpr bit::math::euler::euler( radian roll, radian pitch, radian yaw )
  noexcept
  : m_roll(roll),
    m_pitch(pitch),
    m_yaw(yaw)
{

}

//----------------------------------------------------------------------------

inline bit::math::euler::euler( const quaternion& q )
  noexcept
{
  from_quaternion(q);
}

//----------------------------------------------------------------------------

inline bit::math::euler::euler( const matrix3_type& mat )
  noexcept
{
  from_rotation_matrix(mat);
}

inline bit::math::euler::euler( const matrix4_type& mat )
  noexcept
{
  from_rotation_matrix(mat);
}

//----------------------------------------------------------------------------
// Assignment
//----------------------------------------------------------------------------

inline bit::math::euler& bit::math::euler::operator=( const quaternion& q )
  noexcept
{
  from_quaternion(q);
  return (*this);
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

inline constexpr bit::math::radian bit::math::euler::yaw()
  const noexcept
{
  return m_yaw;
}

//----------------------------------------------------------------------------

inline constexpr bit::math::radian bit::math::euler::pitch()
  const noexcept
{
  return m_pitch;
}

//----------------------------------------------------------------------------

inline constexpr bit::math::radian bit::math::euler::roll()
  const noexcept
{
  return m_roll;
}

//----------------------------------------------------------------------------

inline std::tuple<bit::math::euler::vector_type,bit::math::euler::vector_type,bit::math::euler::vector_type>
  bit::math::euler::axes()
  const noexcept
{
  auto forward = vector_type();
  auto right   = vector_type();
  auto up      = vector_type();

  extract_axis(&forward, &right, &up);

  return std::make_tuple(forward,right,up);
}

//----------------------------------------------------------------------------

inline bit::math::euler bit::math::euler::normalized()
  const noexcept
{
  return euler(*this).normalize();
}

//----------------------------------------------------------------------------

inline bit::math::euler::vector_type bit::math::euler::direction()
  const noexcept
{
  vector_type vec;
  extract_direction(&vec);

  return vec;
}

//----------------------------------------------------------------------------

inline bit::math::euler::matrix3_type bit::math::euler::rotation_matrix()
  const noexcept
{
  matrix3_type mat;
  extract_rotation_matrix(&mat);

  return mat;
}

inline bit::math::euler::operator bit::math::quaternion()
  const noexcept
{
  return quaternion(m_yaw,m_pitch,m_roll);
}


//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

inline bit::math::euler& bit::math::euler::operator += ( const euler& rhs )
  noexcept
{
  return rotate(rhs.roll(),rhs.pitch(),rhs.yaw());
}

inline bit::math::euler& bit::math::euler::operator -= ( const euler& rhs )
  noexcept
{
  return rotate(-rhs.roll(),-rhs.pitch(),-rhs.yaw());
}

//----------------------------------------------------------------------------

inline bit::math::euler& bit::math::euler::operator *= ( float_t scalar )
  noexcept
{
  m_roll *= scalar;
  m_pitch *= scalar;
  m_yaw *= scalar;
  return (*this);
}

inline bit::math::euler& bit::math::euler::operator /= ( float_t scalar )
  noexcept
{
  const auto scalar_inv = 1 / scalar;

  m_roll *= scalar_inv;
  m_pitch *= scalar_inv;
  m_yaw *= scalar_inv;
  return (*this);
}

//----------------------------------------------------------------------------
// Operators
//----------------------------------------------------------------------------

inline bit::math::euler bit::math::operator + ( const euler& lhs, const euler& rhs )
  noexcept
{
  return euler(lhs) += rhs;
}

inline bit::math::euler bit::math::operator - ( const euler& lhs, const euler& rhs )
  noexcept
{
  return euler(lhs) -= rhs;
}

//----------------------------------------------------------------------------

inline bit::math::euler bit::math::operator * ( const euler& lhs, float_t rhs )
  noexcept
{
  return euler(lhs) *= rhs;
}

inline bit::math::euler bit::math::operator * ( float_t lhs, const euler& rhs )
  noexcept
{
  return euler(rhs) *= lhs;
}

//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------

inline constexpr bool bit::math::operator==( const euler& lhs, const euler& rhs )
  noexcept
{
  return lhs.roll() == rhs.roll() &&
         lhs.pitch() == rhs.pitch() &&
         lhs.yaw() == rhs.yaw();
}

inline constexpr bool bit::math::operator!=( const euler& lhs, const euler& rhs )
  noexcept
{
  return !(lhs==rhs);
}

//----------------------------------------------------------------------------

inline constexpr bool bit::math::almost_equal( const euler& lhs, const euler& rhs )
  noexcept
{
  return almost_equal( lhs.roll(), rhs.roll() ) &&
         almost_equal( lhs.pitch(), rhs.pitch() ) &&
         almost_equal( lhs.yaw(), rhs.yaw() );
}

template<typename Arithmetic, std::enable_if<std::is_arithmetic<Arithmetic>::value>*>
inline constexpr bool bit::math::almost_equal( const euler& lhs, const euler& rhs, Arithmetic tolerance )
  noexcept
{
  return almost_equal( lhs.roll(), rhs.roll(), tolerance ) &&
         almost_equal( lhs.pitch(), rhs.pitch(), tolerance ) &&
         almost_equal( lhs.yaw(), rhs.yaw(), tolerance );
}

#endif /* BIT_MATH_DETAIL_EULER_INL */
