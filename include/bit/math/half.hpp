/**
 * \file half.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_HALF_HPP
#define BIT_MATH_HALF_HPP

#include <cstdint> // std::uint16_t, std::uint32_t
#include <limits>  // std::numeric_limits
#include <climits> // CHAR_BIT
#include <type_traits> // std::enable_if, std::is_numeric

// This can *only* work with IEE 754 floating points. Anything other than this
// will fail. All units must be in terms of 8-bit bytes, and the standard
// integer types must be precisely the correct size

static_assert( std::numeric_limits<float>::is_iec559, "This code requires IEEE-754 floats" );
static_assert( CHAR_BIT == 8, "Bytes must be 8 bits" );
static_assert( sizeof(std::uint16_t) == 2, "uint16_t must be exactly 2 bytes");
static_assert( sizeof(std::uint32_t) == 4, "uint32_t must be exactly 4 bytes");
static_assert( sizeof(std::int32_t) == 4, "int32_t must be exactly 4 bytes");

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    ///
    ///
    ///
    //////////////////////////////////////////////////////////////////////////
    class half
    {
      //----------------------------------------------------------------------
      // Constructors / Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs a half with an undefined value
      constexpr half() noexcept;

      /// \brief Constructs a half from a given floating point value
      ///
      /// \param f the float to copy
      half( float f ) noexcept;

      /// \brief Copy-constructs a half from another half
      ///
      /// \param other the other half to copy
      half( const half& other ) noexcept = default;

      /// \brief Move-constructs a half from another half
      ///
      /// \param other the other half to move
      half( half&& other ) noexcept = default;

      //----------------------------------------------------------------------

      /// \brief Assigns a floating point value \p f to the given half
      ///
      /// \param f the float to assign
      /// \return reference to \c (*this)
      half& operator=( float f ) noexcept;

      /// \brief Copy-assigns a half
      ///
      /// \param other the half to copy
      /// \return reference to \c (*this)
      half& operator=( const half& other ) noexcept = default;

      /// \brief Move-assigns a half
      ///
      /// \param other the half to move
      /// \return reference to \c (*this)
      half& operator=( half&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Mutators
      //----------------------------------------------------------------------
    public:

      void swap( half& rhs ) noexcept;

      //----------------------------------------------------------------------
      // Casting
      //----------------------------------------------------------------------
    public:

      /// \brief Converts this \ref half to a float implicitly
      operator float() const noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      half& operator+=( float rhs ) noexcept;
      half& operator+=( const half& rhs ) noexcept;

      half& operator-=( float rhs ) noexcept;
      half& operator-=( const half& rhs ) noexcept;

      half& operator*=( float rhs ) noexcept;
      half& operator*=( const half& rhs ) noexcept;

      half& operator/=( float rhs ) noexcept;
      half& operator/=( const half& rhs ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      std::uint16_t m_bits;

      friend bool operator==( const half&, const half& ) noexcept;
      friend bool operator<( const half&, const half& ) noexcept;

    };

    //------------------------------------------------------------------------
    // Free Operators (Comparison)
    //------------------------------------------------------------------------

    bool operator==( const half& lhs, const half& rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator==( const half& lhs, Arithmetic rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator==( Arithmetic lhs, const half& rhs) noexcept;

    bool operator!=( const half& lhs, const half& rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator!=( const half& lhs, Arithmetic rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator!=( Arithmetic lhs, const half& rhs) noexcept;

    bool operator<( const half& lhs, const half& rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator<( const half& lhs, Arithmetic rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator<( Arithmetic lhs, const half& rhs) noexcept;

    bool operator>( const half& lhs, const half& rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator>( const half& lhs, Arithmetic rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator>( Arithmetic lhs, const half& rhs) noexcept;

    bool operator<=( const half& lhs, const half& rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator<=( const half& lhs, Arithmetic rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator<=( Arithmetic lhs, const half& rhs) noexcept;

    bool operator>=( const half& lhs, const half& rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator>=( const half& lhs, Arithmetic rhs) noexcept;
    template<typename Arithmetic, typename = std::enable_if_t<std::is_arithmetic<Arithmetic>::value>>
    bool operator>=( Arithmetic lhs, const half& rhs) noexcept;

    //------------------------------------------------------------------------
    // Free Operators (Application)
    //------------------------------------------------------------------------

    half operator+(const half& lhs, const half& rhs) noexcept;

    // handle type-promotion...

    float operator+(const half& lhs, float rhs) noexcept;
    float operator+(float lhs, const half& rhs) noexcept;

    double operator+(const half& lhs, double rhs) noexcept;
    double operator+(double lhs, const half& rhs) noexcept;

    long double operator+(const half& lhs, long double rhs) noexcept;
    long double operator+(long double lhs, const half& rhs) noexcept;

    // handle arbitrary integral types

    template<typename Integral, typename = std::enable_if_t<std::is_integral<Integral>::value>>
    half operator+(const half& lhs, Integral rhs) noexcept;

    template<typename Integral, typename = std::enable_if_t<std::is_integral<Integral>::value>>
    half operator+(Integral lhs, const half& rhs) noexcept;

    //------------------------------------------------------------------------

    half operator-(const half& lhs, const half& rhs) noexcept;


    float operator-(const half& lhs, float rhs) noexcept;
    float operator-(float lhs, const half& rhs) noexcept;

    double operator-(const half& lhs, double rhs) noexcept;
    double operator-(double lhs, const half& rhs) noexcept;

    long double operator-(const half& lhs, long double rhs) noexcept;
    long double operator-(long double lhs, const half& rhs) noexcept;

    template<typename Integral, typename = std::enable_if_t<std::is_integral<Integral>::value>>
    half operator-(const half& lhs, Integral rhs) noexcept;

    template<typename Integral, typename = std::enable_if_t<std::is_integral<Integral>::value>>
    half operator-(Integral lhs, const half& rhs) noexcept;

    //------------------------------------------------------------------------

    half operator*(const half& lhs, const half& rhs) noexcept;

    float operator*(const half& lhs, float rhs) noexcept;
    float operator*(float lhs, const half& rhs) noexcept;

    double operator*(const half& lhs, double rhs) noexcept;
    double operator*(double lhs, const half& rhs) noexcept;

    long double operator*(const half& lhs, long double rhs) noexcept;
    long double operator*(long double lhs, const half& rhs) noexcept;

    template<typename Integral, typename = std::enable_if_t<std::is_integral<Integral>::value>>
    half operator*(const half& lhs, Integral rhs) noexcept;

    template<typename Integral, typename = std::enable_if_t<std::is_integral<Integral>::value>>
    half operator*(Integral lhs, const half& rhs) noexcept;

    //------------------------------------------------------------------------

    half operator/(const half& lhs, const half& rhs) noexcept;

    float operator/(const half& lhs, float rhs) noexcept;
    float operator/(float lhs, const half& rhs) noexcept;

    double operator/(const half& lhs, double rhs) noexcept;
    double operator/(double lhs, const half& rhs) noexcept;

    long double operator/(const half& lhs, long double rhs) noexcept;
    long double operator/(long double lhs, const half& rhs) noexcept;

    template<typename Integral, typename = std::enable_if_t<std::is_integral<Integral>::value>>
    half operator/(const half& lhs, Integral rhs) noexcept;

    template<typename Integral, typename = std::enable_if_t<std::is_integral<Integral>::value>>
    half operator/(Integral lhs, const half& rhs) noexcept;

    //------------------------------------------------------------------------

    void swap(half& lhs, half& rhs) noexcept;

    /// \brief Converts a literal to a half
    ///
    /// Literals are identical to floating-point literals, but are directly
    /// converted to half types.
    ///
    /// \param str the string for the literal
    /// \param n the length of the string
    /// \return a half
    half operator""_h( long double f ) noexcept;

  } // namespace math
} // namespace bit

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

constexpr bit::math::half::half()
  noexcept
  : m_bits(0)
{
  // intentionally left uninitialized
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

inline void bit::math::half::swap( half& other )
  noexcept
{
  using std::swap;

  swap(m_bits, other.m_bits);
}

//-----------------------------------------------------------------------------
// Compound Operators
//-----------------------------------------------------------------------------

inline bit::math::half& bit::math::half::operator+=( float rhs )
  noexcept
{
  return (*this) += half(rhs);
}

inline bit::math::half& bit::math::half::operator-=( float rhs ) noexcept
{
  return (*this) -= half(rhs);
}

inline bit::math::half& bit::math::half::operator*=( float rhs ) noexcept
{
  return (*this) *= half(rhs);
}

inline bit::math::half& bit::math::half::operator/=( float rhs ) noexcept
{
  return (*this) /= half(rhs);
}


//------------------------------------------------------------------------
// Free Operators (Comparison)
//------------------------------------------------------------------------

inline bool bit::math::operator==( const half& lhs, const half& rhs )
  noexcept
{
  return lhs.m_bits == rhs.m_bits;
}

template<typename Arithmetic, typename>
inline bool bit::math::operator==( const half& lhs, Arithmetic rhs )
  noexcept
{
  return lhs == half(rhs);
}

template<typename Arithmetic, typename>
inline bool bit::math::operator==( Arithmetic lhs, const half& rhs )
  noexcept
{
  return half(lhs) == rhs;
}

//-----------------------------------------------------------------------------

inline bool bit::math::operator!=( const half& lhs, const half& rhs )
  noexcept
{
  return !(lhs==rhs);
}

template<typename Arithmetic, typename>
inline bool bit::math::operator!=( const half& lhs, Arithmetic rhs )
  noexcept
{
  return !(lhs==rhs);
}

template<typename Arithmetic, typename>
inline bool bit::math::operator!=( Arithmetic lhs, const half& rhs )
  noexcept
{
  return !(lhs==rhs);
}

//-----------------------------------------------------------------------------

inline bool bit::math::operator<( const half& lhs, const half& rhs )
  noexcept
{
  return lhs.m_bits < rhs.m_bits;
}

template<typename Arithmetic, typename>
inline bool bit::math::operator<( const half& lhs, Arithmetic rhs )
  noexcept
{
  return lhs < half(rhs);
}

template<typename Arithmetic, typename>
inline bool bit::math::operator<( Arithmetic lhs, const half& rhs )
  noexcept
{
  return half(lhs) < rhs;
}

//-----------------------------------------------------------------------------

inline bool bit::math::operator>( const half& lhs, const half& rhs )
  noexcept
{
  return rhs < lhs;
}

template<typename Arithmetic, typename>
inline bool bit::math::operator>( const half& lhs, Arithmetic rhs )
  noexcept
{
  return rhs < lhs;
}

template<typename Arithmetic, typename>
inline bool bit::math::operator>( Arithmetic lhs, const half& rhs )
  noexcept
{
  return rhs < lhs;
}

//-----------------------------------------------------------------------------

inline bool bit::math::operator<=( const half& lhs, const half& rhs )
  noexcept
{
  return !(rhs < lhs);
}

template<typename Arithmetic, typename>
inline bool bit::math::operator<=( const half& lhs, Arithmetic rhs )
  noexcept
{
  return !(rhs < lhs);
}

template<typename Arithmetic, typename>
inline bool bit::math::operator<=( Arithmetic lhs, const half& rhs )
  noexcept
{
  return !(rhs < lhs);
}

//-----------------------------------------------------------------------------

inline bool bit::math::operator>=( const half& lhs, const half& rhs )
  noexcept
{
  return !(lhs < rhs);
}

template<typename Arithmetic, typename>
inline bool bit::math::operator>=( const half& lhs, Arithmetic rhs )
  noexcept
{
  return !(lhs < rhs);
}

template<typename Arithmetic, typename>
inline bool bit::math::operator>=( Arithmetic lhs, const half& rhs )
  noexcept
{
  return !(lhs < rhs);
}

//-----------------------------------------------------------------------------
// Free Operators (Application)
//-----------------------------------------------------------------------------

inline bit::math::half bit::math::operator+( const half& lhs, const half& rhs )
  noexcept
{
  return half(lhs)+=rhs;
}

inline float bit::math::operator+( const half& lhs, float rhs )
  noexcept
{
  return static_cast<float>(lhs) + rhs;
}

inline float bit::math::operator+( float lhs, const half& rhs )
  noexcept
{
  return lhs + static_cast<float>(rhs);
}

inline double bit::math::operator+( const half& lhs, double rhs )
  noexcept
{
  return static_cast<float>(lhs) + rhs;
}

inline double bit::math::operator+( double lhs, const half& rhs )
  noexcept
{
  return lhs + static_cast<float>(rhs);
}

inline long double bit::math::operator+( const half& lhs, long double rhs )
  noexcept
{
  return static_cast<float>(lhs) + rhs;
}

inline long double bit::math::operator+( long double lhs, const half& rhs )
  noexcept
{
  return lhs + static_cast<float>(rhs);
}

template<typename Integral, typename>
bit::math::half bit::math::operator+( const half& lhs, Integral rhs )
  noexcept
{
  return half(lhs) += static_cast<float>(rhs);
}

template<typename Integral, typename>
bit::math::half bit::math::operator+(Integral lhs, const half& rhs) noexcept
{
  return half(rhs) += static_cast<float>(lhs);
}

//-----------------------------------------------------------------------------

inline bit::math::half bit::math::operator-( const half& lhs, const half& rhs )
  noexcept
{
  return half(lhs)-=rhs;
}

inline float bit::math::operator-( const half& lhs, float rhs )
  noexcept
{
  return static_cast<float>(lhs) - rhs;
}

inline float bit::math::operator-( float lhs, const half& rhs )
  noexcept
{
  return lhs - static_cast<float>(rhs);
}

inline double bit::math::operator-( const half& lhs, double rhs )
  noexcept
{
  return static_cast<float>(lhs) - rhs;
}

inline double bit::math::operator-( double lhs, const half& rhs )
  noexcept
{
  return lhs - static_cast<float>(rhs);
}

inline long double bit::math::operator-( const half& lhs, long double rhs )
  noexcept
{
  return static_cast<float>(lhs) - rhs;
}

inline long double bit::math::operator-( long double lhs, const half& rhs )
  noexcept
{
  return lhs - static_cast<float>(rhs);
}

template<typename Integral, typename>
inline bit::math::half bit::math::operator-( const half& lhs, Integral rhs )
  noexcept
{
  return half(lhs) -= static_cast<float>(rhs);
}

template<typename Integral, typename>
inline bit::math::half bit::math::operator-(Integral lhs, const half& rhs)
  noexcept
{
  return half(rhs) -= static_cast<float>(lhs);
}

//-----------------------------------------------------------------------------

inline bit::math::half bit::math::operator*( const half& lhs, const half& rhs )
  noexcept
{
  return half(lhs)*=rhs;
}

inline float bit::math::operator*( const half& lhs, float rhs )
  noexcept
{
  return static_cast<float>(lhs) * rhs;
}

inline float bit::math::operator*( float lhs, const half& rhs )
  noexcept
{
  return lhs * static_cast<float>(rhs);
}

inline double bit::math::operator*( const half& lhs, double rhs )
  noexcept
{
  return static_cast<float>(lhs) * rhs;
}

inline double bit::math::operator*( double lhs, const half& rhs )
  noexcept
{
  return lhs * static_cast<float>(rhs);
}

inline long double bit::math::operator*( const half& lhs, long double rhs )
  noexcept
{
  return static_cast<float>(lhs) * rhs;
}

inline long double bit::math::operator*( long double lhs, const half& rhs )
  noexcept
{
  return lhs * static_cast<float>(rhs);
}

template<typename Integral, typename>
inline bit::math::half bit::math::operator*( const half& lhs, Integral rhs )
  noexcept
{
  return half(lhs) *= static_cast<float>(rhs);
}

template<typename Integral, typename>
inline bit::math::half bit::math::operator*(Integral lhs, const half& rhs)
  noexcept
{
  return half(rhs) *= static_cast<float>(lhs);
}

//-----------------------------------------------------------------------------

inline bit::math::half bit::math::operator/( const half& lhs, const half& rhs )
  noexcept
{
  return half(lhs)/=rhs;
}

inline float bit::math::operator/( const half& lhs, float rhs )
  noexcept
{
  return static_cast<float>(lhs) / rhs;
}

inline float bit::math::operator/( float lhs, const half& rhs )
  noexcept
{
  return lhs / static_cast<float>(rhs);
}

inline double bit::math::operator/( const half& lhs, double rhs )
  noexcept
{
  return static_cast<float>(lhs) / rhs;
}

inline double bit::math::operator/( double lhs, const half& rhs )
  noexcept
{
  return lhs / static_cast<float>(rhs);
}

inline long double bit::math::operator/( const half& lhs, long double rhs )
  noexcept
{
  return static_cast<float>(lhs) / rhs;
}

inline long double bit::math::operator/( long double lhs, const half& rhs )
  noexcept
{
  return lhs / static_cast<float>(rhs);
}

template<typename Integral, typename>
inline bit::math::half bit::math::operator/( const half& lhs, Integral rhs )
  noexcept
{
  return half(lhs) /= static_cast<float>(rhs);
}

template<typename Integral, typename>
inline bit::math::half bit::math::operator/(Integral lhs, const half& rhs)
  noexcept
{
  return half(rhs) /= static_cast<float>(lhs);
}

//-----------------------------------------------------------------------------

inline void bit::math::swap( half& lhs, half& rhs )
  noexcept
{
  lhs.swap(rhs);
}

inline bit::math::half bit::math::operator ""_h( long double f )
  noexcept
{
  return half( static_cast<float>(f) );
}

#endif /* BIT_MATH_HALF_HPP */
