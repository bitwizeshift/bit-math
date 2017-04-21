#ifndef BIT_MATH_DETAIL_INTERPOLATION_INL
#define BIT_MATH_DETAIL_INTERPOLATION_INL

//----------------------------------------------------------------------------
// Interpolation
//----------------------------------------------------------------------------

template<typename V0, typename V1, typename T, typename Func>
inline constexpr std::common_type_t<V0,V1,T>
  bit::math::interpolate( const V0& v0, const V1& v1, const T& t, Func func  )
  noexcept
{
  auto r = func(t);
  return v0 * (1 - r) + v1 * r;
}

//----------------------------------------------------------------------------

template<typename V0, typename V1, typename T>
inline constexpr std::common_type_t<V0,V1,T>
  bit::math::linear( const V0& v0, const V1& v1, const T& t )
  noexcept
{
  return v0 * (1 - t) + v1 * t;
}


template<typename V0, typename V1, typename T>
inline constexpr std::common_type_t<V0,V1,T>
  bit::math::quadratic( const V0& v0, const V1& v1, const T& t )
  noexcept
{
  return linear(v0,v1,t*t);
}


template<typename V0, typename V1, typename T>
inline constexpr std::common_type_t<V0,V1,T>
  bit::math::cubic( const V0& v0, const V0& v1, const T& t )
  noexcept
{
  return linear(v0,v1,t*t*t);
}


template<typename V0, typename V1, typename T>
inline constexpr std::common_type_t<V0,V1,T>
  bit::math::quartic( const V0& v0, const V0& v1, const T& t )
  noexcept
{
  return linear(v0,v1,t*t*t*t);
}


template<typename V0, typename V1, typename T>
inline constexpr std::common_type_t<V0,V1,T>
  bit::math::quintic( const V0& v0, const V0& v1, const T& t )
  noexcept
{
  return linear(v0,v1,t*t*t*t*t);
}

//----------------------------------------------------------------------------

template<typename V0, typename V1, typename T>
inline std::common_type_t<V0,V1,T>
  bit::math::circular( const V0& v0, const V0& v1, const T& t )
  noexcept
{
  return linear(v0, v1, (1.0 - sqrt(1.0 - (t*t))));
}

//----------------------------------------------------------------------------

template<typename V0, typename V1, typename T>
inline std::common_type_t<V0,V1,T>
  bit::math::half_cosine( const V0& v0, const V0& v1, const T& t )
  noexcept
{
  return linear(v0, v1, (0.5 - cos(t * half_pi<std::common_type_t<V0,V1,T>>())*0.5));
}


template<typename V0, typename V1, typename T>
inline std::common_type_t<V0,V1,T>
  bit::math::cosine( const V0& v0, const V0& v1, const T& t )
  noexcept
{
  return linear(v0, v1, (1.0 - cos(t * pi<std::common_type_t<V0,V1,T>>())));
}

//----------------------------------------------------------------------------

template<typename V0, typename V1, typename T>
inline std::common_type_t<V0,V1,T>
  bit::math::half_sine( const V0& v0, const V0& v1, const T& t )
  noexcept
{
  return linear(v0, v1, (0.5 - sin(t * half_pi<std::common_type_t<V0,V1,T>>())*0.5));
}


template<typename V0, typename V1, typename T>
inline std::common_type_t<V0,V1,T>
  bit::math::sine( const V0& v0, const V0& v1, const T& t )
  noexcept
{
  return linear(v0, v1, (1.0 - sin(t * pi<std::common_type_t<V0,V1,T>>())));
}

//----------------------------------------------------------------------------

template<typename V00, typename V10, typename V01, typename V11, typename Tx, typename Ty>
inline constexpr std::common_type_t<V00,V10,V01,V11,Tx,Ty>
  bit::math::bilinear( const V00& v00, const V10 v10, const V01& v01,
                       const V11& v11, const Tx& tx, const Ty& ty )
  noexcept
{
  return linear( linear(v00,v10,tx), linear(v01,v11,tx), ty );
}

#endif /* BIT_MATH_DETAIL_INTERPOLATION_INL */
