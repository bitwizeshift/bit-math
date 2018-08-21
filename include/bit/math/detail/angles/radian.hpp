/*****************************************************************************
 * \file
 * \brief This internal header defines a type representing a radian angle
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
#ifndef BIT_MATH_DETAIL_ANGLES_RADIAN_HPP
#define BIT_MATH_DETAIL_ANGLES_RADIAN_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief Represents an angle, in radians
    ///
    /// The radian class is provided as a utility, and its precision is
    /// specified at compile-time with compile-time defines
    //////////////////////////////////////////////////////////////////////////
    class radian
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type = float_t;

      //----------------------------------------------------------------------
      // Public Static Members
      //----------------------------------------------------------------------
    public:

      static const radian revolution;
      static const radian half_revolution;
      static const radian quarter_revolution;
      static const radian neg_revolution;
      static const radian neg_half_revolution;
      static const radian neg_quarter_revolution;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a radian.
      ///
      /// The angle defaults to 0 radians.
      constexpr radian() noexcept;

      /// \brief Constructs a radian from the given floating point value
      ///
      /// \param value the value of the radian angle
      constexpr explicit radian( value_type value ) noexcept;

      /// \brief Copy-constructs a radian from another radian
      ///
      /// \param other the other radian to copy
      constexpr radian( const radian& other ) noexcept = default;

      /// \brief Move-constructs a radian from another radian
      ///
      /// \param other the other radian to move
      constexpr radian( radian&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a radian from another radian
      ///
      /// \param other the other radian to copy
      constexpr radian& operator=( const radian& other ) noexcept = default;

      /// \brief Move-assigns a radian from another radian
      ///
      /// \param other the other radian to move
      constexpr radian& operator=( radian&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the value decimal value of the angle
      ///
      /// \return the value of the angle
      constexpr value_type value() const noexcept;

      /// \brief Counts the number of revolutions for the current \ref radian
      ///
      /// \return the number of revolutions
      constexpr value_type revolutions() const noexcept;

      /// \brief Constrains the \ref radian between \c 0 and \c 2-pi
      ///
      /// \return the constrained \ref radian
      radian constrained() const noexcept;

      //----------------------------------------------------------------------
      // Mutators
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps this \ref radian with another one
      ///
      /// \param other the other radian
      void swap( radian& other ) noexcept;

      //----------------------------------------------------------------------
      // Unary Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Unary operator that returns itself
      ///
      /// \return itself
      constexpr radian operator+() const noexcept;

      /// \brief Unary negation operator
      ///
      /// \return negated radian
      constexpr radian operator-() const noexcept;

      //----------------------------------------------------------------------
      // Compound Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Compound add-assignment operator
      ///
      /// \param rhs the radian to add
      /// \return reference to \c (*this)
      radian& operator+=( const radian& rhs ) noexcept;

      /// \brief Compound subdtract-assignment operator
      ///
      /// \param rhs the radian to subtract
      /// \return reference to \c (*this)
      radian& operator-=( const radian& rhs ) noexcept;

      /// \brief Compound multiply-assignment operator
      ///
      /// \param rhs the multipllier
      /// \return reference to \c (*this)
      radian& operator*=( value_type rhs ) noexcept;

      /// \brief Compound division-assignment operator
      ///
      /// \param rhs the divisor
      /// \return reference to \c (*this)
      radian& operator/=( value_type rhs ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_angle; ///< The angle of this radian
    };

    //------------------------------------------------------------------------
    // Inline Operators
    //------------------------------------------------------------------------

    /// \brief Adds the radians \c lhs to \c rhs
    ///
    /// \param lhs the radian on the left side of the equation
    /// \param rhs the radian on the right side of the equation
    /// \return the result of \c lhs + \c rhs
    constexpr radian operator+( const radian& lhs, const radian& rhs ) noexcept;

    /// \brief Subtracts the radians \c rhs from \c lhs
    ///
    /// \param lhs the radian on the left side of the equation
    /// \param rhs the radian on the right side of the equation
    /// \return the result of \c lhs - \c rhs
    constexpr radian operator-( const radian& lhs, const radian& rhs ) noexcept;

    /// \brief Multiplies \c lhs by the multiplier \c rhs
    ///
    /// \param lhs the radian on the left side of the equation
    /// \param rhs the float multiplier
    /// \return the result of \c lhs * \c rhs
    constexpr radian operator*( const radian& lhs, radian::value_type rhs ) noexcept;

    /// \brief Multiplies \c rhs by the multiplier \c lhs
    ///
    /// \param lhs the float multiplier
    /// \param rhs the radian on the left side of the equation
    /// \return the result of \c lhs * \c rhs
    constexpr radian operator*( radian::value_type rhs, const radian& lhs ) noexcept;

    /// \brief Divides the radian \c lhs by the divisor \c rhs
    ///
    /// \param lhs the radian on the left side of the equation
    /// \param rhs the float divisor
    /// \return the result of \c lhs / \c rhs
    constexpr radian operator/( const radian& lhs, radian::value_type rhs ) noexcept;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps \p lhs and \p rhs
    ///
    /// \param lhs the left radian to swap
    /// \param rhs the right radian to swap
    void swap( radian& lhs, radian& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    constexpr bool operator==( const radian& lhs, const radian& rhs ) noexcept;
    constexpr bool operator!=( const radian& lhs, const radian& rhs ) noexcept;
    constexpr bool operator<( const radian& lhs, const radian& rhs ) noexcept;
    constexpr bool operator>( const radian& lhs, const radian& rhs ) noexcept;
    constexpr bool operator<=( const radian& lhs, const radian& rhs ) noexcept;
    constexpr bool operator>=( const radian& lhs, const radian& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two radian relative to \ref default_tolerance
    ///
    /// \param lhs the left radian
    /// \param rhs the right radian
    /// \return \c true if the two radian contain almost equal values
    constexpr bool almost_equal( const radian& lhs, const radian& rhs ) noexcept;

    /// \brief Determines equality between two radian relative to \ref tolerance
    ///
    /// \param lhs the left radian
    /// \param rhs the right radian
    /// \return \c true if the two radian contain almost equal values
    template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const radian& lhs,
                                 const radian& rhs,
                                 Arithmetic tolerance ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref radian
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_radian : std::false_type{};

    template<> struct is_radian<radian> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_radian
    template<typename T>
    constexpr bool is_radian_v = is_radian<T>::value;

  } // namespace math
} // namespace bit

#include "radian.inl"

#endif /* BIT_MATH_DETAIL_ANGLES_RADIAN_HPP */
