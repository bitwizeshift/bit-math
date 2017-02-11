/**
 * \file degree.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_DETAIL_ANGLES_DEGREE_HPP
#define BIT_MATH_DETAIL_ANGLES_DEGREE_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief Represents an angle in degrees.
    ///
    /// A purely inline class to abstract the concept of a 'Degrees'.
    ///
    /// The degree class is provided as a utility, and its precision is specified
    /// at compile-time with compile-time defines
    //////////////////////////////////////////////////////////////////////////
    class degree
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

      /// \brief Default constructs a degree.
      ///
      /// The angle is in an undefined state until it is assigned
      constexpr degree() noexcept;

      /// \brief Constructs a degree from the given floating point value
      ///
      /// \param value the value of the degree angle
      constexpr explicit degree( value_type value ) noexcept;

      /// \brief Copy-constructs a degree from another degree
      ///
      /// \param other the other degree to copy
      constexpr degree( const degree& other ) noexcept = default;

      /// \brief Move-constructs a degree from another degree
      ///
      /// \param other the other degree to move
      constexpr degree( degree&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a degree from another degree
      ///
      /// \param other the other degree to copy
      constexpr degree& operator=( const degree& other ) noexcept = default;

      /// \brief Move-assigns a degree from another degree
      ///
      /// \param other the other degree to move
      constexpr degree& operator=( degree&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the value decimal value of the angle
      ///
      /// \return the value of the angle
      constexpr value_type value() const noexcept;

      /// \brief Counts the number of revolutions for the current \ref degree
      ///
      /// \return the number of revolutions
      constexpr value_type revolutions() const noexcept;

      /// \brief Constrains the \ref degree between \c 0 and \c 360
      ///
      /// \return the constrained \ref degree
      degree constrained() const noexcept;

      //----------------------------------------------------------------------
      // Mutators
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps this \ref radian with another one
      ///
      /// \param other the other radian
      void swap( degree& other ) noexcept;

      //----------------------------------------------------------------------
      // Compound Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Compound add-assignment operator
      ///
      /// \param rhs the degree to add
      /// \return reference to \c (*this)
      degree& operator+=( const degree& rhs ) noexcept;

      /// \brief Compound subdtract-assignment operator
      ///
      /// \param rhs the degree to subtract
      /// \return reference to \c (*this)
      degree& operator-=( const degree& rhs ) noexcept;

      /// \brief Compound multiply-assignment operator
      ///
      /// \param rhs the multipllier
      /// \return reference to \c (*this)
      degree& operator*=( value_type rhs ) noexcept;

      /// \brief Compound division-assignment operator
      ///
      /// \param rhs the divisor
      /// \return reference to \c (*this)
      degree& operator/=( value_type rhs ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_angle;
    };

    //------------------------------------------------------------------------
    // Inline Operators
    //------------------------------------------------------------------------

    /// \brief Adds the degrees \c lhs to \c rhs
    ///
    /// \param lhs the degree on the left side of the equation
    /// \param rhs the degree on the right side of the equation
    /// \return the result of \c lhs + \c rhs
    constexpr degree operator + ( const degree& lhs, const degree& rhs ) noexcept;

    /// \brief Subtracts the degrees \c rhs from \c lhs
    ///
    /// \param lhs the degree on the left side of the equation
    /// \param rhs the degree on the right side of the equation
    /// \return the result of \c lhs - \c rhs
    constexpr degree operator - ( const degree& lhs, const degree& rhs ) noexcept;

    /// \brief Multiplies \c lhs by the multiplier \c rhs
    ///
    /// \param lhs the degree on the left side of the equation
    /// \param rhs the float multiplier
    /// \return the result of \c lhs * \c rhs
    constexpr degree operator * ( const degree& lhs, radian::value_type rhs ) noexcept;

    /// \brief Divides the degree \c lhs by the divisor \c rhs
    ///
    /// \param lhs the degree on the left side of the equation
    /// \param rhs the float divisor
    /// \return the result of \c lhs / \c rhs
    constexpr degree operator / ( const degree& lhs, radian::value_type rhs ) noexcept;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps \p lhs and \p rhs
    ///
    /// \param lhs the left degree to swap
    /// \param rhs the right degree to swap
    void swap( degree& lhs, degree& rhs ) noexcept;

  } // namespace math
} // namespace bit

#include "degree.inl"

#endif /* BIT_MATH_DETAIL_ANGLES_DEGREE_HPP */
