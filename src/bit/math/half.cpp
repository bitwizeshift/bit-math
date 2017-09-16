/**
 * \file half.cpp
 *
 * \brief This file is a C++ adaptation of Mike Acton's branchless half
 *        implementation
 *
 * The majority of the implementation is in-tact, including the original
 * C-style functions. Only minor alterations to the naming and decorations of
 * the function have been made to preserve the original work.
 *
 * The full-license of the original code is listed below.
 */

// Branch-free implementation of half-precision (16 bit) floating point
// Copyright 2006 Mike Acton <macton@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE
//

#include <bit/math/half.hpp>

#include <cstring> // std::memcpy

namespace {

  std::uint32_t half_uint32_li( std::uint32_t a );
  std::uint32_t half_uint32_dec( std::uint32_t a );
  std::uint32_t half_uint32_inc( std::uint32_t a );
  std::uint32_t half_uint32_not( std::uint32_t a );
  std::uint32_t half_uint32_neg( std::uint32_t a );
  std::uint32_t half_uint32_ext( std::uint32_t a );

  std::uint32_t half_uint32_and( std::uint32_t a, std::uint32_t b );
  std::uint32_t half_uint32_xor( std::uint32_t a, std::uint32_t b );
  std::uint32_t half_uint32_andc( std::uint32_t a, std::uint32_t b );
  std::uint32_t half_uint32_or( std::uint32_t a, std::uint32_t b );
  std::uint32_t half_uint32_srl( std::uint32_t a, int sa );
  std::uint32_t half_uint32_sll( std::uint32_t a, int sa );
  std::uint32_t half_uint32_add( std::uint32_t a, std::uint32_t b );
  std::uint32_t half_uint32_sub( std::uint32_t a, std::uint32_t b );
  std::uint32_t half_uint32_mul( std::uint32_t a, std::uint32_t b );
  std::uint32_t half_uint32_sels( std::uint32_t test, std::uint32_t a, std::uint32_t b );
  std::uint32_t half_uint32_selb( std::uint32_t mask, std::uint32_t a, std::uint32_t b );

  std::uint16_t half_uint16_li( std::uint16_t a );
  std::uint16_t half_uint16_ext( std::uint16_t a );
  std::uint16_t half_uint16_neg( std::uint16_t a );
  std::uint16_t half_uint16_not( std::uint16_t a );
  std::uint16_t half_uint16_dec( std::uint16_t a );
  std::uint16_t half_uint16_sll( std::uint16_t a, int sa );
  std::uint16_t half_uint16_srl( std::uint16_t a, int sa );
  std::uint16_t half_uint16_add( std::uint16_t a, std::uint16_t b );
  std::uint16_t half_uint16_sub( std::uint16_t a, std::uint16_t b );
  std::uint16_t half_uint16_and( std::uint16_t a, std::uint16_t b );
  std::uint16_t half_uint16_or( std::uint16_t a, std::uint16_t b );
  std::uint16_t half_uint16_xor( std::uint16_t a, std::uint16_t b );
  std::uint16_t half_uint16_andc( std::uint16_t a, std::uint16_t b );
  std::uint16_t half_uint16_andsrl( std::uint16_t a, std::uint16_t b, int sa );
  std::uint16_t half_uint16_srlm( std::uint16_t a, int sa, std::uint16_t mask );
  std::uint16_t half_uint16_addm( std::uint16_t a, std::uint16_t b, std::uint16_t mask );
  std::uint16_t half_uint16_sels( std::uint16_t test, std::uint16_t a, std::uint16_t b );

  std::uint32_t half_uint32_cntlz( std::uint32_t x );
  std::uint16_t half_uint16_cntlz( std::uint16_t x );

  std::uint16_t half_from_float_bits( std::uint32_t f );
  std::uint32_t half_to_float_bits( std::uint16_t h );

  std::uint16_t half_from_float( float f );
  float half_to_float( std::uint16_t h );

  /// \brief Adds two half values together
  ///
  ///  (SUM)        std::uint16_t z = half_add( lhs, rhs );
  ///  (DIFFERENCE) std::uint16_t z = half_add( lhs, -rhs );
  ///
  ///  * Difference of ZEROs is always +ZERO
  ///  * Sum round with guard + round + sticky bit (grs)
  ///  * QNaN + <x>  = QNaN
  ///  * <x>  + +INF = +INF
  ///  * <x>  - -INF = -INF
  ///  * INF  - INF  = SNaN
  ///
  ///  Will have exactly (0 ulps difference) the same result as:
  ///  (Round up)
  ///  \code
  ///   union float_32
  ///   {
  ///     float    f32;
  ///     std::uint32_t u32;
  ///   };
  ///
  ///   auto fx = float_32{ half_to_float( lhs ) };
  ///   auto fy = float_32{ half_to_float( rhs ) };
  ///   auto fz = float_32{ fx.f32 + fy.f32    };
  ///   auto z  = float_to_half( fz.u32 );
  /// \endcode
  ///
  /// \param lhs the left half to add
  /// \param rhs the right half to add
  /// \return the result of the addition
  std::uint16_t half_add( std::uint16_t lhs, std::uint16_t rhs );
  std::uint16_t half_sub( std::uint16_t lhs, std::uint16_t rhs );

  /// \brief Multiplies \p lhs by \p rhs
  ///
  ///  May have 0 or 1 ulp difference from the following result:
  ///  (Round to nearest)
  ///  NOTE: Rounding mode differs between conversion and multiply
  ///
  ///     union FLOAT_32
  ///     {
  ///       float    f32;
  ///       std::uint32_t u32;
  ///     };
  ///
  ///     union FLOAT_32 fx = { .u32 = half_to_float( x ) };
  ///     union FLOAT_32 fy = { .u32 = half_to_float( y ) };
  ///     union FLOAT_32 fz = { .f32 = fx.f32 * fy.f32    };
  ///     std::uint16_t       z  = float_to_half( fz );
  ///
  /// \param lhs the left half to multiply
  /// \param rhs the right half to multiply
  /// \return the result of the multiplication
  std::uint16_t half_mul( std::uint16_t lhs, std::uint16_t rhs );
  std::uint16_t half_div( std::uint16_t lhs, std::uint16_t rhs );

  using float_storage_t = std::aligned_storage_t<sizeof(float),alignof(float)>;

} // anonymous namespace

//=============================================================================
// bit::math::half
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors / Assignment
//-----------------------------------------------------------------------------

bit::math::half::half( float f )
  noexcept
  : m_bits( half_from_float(f) )
{
}

//-----------------------------------------------------------------------------

bit::math::half& bit::math::half::operator=( float f )
  noexcept
{
  m_bits = half_from_float(f);

  return (*this);
}

//-----------------------------------------------------------------------------
// Casting
//-----------------------------------------------------------------------------

bit::math::half::operator float()
  const noexcept
{
  float_storage_t bytes;
  auto bits = half_to_float_bits(m_bits);

  std::memcpy( &bits, &bytes, sizeof(float) );

  return *reinterpret_cast<float*>(&bytes);
}

//-----------------------------------------------------------------------------
// Compound Operators
//-----------------------------------------------------------------------------

bit::math::half& bit::math::half::operator+=( const half& rhs )
  noexcept
{
  m_bits = half_add(m_bits, rhs.m_bits);
  return (*this);
}

bit::math::half& bit::math::half::operator-=( const half& rhs ) noexcept
{
  m_bits = half_sub(m_bits, rhs.m_bits);
  return (*this);
}

bit::math::half& bit::math::half::operator*=( const half& rhs ) noexcept
{
  m_bits = half_mul(m_bits, rhs.m_bits);
  return (*this);
}

bit::math::half& bit::math::half::operator/=( const half& rhs ) noexcept
{
  m_bits = half_div(m_bits, rhs.m_bits);
  return (*this);
}

//-----------------------------------------------------------------------------

namespace {
  // Load immediate
  inline std::uint32_t half_uint32_li( std::uint32_t a )
  {
    return a;
  }

  // Decrement
  inline std::uint32_t half_uint32_dec( std::uint32_t a )
  {
    return a - 1;
  }

  // Increment
  inline std::uint32_t half_uint32_inc( std::uint32_t a )
  {
    return a + 1;
  }

  // Complement
  inline std::uint32_t half_uint32_not( std::uint32_t a )
  {
    return ~a;
  }

  // Negate
  inline std::uint32_t half_uint32_neg( std::uint32_t a )
  {
    return -a;
  }

  // Extend sign
  inline std::uint32_t half_uint32_ext( std::uint32_t a )
  {
    return static_cast<std::int32_t>(a) >> 31;
  }

  // And
  inline std::uint32_t half_uint32_and( std::uint32_t a, std::uint32_t b )
  {
    return a & b;
  }

  // Exclusive Or
  inline std::uint32_t half_uint32_xor( std::uint32_t a, std::uint32_t b )
  {
    return a ^ b;
  }

  // And with Complement
  inline std::uint32_t half_uint32_andc( std::uint32_t a, std::uint32_t b )
  {
    return a & ~b;
  }

  // Or
  inline std::uint32_t half_uint32_or( std::uint32_t a, std::uint32_t b )
  {
    return a | b;
  }

  // Shift Right Logical
  inline std::uint32_t half_uint32_srl( std::uint32_t a, int sa )
  {
    return a >> sa;
  }

  // Shift Left Logical
  inline std::uint32_t half_uint32_sll( std::uint32_t a, int sa )
  {
    return a << sa;
  }

  // Add
  inline std::uint32_t half_uint32_add( std::uint32_t a, std::uint32_t b )
  {
    return a + b;
  }

  // Subtract
  inline std::uint32_t half_uint32_sub( std::uint32_t a, std::uint32_t b )
  {
    return a - b;
  }

  // Multiply
  inline std::uint32_t half_uint32_mul( std::uint32_t a, std::uint32_t b )
  {
    return a * b;
  }

  // Select on Sign bit
  inline std::uint32_t half_uint32_sels( std::uint32_t test, std::uint32_t a, std::uint32_t b )
  {
    const auto mask   = half_uint32_ext( test );
    const auto sel_a  = half_uint32_and( a, mask );
    const auto sel_b  = half_uint32_andc( b, mask );
    const auto result = half_uint32_or( sel_a, sel_b );

    return (result);
  }

  // Select Bits on mask
  inline std::uint32_t half_uint32_selb( std::uint32_t mask, std::uint32_t a, std::uint32_t b )
  {
    const auto sel_a  = half_uint32_and( a, mask );
    const auto sel_b  = half_uint32_andc( b, mask );
    const auto result = half_uint32_or( sel_a, sel_b );

    return result;
  }

  // Load Immediate
  inline std::uint16_t half_uint16_li( std::uint16_t a )
  {
    return a;
  }

  // Extend sign
  inline std::uint16_t half_uint16_ext( std::uint16_t a )
  {
    return static_cast<std::int16_t>(a) >> 15;
  }

  // Negate
  inline std::uint16_t half_uint16_neg( std::uint16_t a )
  {
    return -a;
  }

  // Complement
  inline std::uint16_t half_uint16_not( std::uint16_t a )
  {
    return ~a;
  }

  // Decrement
  inline std::uint16_t half_uint16_dec( std::uint16_t a )
  {
    return a - 1;
  }

  // Shift Left Logical
  inline std::uint16_t half_uint16_sll( std::uint16_t a, int sa )
  {
    return a << sa;
  }

  // Shift Right Logical
  inline std::uint16_t half_uint16_srl( std::uint16_t a, int sa )
  {
    return a >> sa;
  }

  // Add
  inline std::uint16_t half_uint16_add( std::uint16_t a, std::uint16_t b )
  {
    return a + b;
  }

  // Subtract
  inline std::uint16_t half_uint16_sub( std::uint16_t a, std::uint16_t b )
  {
    return a - b;
  }

  // And
  inline std::uint16_t half_uint16_and( std::uint16_t a, std::uint16_t b )
  {
    return a & b;
  }

  // Or
  inline std::uint16_t half_uint16_or( std::uint16_t a, std::uint16_t b )
  {
    return a | b;
  }

  // Exclusive Or
  inline std::uint16_t half_uint16_xor( std::uint16_t a, std::uint16_t b )
  {
    return a ^ b;
  }

  // And with Complement
  inline std::uint16_t half_uint16_andc( std::uint16_t a, std::uint16_t b )
  {
    return a & ~b;
  }

  // And then Shift Right Logical
  inline std::uint16_t half_uint16_andsrl( std::uint16_t a, std::uint16_t b, int sa )
  {
    return (a & b) >> sa;
  }

  // Shift Right Logical then Mask
  inline std::uint16_t half_uint16_srlm( std::uint16_t a, int sa, std::uint16_t mask )
  {
    return (a >> sa) & mask;
  }

  // Add then Mask
  inline std::uint16_t half_uint16_addm( std::uint16_t a, std::uint16_t b, std::uint16_t mask )
  {
    return (a + b) & mask;
  }

  // Select on Sign bit
  inline std::uint16_t half_uint16_sels( std::uint16_t test, std::uint16_t a, std::uint16_t b )
  {
    const auto mask   = half_uint16_ext( test );
    const auto sel_a  = half_uint16_and(  a,     mask  );
    const auto sel_b  = half_uint16_andc( b,     mask  );
    const auto result = half_uint16_or( sel_a, sel_b );

    return result;
  }

  // Count Leading Zeros
  inline std::uint32_t half_uint32_cntlz( std::uint32_t x )
  {
#ifdef __GNUC__
    /* NOTE: __builtin_clz is undefined for x == 0 */
    /* On PowerPC, this will map to insn: cntlzw   */
    /* On Pentium, this will map to insn: clz      */
    auto is_x_nez_msb = half_uint32_neg( x );
    auto nlz          = __builtin_clz( x );
    auto result       = half_uint32_sels( is_x_nez_msb, nlz, 0x00000020 );

    return result;
#else
    const auto x0  = half_uint32_srl( x,  1 );
    const auto x1  = half_uint32_or( x,  x0 );
    const auto x2  = half_uint32_srl( x1, 2 );
    const auto x3  = half_uint32_or( x1, x2 );
    const auto x4  = half_uint32_srl( x3, 4 );
    const auto x5  = half_uint32_or( x3, x4 );
    const auto x6  = half_uint32_srl( x5, 8 );
    const auto x7  = half_uint32_or( x5, x6 );
    const auto x8  = half_uint32_srl( x7, 16 );
    const auto x9  = half_uint32_or( x7, x8 );
    const auto xA  = half_uint32_not( x9 );
    const auto xB  = half_uint32_srl( xA, 1 );
    const auto xC  = half_uint32_and( xB, 0x55555555 );
    const auto xD  = half_uint32_sub( xA, xC );
    const auto xE  = half_uint32_and( xD, 0x33333333 );
    const auto xF  = half_uint32_srl( xD, 2 );
    const auto x10 = half_uint32_and( xF, 0x33333333 );
    const auto x11 = half_uint32_add( xE, x10 );
    const auto x12 = half_uint32_srl( x11, 4 );
    const auto x13 = half_uint32_add( x11, x12 );
    const auto x14 = half_uint32_and( x13, 0x0f0f0f0f );
    const auto x15 = half_uint32_srl( x14, 8 );
    const auto x16 = half_uint32_add( x14, x15 );
    const auto x17 = half_uint32_srl( x16, 16 );
    const auto x18 = half_uint32_add( x16, x17 );
    const auto x19 = half_uint32_and( x18, 0x0000003f );

    return x19;
#endif
  }

  // Count Leading Zeros
  inline std::uint16_t half_uint16_cntlz( std::uint16_t x )
  {
#ifdef __GNUC__
    const auto x32 = static_cast<std::uint32_t>(x);
    auto nlz32 = static_cast<std::uint16_t>( half_uint32_cntlz(x32) );
    auto nlz   = half_uint32_sub( nlz32, 16 );

    return nlz;
#else
    const auto x0  = half_uint16_srl(  x,  1 );
    const auto x1  = half_uint16_or(   x,  x0 );
    const auto x2  = half_uint16_srl(  x1, 2 );
    const auto x3  = half_uint16_or(   x1, x2 );
    const auto x4  = half_uint16_srl(  x3, 4 );
    const auto x5  = half_uint16_or(   x3, x4 );
    const auto x6  = half_uint16_srl(  x5, 8 );
    const auto x7  = half_uint16_or(   x5, x6 );
    const auto x8  = half_uint16_not(  x7 );
    const auto x9  = half_uint16_srlm( x8, 1, 0x5555 );
    const auto xA  = half_uint16_sub(  x8, x9 );
    const auto xB  = half_uint16_and(  xA, 0x3333 );
    const auto xC  = half_uint16_srlm( xA, 2, 0x3333 );
    const auto xD  = half_uint16_add(  xB, xC );
    const auto xE  = half_uint16_srl(  xD, 4 );
    const auto xF  = half_uint16_addm( xD, xE, 0x0f0f );
    const auto x10 = half_uint16_srl(  xF, 8 );
    const auto x11 = half_uint16_addm( xF, x10, 0x001f );

    return x11;
#endif
  }

  std::uint16_t half_from_float_bits( std::uint32_t f )
  {
    const auto one                        = half_uint32_li( 0x00000001 );
    const auto f_s_mask                   = half_uint32_li( 0x80000000 );
    const auto f_e_mask                   = half_uint32_li( 0x7f800000 );
    const auto f_m_mask                   = half_uint32_li( 0x007fffff );
    const auto f_m_hidden_bit             = half_uint32_li( 0x00800000 );
    const auto f_m_round_bit              = half_uint32_li( 0x00001000 );
    const auto f_snan_mask                = half_uint32_li( 0x7fc00000 );
    const auto f_e_pos                    = half_uint32_li( 0x00000017 );
    const auto h_e_pos                    = half_uint32_li( 0x0000000a );
    const auto h_e_mask                   = half_uint32_li( 0x00007c00 );
    const auto h_snan_mask                = half_uint32_li( 0x00007e00 );
    const auto h_e_mask_value             = half_uint32_li( 0x0000001f );
    const auto f_h_s_pos_offset           = half_uint32_li( 0x00000010 );
    const auto f_h_bias_offset            = half_uint32_li( 0x00000070 );
    const auto f_h_m_pos_offset           = half_uint32_li( 0x0000000d );
    const auto h_nan_min                  = half_uint32_li( 0x00007c01 );
    const auto f_h_e_biased_flag          = half_uint32_li( 0x0000008f );
    const auto f_s                        = half_uint32_and( f,               f_s_mask         );
    const auto f_e                        = half_uint32_and( f,               f_e_mask         );
    const auto h_s                        = half_uint32_srl( f_s,             f_h_s_pos_offset );
    const auto f_m                        = half_uint32_and( f,               f_m_mask         );
    const auto f_e_amount                 = half_uint32_srl( f_e,             f_e_pos          );
    const auto f_e_half_bias              = half_uint32_sub( f_e_amount,      f_h_bias_offset  );
    const auto f_snan                     = half_uint32_and( f,               f_snan_mask      );
    const auto f_m_round_mask             = half_uint32_and( f_m,             f_m_round_bit    );
    const auto f_m_round_offset           = half_uint32_sll( f_m_round_mask,  one              );
    const auto f_m_rounded                = half_uint32_add( f_m,             f_m_round_offset );
    const auto f_m_denorm_sa              = half_uint32_sub( one,             f_e_half_bias    );
    const auto f_m_with_hidden            = half_uint32_or(  f_m_rounded,     f_m_hidden_bit   );
    const auto f_m_denorm                 = half_uint32_srl( f_m_with_hidden, f_m_denorm_sa    );
    const auto h_m_denorm                 = half_uint32_srl( f_m_denorm,      f_h_m_pos_offset );
    const auto f_m_rounded_overflow       = half_uint32_and( f_m_rounded,     f_m_hidden_bit   );
    const auto m_nan                      = half_uint32_srl( f_m,             f_h_m_pos_offset );
    const auto h_em_nan                   = half_uint32_or(  h_e_mask,        m_nan            );
    const auto h_e_norm_overflow_offset   = half_uint32_inc( f_e_half_bias );
    const auto h_e_norm_overflow          = half_uint32_sll( h_e_norm_overflow_offset, h_e_pos          );
    const auto h_e_norm                   = half_uint32_sll( f_e_half_bias,            h_e_pos          );
    const auto h_m_norm                   = half_uint32_srl( f_m_rounded,              f_h_m_pos_offset );
    const auto h_em_norm                  = half_uint32_or(  h_e_norm,                 h_m_norm         );
    const auto is_h_ndenorm_msb           = half_uint32_sub( f_h_bias_offset,   f_e_amount    );
    const auto is_f_e_flagged_msb         = half_uint32_sub( f_h_e_biased_flag, f_e_half_bias );
    const auto is_h_denorm_msb            = half_uint32_not( is_h_ndenorm_msb );
    const auto is_f_m_eqz_msb             = half_uint32_dec( f_m   );
    const auto is_h_nan_eqz_msb           = half_uint32_dec( m_nan );
    const auto is_f_inf_msb               = half_uint32_and( is_f_e_flagged_msb, is_f_m_eqz_msb   );
    const auto is_f_nan_underflow_msb     = half_uint32_and( is_f_e_flagged_msb, is_h_nan_eqz_msb );
    const auto is_e_overflow_msb          = half_uint32_sub( h_e_mask_value,     f_e_half_bias    );
    const auto is_h_inf_msb               = half_uint32_or(  is_e_overflow_msb,  is_f_inf_msb     );
    const auto is_f_nsnan_msb             = half_uint32_sub( f_snan,             f_snan_mask      );
    const auto is_m_norm_overflow_msb     = half_uint32_neg( f_m_rounded_overflow );
    const auto is_f_snan_msb              = half_uint32_not( is_f_nsnan_msb );
    const auto h_em_overflow_result       = half_uint32_sels( is_m_norm_overflow_msb, h_e_norm_overflow, h_em_norm                 );
    const auto h_em_nan_result            = half_uint32_sels( is_f_e_flagged_msb,     h_em_nan,          h_em_overflow_result      );
    const auto h_em_nan_underflow_result  = half_uint32_sels( is_f_nan_underflow_msb, h_nan_min,         h_em_nan_result           );
    const auto h_em_inf_result            = half_uint32_sels( is_h_inf_msb,           h_e_mask,          h_em_nan_underflow_result );
    const auto h_em_denorm_result         = half_uint32_sels( is_h_denorm_msb,        h_m_denorm,        h_em_inf_result           );
    const auto h_em_snan_result           = half_uint32_sels( is_f_snan_msb,          h_snan_mask,       h_em_denorm_result        );
    const auto h_result                   = half_uint32_or( h_s, h_em_snan_result );

    return static_cast<std::uint16_t>(h_result);
  }

  std::uint32_t half_to_float_bits( std::uint16_t h )
  {
    const auto h_e_mask              = half_uint32_li( 0x00007c00 );
    const auto h_m_mask              = half_uint32_li( 0x000003ff );
    const auto h_s_mask              = half_uint32_li( 0x00008000 );
    const auto h_f_s_pos_offset      = half_uint32_li( 0x00000010 );
    const auto h_f_e_pos_offset      = half_uint32_li( 0x0000000d );
    const auto h_f_bias_offset       = half_uint32_li( 0x0001c000 );
    const auto f_e_mask              = half_uint32_li( 0x7f800000 );
    const auto f_m_mask              = half_uint32_li( 0x007fffff );
    const auto h_f_e_denorm_bias     = half_uint32_li( 0x0000007e );
    const auto h_f_m_denorm_sa_bias  = half_uint32_li( 0x00000008 );
    const auto f_e_pos               = half_uint32_li( 0x00000017 );
    const auto h_e_mask_minus_one    = half_uint32_li( 0x00007bff );
    const auto h_e                   = half_uint32_and( h, h_e_mask );
    const auto h_m                   = half_uint32_and( h, h_m_mask );
    const auto h_s                   = half_uint32_and( h, h_s_mask );
    const auto h_e_f_bias            = half_uint32_add( h_e, h_f_bias_offset );
    const auto h_m_nlz               = half_uint32_cntlz( h_m );
    const auto f_s                   = half_uint32_sll( h_s,        h_f_s_pos_offset );
    const auto f_e                   = half_uint32_sll( h_e_f_bias, h_f_e_pos_offset );
    const auto f_m                   = half_uint32_sll( h_m,        h_f_e_pos_offset );
    const auto f_em                  = half_uint32_or(  f_e,        f_m              );
    const auto h_f_m_sa              = half_uint32_sub( h_m_nlz,             h_f_m_denorm_sa_bias );
    const auto f_e_denorm_unpacked   = half_uint32_sub( h_f_e_denorm_bias,   h_f_m_sa             );
    const auto h_f_m                 = half_uint32_sll( h_m,                 h_f_m_sa             );
    const auto f_m_denorm            = half_uint32_and( h_f_m,               f_m_mask             );
    const auto f_e_denorm            = half_uint32_sll( f_e_denorm_unpacked, f_e_pos              );
    const auto f_em_denorm           = half_uint32_or(  f_e_denorm,          f_m_denorm           );
    const auto f_em_nan              = half_uint32_or(  f_e_mask,            f_m                  );
    const auto is_e_eqz_msb          = half_uint32_dec(  h_e );
    const auto is_m_nez_msb          = half_uint32_neg(  h_m );
    const auto is_e_flagged_msb      = half_uint32_sub(  h_e_mask_minus_one, h_e );
    const auto is_zero_msb           = half_uint32_andc( is_e_eqz_msb,       is_m_nez_msb );
    const auto is_inf_msb            = half_uint32_andc( is_e_flagged_msb,   is_m_nez_msb );
    const auto is_denorm_msb         = half_uint32_and(  is_m_nez_msb,       is_e_eqz_msb );
    const auto is_nan_msb            = half_uint32_and(  is_e_flagged_msb,   is_m_nez_msb );
    const auto is_zero               = half_uint32_ext(  is_zero_msb );
    const auto f_zero_result         = half_uint32_andc( f_em, is_zero );
    const auto f_denorm_result       = half_uint32_sels( is_denorm_msb, f_em_denorm, f_zero_result );
    const auto f_inf_result          = half_uint32_sels( is_inf_msb,    f_e_mask,    f_denorm_result );
    const auto f_nan_result          = half_uint32_sels( is_nan_msb,    f_em_nan,    f_inf_result    );
    const auto f_result              = half_uint32_or( f_s, f_nan_result );

    return f_result;
  }

  std::uint16_t half_from_float( float f )
  {
    // Technically, using a union or a reinterpret_cast for float -> int violates
    // strict aliasing. For full c++ conformance, copying into a byte array, and
    // interpreting that byte array as an int is the only way to appropriately
    // cast between the two (although a union may work in practice, it is UB
    // in C++ to type-pun).

    // As a result, memcpy is used here for correctness; though it may come at
    // a slight performance overhead.

    float_storage_t bytes;

    std::memcpy(&bytes, &f, sizeof(float));
    return half_from_float_bits( *reinterpret_cast<std::uint32_t*>(&bytes) );
  }

  float half_to_float( std::uint16_t h )
  {
    float_storage_t bytes;

    auto float_bits = half_to_float_bits(h);

    std::memcpy(&bytes, &float_bits, sizeof(float));
    return *reinterpret_cast<float*>(&bytes);
  }


  std::uint16_t half_add( std::uint16_t lhs, std::uint16_t rhs )
  {
    const auto one                       = half_uint16_li( 0x0001 );
    const auto msb_to_lsb_sa             = half_uint16_li( 0x000f );
    const auto h_s_mask                  = half_uint16_li( 0x8000 );
    const auto h_e_mask                  = half_uint16_li( 0x7c00 );
    const auto h_m_mask                  = half_uint16_li( 0x03ff );
    const auto h_m_msb_mask              = half_uint16_li( 0x2000 );
    const auto h_m_msb_sa                = half_uint16_li( 0x000d );
    const auto h_m_hidden                = half_uint16_li( 0x0400 );
    const auto h_e_pos                   = half_uint16_li( 0x000a );
    const auto h_e_bias_minus_one        = half_uint16_li( 0x000e );
    const auto h_m_grs_carry             = half_uint16_li( 0x4000 );
    const auto h_m_grs_carry_pos         = half_uint16_li( 0x000e );
    const auto h_grs_size                = half_uint16_li( 0x0003 );
    const auto h_snan                    = half_uint16_li( 0xfe00 );
    const auto h_e_mask_minus_one        = half_uint16_li( 0x7bff );
    const auto h_grs_round_carry         = half_uint16_sll( one, h_grs_size );
    const auto h_grs_round_mask          = half_uint16_sub( h_grs_round_carry, one );
    const auto x_e                       = half_uint16_and( lhs, h_e_mask );
    const auto y_e                       = half_uint16_and( rhs, h_e_mask );
    const auto is_y_e_larger_msb         = half_uint16_sub( x_e, y_e );
    const auto a                         = half_uint16_sels( is_y_e_larger_msb, rhs, lhs);
    const auto a_s                       = half_uint16_and( a, h_s_mask );
    const auto a_e                       = half_uint16_and( a, h_e_mask );
    const auto a_m_no_hidden_bit         = half_uint16_and( a, h_m_mask );
    const auto a_em_no_hidden_bit        = half_uint16_or( a_e, a_m_no_hidden_bit );
    const auto b                         = half_uint16_sels( is_y_e_larger_msb, lhs, rhs);
    const auto b_s                       = half_uint16_and( b, h_s_mask );
    const auto b_e                       = half_uint16_and( b, h_e_mask );
    const auto b_m_no_hidden_bit         = half_uint16_and( b, h_m_mask );
    const auto b_em_no_hidden_bit        = half_uint16_or( b_e, b_m_no_hidden_bit );
    const auto is_diff_sign_msb          = half_uint16_xor( a_s, b_s );
    const auto is_a_inf_msb              = half_uint16_sub( h_e_mask_minus_one, a_em_no_hidden_bit );
    const auto is_b_inf_msb              = half_uint16_sub( h_e_mask_minus_one, b_em_no_hidden_bit );
    const auto is_undenorm_msb           = half_uint16_dec( a_e );
    const auto is_undenorm               = half_uint16_ext( is_undenorm_msb );
    const auto is_both_inf_msb           = half_uint16_and( is_a_inf_msb, is_b_inf_msb );
    const auto is_invalid_inf_op_msb     = half_uint16_and( is_both_inf_msb, b_s );
    const auto is_a_e_nez_msb            = half_uint16_neg( a_e );
    const auto is_b_e_nez_msb            = half_uint16_neg( b_e );
    const auto is_a_e_nez                = half_uint16_ext( is_a_e_nez_msb );
    const auto is_b_e_nez                = half_uint16_ext( is_b_e_nez_msb );
    const auto a_m_hidden_bit            = half_uint16_and( is_a_e_nez, h_m_hidden );
    const auto b_m_hidden_bit            = half_uint16_and( is_b_e_nez, h_m_hidden );
    const auto a_m_no_grs                = half_uint16_or( a_m_no_hidden_bit, a_m_hidden_bit );
    const auto b_m_no_grs                = half_uint16_or( b_m_no_hidden_bit, b_m_hidden_bit );
    const auto diff_e                    = half_uint16_sub( a_e,        b_e );
    const auto a_e_unbias                = half_uint16_sub( a_e,        h_e_bias_minus_one );
    const auto a_m                       = half_uint16_sll( a_m_no_grs, h_grs_size );
    const auto a_e_biased                = half_uint16_srl( a_e,        h_e_pos );
    const auto m_sa_unbias               = half_uint16_srl( a_e_unbias, h_e_pos );
    const auto m_sa_default              = half_uint16_srl( diff_e,     h_e_pos );
    const auto m_sa_unbias_mask          = half_uint16_andc( is_a_e_nez_msb,   is_b_e_nez_msb );
    const auto m_sa                      = half_uint16_sels( m_sa_unbias_mask, m_sa_unbias, m_sa_default );
    const auto b_m_no_sticky             = half_uint16_sll( b_m_no_grs,        h_grs_size );
    const auto sh_m                      = half_uint16_srl( b_m_no_sticky,     m_sa );
    const auto sticky_overflow           = half_uint16_sll( one,               m_sa );
    const auto sticky_mask               = half_uint16_dec( sticky_overflow );
    const auto sticky_collect            = half_uint16_and( b_m_no_sticky, sticky_mask );
    const auto is_sticky_set_msb         = half_uint16_neg( sticky_collect );
    const auto sticky                    = half_uint16_srl( is_sticky_set_msb, msb_to_lsb_sa);
    const auto b_m                       = half_uint16_or( sh_m, sticky );
    const auto is_c_m_ab_pos_msb         = half_uint16_sub( b_m, a_m );
    const auto c_inf                     = half_uint16_or( a_s, h_e_mask );
    const auto c_m_sum                   = half_uint16_add( a_m, b_m );
    const auto c_m_diff_ab               = half_uint16_sub( a_m, b_m );
    const auto c_m_diff_ba               = half_uint16_sub( b_m, a_m );
    const auto c_m_smag_diff             = half_uint16_sels( is_c_m_ab_pos_msb, c_m_diff_ab, c_m_diff_ba );
    const auto c_s_diff                  = half_uint16_sels( is_c_m_ab_pos_msb, a_s,         b_s         );
    const auto c_s                       = half_uint16_sels( is_diff_sign_msb,  c_s_diff,    a_s         );
    const auto c_m_smag_diff_nlz         = half_uint16_cntlz( c_m_smag_diff );
    const auto diff_norm_sa              = half_uint16_sub( c_m_smag_diff_nlz, one );
    const auto is_diff_denorm_msb        = half_uint16_sub( a_e_biased, diff_norm_sa );
    const auto is_diff_denorm            = half_uint16_ext( is_diff_denorm_msb );
    const auto is_a_or_b_norm_msb        = half_uint16_neg( a_e_biased );
    const auto diff_denorm_sa            = half_uint16_dec( a_e_biased );
    const auto c_m_diff_denorm           = half_uint16_sll( c_m_smag_diff, diff_denorm_sa );
    const auto c_m_diff_norm             = half_uint16_sll( c_m_smag_diff, diff_norm_sa );
    const auto c_e_diff_norm             = half_uint16_sub( a_e_biased,  diff_norm_sa );
    const auto c_m_diff_ab_norm          = half_uint16_sels( is_diff_denorm_msb, c_m_diff_denorm, c_m_diff_norm );
    const auto c_e_diff_ab_norm          = half_uint16_andc( c_e_diff_norm, is_diff_denorm );
    const auto c_m_diff                  = half_uint16_sels( is_a_or_b_norm_msb, c_m_diff_ab_norm, c_m_smag_diff );
    const auto c_e_diff                  = half_uint16_sels( is_a_or_b_norm_msb, c_e_diff_ab_norm, a_e_biased    );
    const auto is_diff_eqz_msb           = half_uint16_dec( c_m_diff );
    const auto is_diff_exactly_zero_msb  = half_uint16_and( is_diff_sign_msb, is_diff_eqz_msb );
    const auto is_diff_exactly_zero      = half_uint16_ext( is_diff_exactly_zero_msb );
    const auto c_m_added                 = half_uint16_sels( is_diff_sign_msb, c_m_diff, c_m_sum );
    const auto c_e_added                 = half_uint16_sels( is_diff_sign_msb, c_e_diff, a_e_biased );
    const auto c_m_carry                 = half_uint16_and( c_m_added, h_m_grs_carry );
    const auto is_c_m_carry_msb          = half_uint16_neg( c_m_carry );
    const auto c_e_hidden_offset         = half_uint16_andsrl( c_m_added, h_m_grs_carry, h_m_grs_carry_pos );
    const auto c_m_sub_hidden            = half_uint16_srl( c_m_added, one );
    const auto c_m_no_hidden             = half_uint16_sels( is_c_m_carry_msb, c_m_sub_hidden, c_m_added );
    const auto c_e_no_hidden             = half_uint16_add( c_e_added,         c_e_hidden_offset  );
    const auto c_m_no_hidden_msb         = half_uint16_and( c_m_no_hidden,     h_m_msb_mask       );
    const auto undenorm_m_msb_odd        = half_uint16_srl( c_m_no_hidden_msb, h_m_msb_sa         );
    const auto undenorm_fix_e            = half_uint16_and( is_undenorm,       undenorm_m_msb_odd );
    const auto c_e_fixed                 = half_uint16_add( c_e_no_hidden,     undenorm_fix_e     );
    const auto c_m_round_amount          = half_uint16_and( c_m_no_hidden,     h_grs_round_mask   );
    const auto c_m_rounded               = half_uint16_add( c_m_no_hidden,     c_m_round_amount   );
    const auto c_m_round_overflow        = half_uint16_andsrl( c_m_rounded, h_m_grs_carry, h_m_grs_carry_pos );
    const auto c_e_rounded               = half_uint16_add( c_e_fixed, c_m_round_overflow );
    const auto c_m_no_grs                = half_uint16_srlm( c_m_rounded, h_grs_size,  h_m_mask );
    const auto c_e                       = half_uint16_sll( c_e_rounded, h_e_pos );
    const auto c_em                      = half_uint16_or( c_e, c_m_no_grs );
    const auto c_normal                  = half_uint16_or( c_s, c_em );
    const auto c_inf_result              = half_uint16_sels( is_a_inf_msb, c_inf, c_normal );
    const auto c_zero_result             = half_uint16_andc( c_inf_result, is_diff_exactly_zero );
    const auto c_result                  = half_uint16_sels( is_invalid_inf_op_msb, h_snan, c_zero_result );

    return c_result;
  }

  inline std::uint16_t half_sub( std::uint16_t lhs, std::uint16_t rhs )
  {
    return half_add( lhs, rhs ^ 0x8000 );
  }

  std::uint16_t half_mul( std::uint16_t lhs, std::uint16_t rhs )
  {
    const auto one                                = half_uint32_li( 0x00000001 );
    const auto h_s_mask                           = half_uint32_li( 0x00008000 );
    const auto h_e_mask                           = half_uint32_li( 0x00007c00 );
    const auto h_m_mask                           = half_uint32_li( 0x000003ff );
    const auto h_m_hidden                         = half_uint32_li( 0x00000400 );
    const auto h_e_pos                            = half_uint32_li( 0x0000000a );
    const auto h_e_bias                           = half_uint32_li( 0x0000000f );
    const auto h_m_bit_count                      = half_uint32_li( 0x0000000a );
    const auto h_m_bit_half_count                 = half_uint32_li( 0x00000005 );
    const auto h_nan_min                          = half_uint32_li( 0x00007c01 );
    const auto h_e_mask_minus_one                 = half_uint32_li( 0x00007bff );
    const auto h_snan                             = half_uint32_li( 0x0000fe00 );
    const auto m_round_overflow_bit               = half_uint32_li( 0x00000020 );
    const auto m_hidden_bit                       = half_uint32_li( 0x00100000 );
    const auto a_s                                = half_uint32_and(  lhs,   h_s_mask );
    const auto b_s                                = half_uint32_and(  rhs,   h_s_mask );
    const auto c_s                                = half_uint32_xor(  a_s, b_s      );
    const auto x_e                                = half_uint32_and(  lhs,   h_e_mask );
    const auto x_e_eqz_msb                        = half_uint32_dec(  x_e );
    const auto a                                  = half_uint32_sels( x_e_eqz_msb, rhs, lhs );
    const auto b                                  = half_uint32_sels( x_e_eqz_msb, lhs, rhs );
    const auto a_e                                = half_uint32_and(  a,   h_e_mask );
    const auto b_e                                = half_uint32_and(  b,   h_e_mask );
    const auto a_m                                = half_uint32_and(  a,   h_m_mask );
    const auto b_m                                = half_uint32_and(  b,   h_m_mask );
    const auto a_e_amount                         = half_uint32_srl(  a_e,                 h_e_pos                 );
    const auto b_e_amount                         = half_uint32_srl(  b_e,                 h_e_pos                 );
    const auto a_m_with_hidden                    = half_uint32_or(   a_m,                 h_m_hidden              );
    const auto b_m_with_hidden                    = half_uint32_or(   b_m,                 h_m_hidden              );
    const auto c_m_normal                         = half_uint32_mul(  a_m_with_hidden,     b_m_with_hidden         );
    const auto c_m_denorm_biased                  = half_uint32_mul(  a_m_with_hidden,     b_m                     );
    const auto c_e_denorm_unbias_e                = half_uint32_sub(  h_e_bias,            a_e_amount              );
    const auto c_m_denorm_round_amount            = half_uint32_and(  c_m_denorm_biased,   h_m_mask                );
    const auto c_m_denorm_rounded                 = half_uint32_add(  c_m_denorm_biased,   c_m_denorm_round_amount );
    const auto c_m_denorm_inplace                 = half_uint32_srl(  c_m_denorm_rounded,  h_m_bit_count           );
    const auto c_m_denorm_unbiased                = half_uint32_srl(  c_m_denorm_inplace,  c_e_denorm_unbias_e     );
    const auto c_m_denorm                         = half_uint32_and(  c_m_denorm_unbiased, h_m_mask                );
    const auto c_e_amount_biased                  = half_uint32_add(  a_e_amount,          b_e_amount              );
    const auto c_e_amount_unbiased                = half_uint32_sub(  c_e_amount_biased,   h_e_bias                );
    const auto is_c_e_unbiased_underflow          = half_uint32_ext(  c_e_amount_unbiased );
    const auto c_e_underflow_half_sa              = half_uint32_neg(  c_e_amount_unbiased );
    const auto c_e_underflow_sa                   = half_uint32_sll(  c_e_underflow_half_sa,     one );
    const auto c_m_underflow                      = half_uint32_srl(  c_m_normal,                c_e_underflow_sa );
    const auto c_e_underflow_added                = half_uint32_andc( c_e_amount_unbiased,       is_c_e_unbiased_underflow );
    const auto c_m_underflow_added                = half_uint32_selb( is_c_e_unbiased_underflow, c_m_underflow, c_m_normal );
    const auto is_mul_overflow_test               = half_uint32_and(  c_e_underflow_added, m_round_overflow_bit );
    const auto is_mul_overflow_msb                = half_uint32_neg(  is_mul_overflow_test );
    const auto c_e_norm_radix_corrected           = half_uint32_inc(  c_e_underflow_added );
    const auto c_m_norm_radix_corrected           = half_uint32_srl(  c_m_underflow_added, one );
    const auto c_m_norm_hidden_bit                = half_uint32_and(  c_m_norm_radix_corrected,  m_hidden_bit );
    const auto is_c_m_norm_no_hidden_msb          = half_uint32_dec(  c_m_norm_hidden_bit );
    const auto c_m_norm_lo                        = half_uint32_srl(  c_m_norm_radix_corrected, h_m_bit_half_count );
    const auto c_m_norm_lo_nlz                    = half_uint16_cntlz( c_m_norm_lo );
    const auto is_c_m_hidden_nunderflow_msb       = half_uint32_sub(  c_m_norm_lo_nlz, c_e_norm_radix_corrected );
    const auto is_c_m_hidden_underflow_msb        = half_uint32_not(  is_c_m_hidden_nunderflow_msb );
    const auto is_c_m_hidden_underflow            = half_uint32_ext(  is_c_m_hidden_underflow_msb  );
    const auto c_m_hidden_underflow_normalized_sa = half_uint32_srl(  c_m_norm_lo_nlz, one );
    const auto c_m_hidden_underflow_normalized    = half_uint32_sll(  c_m_norm_radix_corrected, c_m_hidden_underflow_normalized_sa );
    const auto c_m_hidden_normalized              = half_uint32_sll(  c_m_norm_radix_corrected, c_m_norm_lo_nlz );
    const auto c_e_hidden_normalized              = half_uint32_sub(  c_e_norm_radix_corrected, c_m_norm_lo_nlz );
    const auto c_e_hidden                         = half_uint32_andc( c_e_hidden_normalized, is_c_m_hidden_underflow );
    const auto c_m_hidden                         = half_uint32_sels( is_c_m_hidden_underflow_msb, c_m_hidden_underflow_normalized, c_m_hidden_normalized );
    const auto c_m_normalized                     = half_uint32_sels( is_c_m_norm_no_hidden_msb, c_m_hidden, c_m_norm_radix_corrected );
    const auto c_e_normalized                     = half_uint32_sels( is_c_m_norm_no_hidden_msb, c_e_hidden, c_e_norm_radix_corrected );
    const auto c_m_norm_round_amount              = half_uint32_and(  c_m_normalized, h_m_mask );
    const auto c_m_norm_rounded                   = half_uint32_add(  c_m_normalized, c_m_norm_round_amount );
    const auto is_round_overflow_test             = half_uint32_and(  c_e_normalized, m_round_overflow_bit  );
    const auto is_round_overflow_msb              = half_uint32_neg(  is_round_overflow_test );
    const auto c_m_norm_inplace                   = half_uint32_srl(  c_m_norm_rounded,    h_m_bit_count );
    const auto c_m                                = half_uint32_and(  c_m_norm_inplace,    h_m_mask      );
    const auto c_e_norm_inplace                   = half_uint32_sll(  c_e_normalized, h_e_pos       );
    const auto c_e                                = half_uint32_and(  c_e_norm_inplace,    h_e_mask      );
    const auto c_em_nan                           = half_uint32_or(   h_e_mask,  a_m        );
    const auto c_nan                              = half_uint32_or(   a_s,       c_em_nan   );
    const auto c_denorm                           = half_uint32_or(   c_s,       c_m_denorm );
    const auto c_inf                              = half_uint32_or(   c_s,       h_e_mask   );
    const auto c_em_norm                          = half_uint32_or(   c_e,       c_m        );
    const auto is_a_e_flagged_msb                 = half_uint32_sub(  h_e_mask_minus_one, a_e );
    const auto is_b_e_flagged_msb                 = half_uint32_sub(  h_e_mask_minus_one, b_e );
    const auto is_a_e_eqz_msb                     = half_uint32_dec(  a_e );
    const auto is_a_m_eqz_msb                     = half_uint32_dec(  a_m );
    const auto is_b_e_eqz_msb                     = half_uint32_dec(  b_e );
    const auto is_b_m_eqz_msb                     = half_uint32_dec(  b_m );
    const auto is_b_eqz_msb                       = half_uint32_and(  is_b_e_eqz_msb,          is_b_m_eqz_msb         );
    const auto is_a_eqz_msb                       = half_uint32_and(  is_a_e_eqz_msb,          is_a_m_eqz_msb         );
    const auto is_c_nan_via_a_msb                 = half_uint32_andc( is_a_e_flagged_msb,      is_b_e_flagged_msb     );
    const auto is_c_nan_via_b_msb                 = half_uint32_andc( is_b_e_flagged_msb,      is_b_m_eqz_msb         );
    const auto is_c_nan_msb                       = half_uint32_or(   is_c_nan_via_a_msb,      is_c_nan_via_b_msb     );
    const auto is_c_denorm_msb                    = half_uint32_andc( is_b_e_eqz_msb,          is_a_e_flagged_msb     );
    const auto is_a_inf_msb                       = half_uint32_and(  is_a_e_flagged_msb,      is_a_m_eqz_msb         );
    const auto is_c_snan_msb                      = half_uint32_and(  is_a_inf_msb,            is_b_eqz_msb           );
    const auto is_c_nan_min_via_a_msb             = half_uint32_and(  is_a_e_flagged_msb,      is_b_eqz_msb           );
    const auto is_c_nan_min_via_b_msb             = half_uint32_and(  is_b_e_flagged_msb,      is_a_eqz_msb           );
    const auto is_c_nan_min_msb                   = half_uint32_or(   is_c_nan_min_via_a_msb,  is_c_nan_min_via_b_msb );
    const auto is_c_inf_msb                       = half_uint32_or(   is_a_e_flagged_msb,      is_b_e_flagged_msb     );
    const auto is_overflow_msb                    = half_uint32_or(   is_round_overflow_msb,   is_mul_overflow_msb    );
    const auto c_em_overflow_result               = half_uint32_sels( is_overflow_msb, h_e_mask, c_em_norm );
    const auto c_common_result                    = half_uint32_or(   c_s, c_em_overflow_result );
    const auto c_zero_result                      = half_uint32_sels( is_b_eqz_msb,     c_s,       c_common_result  );
    const auto c_nan_result                       = half_uint32_sels( is_c_nan_msb,     c_nan,     c_zero_result );
    const auto c_nan_min_result                   = half_uint32_sels( is_c_nan_min_msb, h_nan_min, c_nan_result     );
    const auto c_inf_result                       = half_uint32_sels( is_c_inf_msb,     c_inf,     c_nan_min_result   );
    const auto c_denorm_result                    = half_uint32_sels( is_c_denorm_msb,  c_denorm,  c_inf_result);
    const auto c_result                           = half_uint32_sels( is_c_snan_msb,    h_snan,    c_denorm_result );

    return static_cast<std::uint16_t>(c_result);
  }

  inline std::uint16_t half_div( std::uint16_t lhs, std::uint16_t rhs )
  {
    // Invert rhs (1/rhs) and multiply
    const auto float_rhs_inv = (1.0f / half_to_float(rhs));

    return half_mul( lhs, half_from_float(float_rhs_inv) );
  }

} // anonymous namespace
