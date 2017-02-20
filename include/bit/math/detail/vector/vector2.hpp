/**
 * \file vector2.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_DETAIL_VECTOR_VECTOR2_HPP
#define BIT_MATH_DETAIL_VECTOR_VECTOR2_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief This object represents a 2-component vector in linear algebra
    ///
    /// Most operations are marked \c constexpr to allow for compile-time
    /// forward-calculations of vector sums and products.
    ///
    /// Operations on this type are able to promote results to reduce loss of
    /// data, depending on what the operands are.
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class vector2
    {
      //----------------------------------------------------------------------
      // Public Types
      //----------------------------------------------------------------------
    public:

      using value_type      = std::decay_t<T>;
      using pointer         = value_type*;
      using const_pointer   = const value_type*;
      using reference       = value_type&;
      using const_reference = const value_type&;

      using size_type  = std::size_t;
      using index_type = std::ptrdiff_t;

      //----------------------------------------------------------------------
      // Public Constants
      //----------------------------------------------------------------------
    public:

      static const vector2<T> zero;   ///< A zero-length vector
      static const vector2<T> unit_x; ///< A unit-vector in the x-direction
      static const vector2<T> unit_y; ///< A unit-vector in the y-direction

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a vector2 with an undefined value
      constexpr vector2() = default;

      /// \brief Constructs a vector2 with a given \p scalar value per
      ///        component
      ///
      /// \param scalar the value to issue per component
      constexpr explicit vector2( value_type scalar ) noexcept;

      /// \brief Constructs a vector2 with a given \p magnitude
      ///        and \p direction
      ///
      /// \param magnitude the distance of the vector
      /// \param direction the angle of the vector
      vector2( value_type magnitude, radian direction ) noexcept;

      /// \brief Constructs a vector2 with components \p x and \p y
      ///
      /// \param x the x-component of the vector2
      /// \param y the y-component of the vector2
      constexpr vector2( value_type x, value_type y ) noexcept;

      /// \brief Copy-constructs a vector2 with the value of another
      ///        vector2
      ///
      /// \param other the other vector2 to copy
      constexpr vector2( const vector2& other ) noexcept = default;

      /// \brief Move-constructs a vector2 with the value of another
      ///        vector2
      ///
      /// \param other the other vector2 to move
      constexpr vector2( vector2&& other ) noexcept = default;

      /// \brief Copy-converts a vector2 with the value of another
      ///        vector2
      ///
      /// \param other the other vector2 to copy
      template<typename U>
      constexpr vector2( const vector2<U>& other ) noexcept;

      /// \brief Move-converts a vector2 with the value of another
      ///        vector2
      ///
      /// \param other the other vector2 to move
      template<typename U>
      constexpr vector2( vector2<U>&& other ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns \p other to \c this
      ///
      /// \param other the other vector2 to copy
      /// \return reference to \c (*this)
      vector2& operator=( const vector2& other ) = default;

      /// \brief Move-assigns \p other to \c this
      ///
      /// \param other the other vector2 to move
      /// \return reference to \c (*this)
      vector2& operator=( vector2&& other ) = default;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the number of components in the vector2
      ///
      /// \return the number of components in the vector2
      constexpr size_type size() const noexcept;

      /// \brief Gets the x component of this vector
      ///
      /// \return reference to the x component
      constexpr reference x() noexcept;

      /// \copydoc vector2::x()
      constexpr const_reference x() const noexcept;

      /// \brief Gets the y component of this vector
      ///
      /// \return reference to the y component
      constexpr reference y() noexcept;

      /// \copydoc vector2::y()
      constexpr const_reference y() const noexcept;

      /// \brief Gets a pointer to the underlying data
      ///
      /// \return a pointer to the data
      constexpr pointer data() noexcept;

      /// \copydoc vector2::ptr()
      constexpr const_pointer data() const noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the entry at the \p n position
      ///
      /// \throw std::out_of_range if \p n >= 2
      ///
      /// \return reference to the \p n entry
      constexpr reference at( index_type n );

      /// \copydoc vector2::at( index_type )
      constexpr const_reference at( index_type n ) const;

      /// \brief Gets the entry at the \p n position
      ///
      /// \note Undefined behaviour if \p n >= 2
      ///
      /// \return reference to the \p n entry
      constexpr reference operator[]( index_type n ) noexcept;

      /// \copydoc vector2::operator[]( index_type )
      constexpr const_reference operator[]( index_type n ) const noexcept;

      //----------------------------------------------------------------------
      // Quantifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Determines the dot-product of \c this and \p rhs
      ///
      /// \param rhs the other vector2 to perform the dot-product with
      /// \return the dot product of \c this and \p rhs
      template<typename U>
      constexpr std::common_type_t<T,U>
        dot( const vector2<U>& rhs ) const noexcept;

      /// \brief Calculates the cross-product of \c this and \p rhs
      ///
      /// \param rhs the other vector2 to perform the cross-product with
      /// \return the cross product of \c this and \p rhs
      template<typename U>
      constexpr std::common_type_t<T,U>
        cross( const vector2<U>& rhs ) const noexcept;

      /// \brief Gets the magnitude of this vector2
      ///
      /// \return the magnitude of the vector2
      value_type magnitude() const noexcept;

      /// \brief Gets the midpoint between \c this and \p vec
      ///
      /// \param vec the vector2 to get the midpoint from
      /// \return the midpoint between \c this and \p vec
      template<typename U>
      constexpr vector2<std::common_type_t<T,U>>
        midpoint( const vector2<U>& vec ) const noexcept;

      /// \brief Gets the reflection vector2 of \c this reflected through the
      ///        \p normal
      ///
      /// \param normal the normal vector2
      /// \return the reflection
      template<typename U>
      constexpr vector2<std::common_type_t<T,U>>
        reflection( const vector2<U>& normal ) const noexcept;

      /// \brief Gets the perpendicular of this vector2
      ///
      /// \return the perpendicular vector2 to \c this
      constexpr vector2<T> perpendicular() const noexcept;

      /// \brief Gets the normalized vector2 of \c this
      ///
      /// \param the normalized vector2 of \c this
      vector2<T> normalized() const noexcept;

      /// \brief Gets the inverse of \c this vector2
      ///
      /// \return the inverse of \c this vector2
      constexpr vector2<T> inverse() const noexcept;

      /// \brief Determines the angle between \c this and \p other
      ///
      /// \param other the other vector to determine the angle between
      /// \return the angle between \c this and \p other
      template<typename U>
      radian angle_between( const vector2<U>& other ) const noexcept;

      /// \brief Determines the angle from \p to \p other
      ///
      /// \param other the other vector to get the angle to
      /// \return the angle from \c this to \p other
      template<typename U>
      radian angle_to( const vector2<U>& other ) const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps the vector2 from \c this to \p other
      ///
      /// \param other the other entry to swap
      constexpr void swap( vector2& other ) noexcept;

      /// \brief Normalizes this vector2 and returns a reference to \c (*this)
      ///
      /// \return the reference to \c (*this)
      constexpr vector2<T>& normalize() noexcept;

      /// \brief Inverts this vector2 and returns a reference to \c (*this)
      ///
      /// \return the reference to \c (*this)
      constexpr vector2<T>& invert() noexcept;

      //----------------------------------------------------------------------
      // Unary Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Unary + operator
      ///
      /// \return A reference to \c (*this)
      constexpr const vector2<T>& operator+() const noexcept;

      /// \brief Negates this vector2's magnitude and direction
      ///
      /// \return the inverse of this vector2
      constexpr vector2<T> operator-() const noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Adds \p rhs to \c this
      ///
      /// \param rhs the vector2 to add to \c this
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector2<T>& operator+=( const vector2<U>& rhs ) noexcept;

      /// \brief Subtracts \p rhs from \c this
      ///
      /// \param rhs the vector2 to subtract from \c this
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector2<T>& operator-=( const vector2<U>& rhs ) noexcept;

      /// \brief Multiplies \c this by \p scalar
      ///
      /// \param scalar the scalar multiplier to modify this vector2 by
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector2<T>& operator*=( U&& scalar ) noexcept;

      /// \brief Divides \c this by \p scalar
      ///
      /// \param scalar the scalar divisor to modify this vector2 by
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector2<T>& operator/=( U&& scalar ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_data[2]; ///< The storage data
    };

    //------------------------------------------------------------------------
    // Free Operators
    //------------------------------------------------------------------------

    /// \brief Adds two vector2s
    ///
    /// \param lhs the left vector2
    /// \param rhs the right vector2
    /// \return the result of \p lhs + \p rhs
    template<typename T, typename U>
    constexpr vector2<std::common_type_t<T,U>>
      operator+( const vector2<T>& lhs, const vector2<U>& rhs ) noexcept;

    /// \brief Subtracts two vector2s
    ///
    /// \param lhs the left vector2
    /// \param rhs the right vector2
    /// \return the result of \p lhs - \p rhs
    template<typename T, typename U>
    constexpr vector2<std::common_type_t<T,U>>
      operator-( const vector2<T>& lhs, const vector2<U>& rhs ) noexcept;

    /// \brief Multiplies a vector2 by a scalar multiplier
    ///
    /// \param lhs the left vector2
    /// \param scalar the scalar to multiply by
    /// \return the result of \p lhs * \c scalar
    template<typename T, typename U>
    constexpr vector2<std::common_type_t<T,U>>
      operator*( const vector2<T>& lhs, U&& scalar ) noexcept;

    /// \brief Multiplies a vector2 by a scalar multiplier
    ///
    /// \param lhs the left vector2
    /// \param scalar the scalar to multiply by
    /// \return the result of \p scalar * \c rhs
    template<typename T, typename U>
    constexpr vector2<std::common_type_t<T,U>>
      operator*( U&& scalar, const vector2<T>& rhs ) noexcept;

    /// \brief Divides a vector2 by a scalar constant
    ///
    /// \param lhs the left vector2
    /// \param scalar the scalar to multiply by
    /// \return the result of \p lhs / \c scalar
    template<typename T, typename U>
    constexpr vector2<std::common_type_t<T,U>>
      operator/( const vector2<T>& lhs, U&& scalar ) noexcept;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Performs the dot product between \p lhs and \p rhs
    ///
    /// \param lhs the left vector2
    /// \param rhs the right vector2
    /// \return
    template<typename T, typename U>
    constexpr std::common_type_t<T,U>
      dot( const vector2<T>& lhs, const vector2<U>& rhs ) noexcept;

    /// \brief Calculates the magnitude of the vector2 \p vec
    ///
    /// \param vec the vector2 to calculate the magnitude from
    /// \return the magnitude
    template<typename T>
    typename vector2<T>::value_type magnitude( const vector2<T>& vec ) noexcept;

    /// \brief Swaps \p lhs with \p rhs
    ///
    /// \param lhs the left vector2 to swap
    /// \param rhs the right vector2 to swap
    template<typename T>
    constexpr void swap( vector2<T>& lhs, vector2<T>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Determines exact equality between two vector2
    ///
    /// \param lhs the left vector2
    /// \param rhs the right vector2
    /// \return \c true if the two vector2 contain identical values
    template<typename T, typename U>
    constexpr bool operator == ( const vector2<T>& lhs, const vector2<U>& rhs ) noexcept;

    /// \brief Determines exact inequality between two vector2
    ///
    /// \param lhs the left vector2
    /// \param rhs the right vector2
    /// \return \c true if the two vector2 contain at least 1 different value
    template<typename T, typename U>
    constexpr bool operator != ( const vector2<T>& lhs, const vector2<U>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two vector2 relative to \ref default_tolerance
    ///
    /// \param lhs the left vector2
    /// \param rhs the right vector2
    /// \return \c true if the two vector2 contain almost equal values
    template<typename T, typename U>
    constexpr bool almost_equal( const vector2<T>& lhs, const vector2<U>& rhs ) noexcept;

    /// \brief Determines equality between two vector2 relative to \ref tolerance
    ///
    /// \param lhs the left vector2
    /// \param rhs the right vector2
    /// \return \c true if the two vector2 contain almost equal values
    template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const vector2<T>& lhs,
                                 const vector2<U>& rhs,
                                 Arithmetic tolerance ) noexcept;

  } // namespace math
} // namespace bit

#include "vector2.inl"

#endif /* BIT_MATH_DETAIL_VECTOR_VECTOR2_HPP */
