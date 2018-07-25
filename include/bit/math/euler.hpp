/*****************************************************************************
 * \file
 * \brief todo: fill in documentation
 *****************************************************************************/

/*
  The MIT License (MIT)

  Bit Math Library.
  https://github.com/bitwizeshift/bit-math

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef BIT_MATH_EULER_HPP
#define BIT_MATH_EULER_HPP

#include "vector.hpp"     // bit::math::vector3 / bit::math::vector4
#include "matrix.hpp"     // bit::math::matrix3 / bit::math::matrix4
#include "angles.hpp"     // bit::math::radian
#include "quaternion.hpp" // bit::math::quaternion

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An euler angle that represents the roll, pitch, and yaw in
    ///        3-space
    //////////////////////////////////////////////////////////////////////////
    class euler
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type      = radian;
      using reference       = value_type&;
      using pointer         = value_type*;
      using const_reference = const value_type&;
      using const_pointer   = const value_type*;

      using vector_type  = vector3<float_t>;
      using matrix3_type = matrix3<float_t>;
      using matrix4_type = matrix4<float_t>;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an euler out of the \p roll, \p pitch, and \p yaw
      ///        angles
      ///
      /// \param roll the angle with respect to the Y axis
      /// \param pitch the angle with respect to the X axis
      /// \param yaw the angle with respect to the Z axis
      constexpr euler( radian roll, radian pitch, radian yaw ) noexcept;

      /// \brief Constructs an euler out of a quaternion
      ///
      /// \param q the quaternion
      euler( const quaternion& q ) noexcept;

      /// \brief Constructs an euler from a 3x3 rotation matrix
      ///
      /// \param rot the rotation matrix
      explicit euler( const matrix3_type& rot ) noexcept;

      /// \brief Constructs an euler from a 4x4 rotation matrix
      ///
      /// \param rot the rotation matrix
      explicit euler( const matrix4_type& rot ) noexcept;

      /// \brief Copy-constructs an euler from another euler
      ///
      /// \param other the other euler to copy
      constexpr euler( const euler& other ) noexcept = default;

      /// \brief Move-constructs an euler from another euler
      ///
      /// \param other the other euler to move
      constexpr euler( euler&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns this euler from another euler
      ///
      /// \param other the other euler to copy
      euler& operator=( const euler& other ) noexcept = default;

      /// \brief Move-assigns this euler from another euler
      ///
      /// \param other the other euler to move
      euler& operator=( euler&& other ) noexcept = default;

      /// \brief Assigns this euler from a quaternion
      ///
      /// \param q the quaternion to assign
      euler& operator=( const quaternion& q ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Retrieves the yaw angle
      ///
      /// \param the yaw angle
      constexpr radian yaw() const noexcept;

      /// \brief Retrieves the pitch angle
      ///
      /// \param the pitch angle
      constexpr radian pitch() const noexcept;

      /// \brief Retrieves the roll angle
      ///
      /// \param the rolll angle
      constexpr radian roll() const noexcept;

      /// \brief Calculates and returns the forward, right, and up axes
      ///        as vectors
      ///
      /// \return a tuple containing the forward, right, and up vector axes
      std::tuple<vector_type,vector_type,vector_type> axes() const noexcept;

      //----------------------------------------------------------------------

      /// \brief Retrives a normalized euler
      ///
      /// \note A normalized euler clamps the angles between +/- pi/2
      ///
      /// \return the normalized euler
      euler normalized() const noexcept;

      /// \brief Retrieves a unit vector in the direction of the angles
      ///
      /// \return the new direction
      vector_type direction() const noexcept;

      /// \brief Retrieves the 3x3 rotation matrix
      ///
      /// \return the 3x3 rotation matrix
      matrix3_type rotation_matrix() const noexcept;

      /// \brief Converts this euler to a quaternion
      explicit operator quaternion() const noexcept;

      //----------------------------------------------------------------------
      // Extraction
      //----------------------------------------------------------------------
    public:

      /// \brief Extracts a 3x3 rotation matrix from this euler
      ///
      /// \param rot pointer to the rotation matrix to extract into
      void extract_rotation_matrix( matrix3_type* rot ) const noexcept;

      /// \brief Extracts a 4x4 rotation matrix from this euler
      ///
      /// \param rot pointer to the rotation matrix to extract into
      void extract_rotation_matrix( matrix4_type* rot ) const noexcept;

      /// \brief Extracts a unit direction vector from this euler
      ///
      /// \param vec the vector to extract into
      void extract_direction( vector_type* vec ) const noexcept;

      /// \brief Extracts the forward, right, and up axes
      ///
      /// \param forward the forward vector
      /// \param right the right vector
      /// \param up the up vector
      void extract_axis( vector_type* forward,
                         vector_type* right,
                         vector_type* up ) const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Clamps all angles by \p yaw, \p pitch, and \p roll
      ///
      /// \param yaw the yaw angle to clamp
      /// \param pitch the pitch angle to clamp
      /// \param roll the roll angle to clamp
      /// \return reference to \c (*this)
      euler& clamp( radian yaw, radian pitch, radian roll ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Clamps the yaw angle by \p limit
      ///
      /// \param limit the angle to clamp to
      /// \return reference to \c (*this)
      euler& clamp_yaw( radian limit ) noexcept;

      /// \brief Clamps the pitch angle by \p limit
      ///
      /// \param limit the angle to clamp to
      /// \return reference to \c (*this)
      euler& clamp_pitch( radian limit ) noexcept;

      /// \brief Clamps the roll angle by \p limit
      ///
      /// \param limit the angle to clamp to
      /// \return reference to \c (*this)
      euler& clamp_roll( radian limit ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Swaps \c (*this) with \p other
      ///
      /// \param other the other \ref euler to swap with
      void swap( euler& other ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Normalizes this euler between +/- pi/2
      ///
      /// \return reference to \c (*this)
      euler& normalize() noexcept;

      /// \brief Rotates this euler about the angles \p roll, \p pitch,
      ///        and \p yaw
      ///
      /// \param roll the roll angle
      /// \param pitch the pitch angle
      /// \param yaw the yaw angle
      /// \return reference to \c (*this)
      euler& rotate( radian roll, radian pitch, radian yaw ) noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Rotates this euler about the angles of the \p rhs euler
      ///
      /// \note This has the same effect as calling
      ///       \code
      ///       rotate( rhs.roll(), rhs.pitch(), rhs.yaw() )
      ///       \endcode
      ///
      /// \param rhs the other euler
      /// \return reference to \c (*this)
      euler& operator+=( const euler& rhs ) noexcept;

      /// \brief Rotates this euler about the angles of the \p rhs euler
      ///
      /// \note This has the same effect as calling
      ///       \code
      ///       rotate( -rhs.roll(), -rhs.pitch(), -rhs.yaw() )
      ///       \endcode
      ///
      /// \param rhs the other euler
      /// \return reference to \c (*this)
      euler& operator-=( const euler& rhs ) noexcept;

      /// \brief Scales each angle of this euler by \p scalar
      ///
      /// \param scalar the scalar to multiply each angle by
      /// \return reference to \c (*this)
      euler& operator*=( float_t scalar ) noexcept;

      /// \brief Scales each angle of this euler by the inverse of \p scalar
      ///
      /// \param scalar the scalar to divide each angle by
      /// \return reference to \c (*this)
      euler& operator/=( float_t scalar ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      radian m_roll;  ///< The roll-angle
      radian m_pitch; ///< The pitch-angle
      radian m_yaw;   ///< The yaw-angle

      //----------------------------------------------------------------------
      // Private Member Functions
      //----------------------------------------------------------------------
    private:

      /// \brief Clamps the \p angle between +/- \p clamp
      ///
      /// \param angle the angle to clamp
      /// \param clamp the range to clamp
      /// \return the clamped angle
      static void clamp_angle( radian* angle, radian clamp ) noexcept;

      /// \brief Wraps an angle between -2pi to 2pi
      ///
      /// \param angle the angle to wrap
      static void wrap_angle( radian* angle ) noexcept;

      /// \brief Assigns the \ref quaternion \p q to this \ref euler
      ///
      /// \param q the quaternion
      void from_quaternion( const quaternion& q ) noexcept;

      /// \brief Assigns the \ref matrix3 \p rot to this \ref euler
      ///
      /// \param rot the rotation matrix
      void from_rotation_matrix( const matrix3_type& rot ) noexcept;

      /// \brief Assigns the \ref matrix4 \p rot to this \ref euler
      ///
      /// \param rot the rotation matrix
      void from_rotation_matrix( const matrix4_type& rot ) noexcept;
    };

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps the eulers at \p lhs with \p rhs
    ///
    /// \param lhs the left euler
    /// \param rhs the right euler
    void swap( euler& lhs, euler& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Operators
    //------------------------------------------------------------------------

    euler operator + ( const euler& lhs, const euler& rhs ) noexcept;
    euler operator - ( const euler& lhs, const euler& rhs ) noexcept;
    euler operator * ( const euler& lhs, float_t rhs ) noexcept;
    euler operator * ( float_t lhs, const euler& rhs ) noexcept;
    quaternion operator * ( const euler& lhs, const euler& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    constexpr bool operator == ( const euler& lhs, const euler& rhs ) noexcept;

    constexpr bool operator != ( const euler& lhs, const euler& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Determines whether two euler angles are almost equal
    ///
    /// \param lhs the left euler
    /// \param rhs the right euler
    /// \return \c true if \p lhs is almost equal to \p rhs
    constexpr bool almost_equal( const euler& lhs, const euler& rhs ) noexcept;

    /// \brief Determines whether two euler angles are almost equal,
    ///        relative to \p tolerance
    ///
    /// \param lhs the left euler
    /// \param rhs the right euler
    /// \param tolerance the tolerance to compare against
    /// \return \c true if \p lhs is almost equal to \p rhs
    template<typename Arithmetic, std::enable_if<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const euler& lhs, const euler& rhs, Arithmetic tolerance ) noexcept;

    //------------------------------------------------------------------------
    // Type Traits
    //------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref euler
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_euler : std::false_type{};

    template<> struct is_euler<euler> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_euler
    template<typename T>
    constexpr bool is_euler_v = is_euler<T>::value;

  } // namespace math
} // namespace bit

#include "detail/euler.inl"

#endif /* BIT_MATH_EULER_HPP */
