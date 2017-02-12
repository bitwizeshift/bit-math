/**
 * \file radian.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
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

#ifdef BIT_MATH_DOUBLE_PRECISION
      using value_type = double;
#else
      using value_type = float;
#endif

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

  } // namespace math
} // namespace bit

#include "radian.inl"

#endif /* BIT_MATH_DETAIL_ANGLES_RADIAN_HPP */
