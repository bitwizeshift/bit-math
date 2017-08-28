/**
 * \file gradian.hpp
 *
 * \brief This internal header defines a type representing a gradian angle
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_MATH_DETAIL_ANGLES_GRADIAN_HPP
#define BIT_MATH_DETAIL_ANGLES_GRADIAN_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief Represents an angle in gradians.
    ///
    /// A purely inline class to abstract the concept of a 'Gradians'.
    ///
    /// The gradian class is provided as a utility, and its precision is specified
    /// at compile-time with compile-time defines
    //////////////////////////////////////////////////////////////////////////
    class gradian
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

      static const gradian revolution;
      static const gradian half_revolution;
      static const gradian quarter_revolution;
      static const gradian neg_revolution;
      static const gradian neg_half_revolution;
      static const gradian neg_quarter_revolution;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a gradian.
      ///
      /// The angle defaults to 0 gradians
      constexpr gradian() noexcept;

      /// \brief Constructs a gradian from the given floating point value
      ///
      /// \param value the value of the gradian angle
      constexpr explicit gradian( value_type value ) noexcept;

      /// \brief Copy-constructs a gradian from another gradian
      ///
      /// \param other the other gradian to copy
      constexpr gradian( const gradian& other ) noexcept = default;

      /// \brief Move-constructs a gradian from another gradian
      ///
      /// \param other the other gradian to move
      constexpr gradian( gradian&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a gradian from another gradian
      ///
      /// \param other the other gradian to copy
      constexpr gradian& operator=( const gradian& other ) noexcept = default;

      /// \brief Move-assigns a gradian from another gradian
      ///
      /// \param other the other gradian to move
      constexpr gradian& operator=( gradian&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the value decimal value of the angle
      ///
      /// \return the value of the angle
      constexpr value_type value() const noexcept;

      /// \brief Counts the number of revolutions for the current \ref gradian
      ///
      /// \return the number of revolutions
      constexpr value_type revolutions() const noexcept;

      /// \brief Constrains the \ref gradian between \c 0 and \c 400
      ///
      /// \return the constrained \ref gradian
      gradian constrained() const noexcept;

      //----------------------------------------------------------------------
      // Mutators
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps this \ref gradian with another one
      ///
      /// \param other the other gradian
      void swap( gradian& other ) noexcept;

      //----------------------------------------------------------------------
      // Unary Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Unary operator that returns itself
      ///
      /// \return itself
      constexpr gradian operator+() const noexcept;

      /// \brief Unary negation operator
      ///
      /// \return negated gradian
      constexpr gradian operator-() const noexcept;

      //----------------------------------------------------------------------
      // Compound Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Compound add-assignment operator
      ///
      /// \param rhs the gradian to add
      /// \return reference to \c (*this)
      gradian& operator+=( const gradian& rhs ) noexcept;

      /// \brief Compound subdtract-assignment operator
      ///
      /// \param rhs the gradian to subtract
      /// \return reference to \c (*this)
      gradian& operator-=( const gradian& rhs ) noexcept;

      /// \brief Compound multiply-assignment operator
      ///
      /// \param rhs the multipllier
      /// \return reference to \c (*this)
      gradian& operator*=( value_type rhs ) noexcept;

      /// \brief Compound division-assignment operator
      ///
      /// \param rhs the divisor
      /// \return reference to \c (*this)
      gradian& operator/=( value_type rhs ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_angle;
    };

    //------------------------------------------------------------------------
    // Inline Operators
    //------------------------------------------------------------------------

    /// \brief Adds the gradians \c lhs to \c rhs
    ///
    /// \param lhs the gradian on the left side of the equation
    /// \param rhs the gradian on the right side of the equation
    /// \return the result of \c lhs + \c rhs
    constexpr gradian operator + ( const gradian& lhs, const gradian& rhs ) noexcept;

    /// \brief Subtracts the gradians \c rhs from \c lhs
    ///
    /// \param lhs the gradian on the left side of the equation
    /// \param rhs the gradian on the right side of the equation
    /// \return the result of \c lhs - \c rhs
    constexpr gradian operator - ( const gradian& lhs, const gradian& rhs ) noexcept;

    /// \brief Multiplies \c lhs by the multiplier \c rhs
    ///
    /// \param lhs the gradian on the left side of the equation
    /// \param rhs the float multiplier
    /// \return the result of \c lhs * \c rhs
    constexpr gradian operator * ( const gradian& lhs, gradian::value_type rhs ) noexcept;

    /// \brief Multiplies \c rhs by the multiplier \c lhs
    ///
    /// \param lhs the float multiplier
    /// \param rhs the gradian on the left side of the equation
    /// \return the result of \c lhs * \c rhs
    constexpr gradian operator*( gradian::value_type rhs, const gradian& lhs ) noexcept;

    /// \brief Divides the gradian \c lhs by the divisor \c rhs
    ///
    /// \param lhs the gradian on the left side of the equation
    /// \param rhs the float divisor
    /// \return the result of \c lhs / \c rhs
    constexpr gradian operator / ( const gradian& lhs, gradian::value_type rhs ) noexcept;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps \p lhs and \p rhs
    ///
    /// \param lhs the left gradian to swap
    /// \param rhs the right gradian to swap
    void swap( gradian& lhs, gradian& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Determines exact equality between two gradian
    ///
    /// \param lhs the left gradian
    /// \param rhs the right gradian
    /// \return \c true if the two gradian contain identical values
    constexpr bool operator == ( const gradian& lhs, const gradian& rhs ) noexcept;

    /// \brief Determines exact inequality between two gradian
    ///
    /// \param lhs the left gradian
    /// \param rhs the right gradian
    /// \return \c true if the two gradian contain at least 1 different value
    constexpr bool operator != ( const gradian& lhs, const gradian& rhs ) noexcept;

    /// \brief Determines whether \p lhs is numerically less than \p rhs
    ///
    /// \param lhs the left gradian
    /// \param rhs the right gradian
    /// \return \c true if \p lhs < \p rhs
    constexpr bool operator < ( const gradian& lhs, const gradian& rhs ) noexcept;

    /// \brief Determines whether \p lhs is numerically greater than \p rhs
    ///
    /// \param lhs the left gradian
    /// \param rhs the right gradian
    /// \return \c true if \p lhs > \p rhs
    constexpr bool operator > ( const gradian& lhs, const gradian& rhs ) noexcept;

    /// \brief Determines whether \p lhs is numerically less than or equal
    ///        to \p rhs
    ///
    /// \param lhs the left gradian
    /// \param rhs the right gradian
    /// \return \c true if \p lhs <= \p rhs
    constexpr bool operator <= ( const gradian& lhs, const gradian& rhs ) noexcept;

    /// \brief Determines whether \p lhs is numerically greater than or equal
    ///        to \p rhs
    ///
    /// \param lhs the left gradian
    /// \param rhs the right gradian
    /// \return \c true if \p lhs >= \p rhs
    constexpr bool operator >= ( const gradian& lhs, const gradian& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two gradian relative to \ref default_tolerance
    ///
    /// \param lhs the left gradian
    /// \param rhs the right gradian
    /// \return \c true if the two gradian contain almost equal values
    constexpr bool almost_equal( const gradian& lhs, const gradian& rhs ) noexcept;

    /// \brief Determines equality between two gradian relative to \ref tolerance
    ///
    /// \param lhs the left gradian
    /// \param rhs the right gradian
    /// \return \c true if the two gradian contain almost equal values
    template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const gradian& lhs,
                                 const gradian& rhs,
                                 Arithmetic tolerance ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref gradian
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_gradian : std::false_type{};

    template<> struct is_gradian<gradian> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_gradian
    template<typename T>
    constexpr bool is_gradian_v = is_gradian<T>::value;

  } // namespace math
} // namespace bit

#include "gradian.inl"

#endif /* BIT_MATH_DETAIL_ANGLES_GRADIAN_HPP */
