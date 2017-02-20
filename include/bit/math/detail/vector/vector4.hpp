/**
 * \file vector4.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_DETAIL_VECTOR_VECTOR4_HPP
#define BIT_MATH_DETAIL_VECTOR_VECTOR4_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class vector4
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

      static const vector4<T> zero;   ///< Zero length vector
      static const vector4<T> unit_x; ///< A unit vector in the x-direction
      static const vector4<T> unit_y; ///< A unit vector in the y-direction
      static const vector4<T> unit_z; ///< A unit vector in the z-direction
      static const vector4<T> unit_w; ///< A unit vector in the w-direction

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a vector4 with an undefined value
      constexpr vector4() = default;

      /// \brief Constructs a vector4 with a given \p scalar value per
      ///        component
      ///
      /// \param scalar the value to issue per component
      constexpr explicit vector4( value_type scalar ) noexcept;

      /// \brief Constructs a vector4 with components \p x and \p y
      ///
      /// \param x the x-component of the vector4
      /// \param y the y-component of the vector4
      /// \param z the z-component of the vector4
      /// \param w the w-component of the vector4
      constexpr vector4( value_type x,
                          value_type y,
                          value_type z,
                          value_type w ) noexcept;

      /// \brief Copy-constructs a vector4 with the value of another
      ///        vector4
      ///
      /// \param other the other vector4 to copy
      constexpr vector4( const vector4& other ) noexcept = default;

      /// \brief Move-constructs a vector4 with the value of another
      ///        vector4
      ///
      /// \param other the other vector4 to move
      constexpr vector4( vector4&& other ) noexcept = default;

      /// \brief Copy-converts a vector4 with the value of another
      ///        vector4
      ///
      /// \param other the other vector4 to copy
      template<typename U>
      constexpr vector4( const vector4<U>& other ) noexcept;

      /// \brief Move-converts a vector4 with the value of another
      ///        vector4
      ///
      /// \param other the other vector4 to move
      template<typename U>
      constexpr vector4( vector4<U>&& other ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns \p other to \c this
      ///
      /// \param other the other vector4 to copy
      /// \return reference to \c (*this)
      vector4& operator=( const vector4& other ) = default;

      /// \brief Move-assigns \p other to \c this
      ///
      /// \param other the other vector4 to move
      /// \return reference to \c (*this)
      vector4& operator=( vector4&& other ) = default;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the number of components in the vector4
      ///
      /// \return the number of components in the vector4
      constexpr size_type size() const noexcept;

      /// \brief Gets the x component of this vector
      ///
      /// \return reference to the x component
      constexpr reference x() noexcept;

      /// \copydoc vector4::x()
      constexpr const_reference x() const noexcept;

      /// \brief Gets the y component of this vector
      ///
      /// \return reference to the y component
      constexpr reference y() noexcept;

      /// \copydoc vector4::y()
      constexpr const_reference y() const noexcept;

      /// \brief Gets the z component of this vector
      ///
      /// \return reference to the z component
      constexpr reference z() noexcept;

      /// \copydoc vector4::z()
      constexpr const_reference z() const noexcept;

      /// \brief Gets the w component of this vector
      ///
      /// \return reference to the w component
      constexpr reference w() noexcept;

      /// \copydoc vector4::w()
      constexpr const_reference w() const noexcept;

      /// \brief Gets a pointer to the underlying data
      ///
      /// \return a pointer to the data
      constexpr pointer data() noexcept;

      /// \copydoc vector4::ptr()
      constexpr const_pointer data() const noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the entry at the \p n position
      ///
      /// \throw std::out_of_range if \p n >= 4
      ///
      /// \return reference to the \p n entry
      constexpr reference at( index_type n );

      /// \copydoc vector4::at( index_type )
      constexpr const_reference at( index_type n ) const;

      /// \brief Gets the entry at the \p n position
      ///
      /// \note Undefined behaviour if \p n >= 4
      ///
      /// \return reference to the \p n entry
      constexpr reference operator[]( index_type n ) noexcept;

      /// \copydoc vector4::operator[]( index_type )
      constexpr const_reference operator[]( index_type n ) const noexcept;

      //----------------------------------------------------------------------
      // Quantifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Determines the dot-product of \c this and \p rhs
      ///
      /// \param rhs the other vector4 to perform the dot-product with
      /// \return the dot product of \c this and \p rhs
      template<typename U>
      constexpr std::common_type_t<T,U>
        dot( const vector4<U>& rhs ) const noexcept;

      /// \brief Calculates the cross-product of \c this and \p rhs
      ///
      /// \note This cross-product is not a true 4-dimensional cross-product,
      ///       it is a cross product constrainted to 3-dimensions, clearing
      ///       the w-entry
      ///
      /// \param rhs the other vector4 to perform the cross-product with
      /// \return the cross product of \c this and \p rhs
      template<typename U>
      constexpr bit::math::vector4<std::common_type_t<T,U>>
        cross( const vector4<U>& rhs ) const noexcept;

      /// \brief Gets the magnitude of this vector4
      ///
      /// \return the magnitude of the vector4
      value_type magnitude() const noexcept;

      /// \brief Gets the midpoint between \c this and \p vec
      ///
      /// \param vec the vector4 to get the midpoint from
      /// \return the midpoint between \c this and \p vec
      template<typename U>
      constexpr vector4<std::common_type_t<T,U>>
        midpoint( const vector4<U>& vec ) const noexcept;

      /// \brief Gets the normalized vector4 of \c this
      ///
      /// \param the normalized vector4 of \c this
      vector4<T> normalized() const noexcept;

      /// \brief Gets the inverse of \c this vector4
      ///
      /// \return the inverse of \c this vector4
      constexpr vector4<T> inverse() const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps the vector4 from \c this to \p other
      ///
      /// \param other the other entry to swap
      constexpr void swap( vector4& other ) noexcept;

      /// \brief Normalizes this vector4 and returns a reference to \c (*this)
      ///
      /// \return the reference to \c (*this)
      constexpr vector4<T>& normalize() noexcept;

      /// \brief Inverts this vector4 and returns a reference to \c (*this)
      ///
      /// \return the reference to \c (*this)
      constexpr vector4<T>& invert() noexcept;

      //----------------------------------------------------------------------
      // Unary Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Unary + operator
      ///
      /// \return A reference to \c (*this)
      constexpr const vector4<T>& operator+() const noexcept;

      /// \brief Negates this vector4's magnitude and direction
      ///
      /// \return the inverse of this vector4
      constexpr vector4<T> operator-() const noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Adds \p rhs to \c this
      ///
      /// \param rhs the vector4 to add to \c this
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector4<T>& operator+=( const vector4<U>& rhs ) noexcept;

      /// \brief Subtracts \p rhs from \c this
      ///
      /// \param rhs the vector4 to subtract from \c this
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector4<T>& operator-=( const vector4<U>& rhs ) noexcept;

      /// \brief Multiplies \c this by \p scalar
      ///
      /// \param scalar the scalar multiplier to modify this vector4 by
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector4<T>& operator*=( U&& scalar ) noexcept;

      /// \brief Divides \c this by \p scalar
      ///
      /// \param scalar the scalar divisor to modify this vector4 by
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector4<T>& operator/=( U&& scalar ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_data[4]; ///< The storage data
    };

    //------------------------------------------------------------------------
    // Free Operators
    //------------------------------------------------------------------------

    /// \brief Adds two vector4s
    ///
    /// \param lhs the left vector4
    /// \param rhs the right vector4
    /// \return the result of \p lhs + \p rhs
    template<typename T, typename U>
    constexpr vector4<std::common_type_t<T,U>>
      operator+( const vector4<T>& lhs, const vector4<U>& rhs ) noexcept;

    /// \brief Subtracts two vector4s
    ///
    /// \param lhs the left vector4
    /// \param rhs the right vector4
    /// \return the result of \p lhs - \p rhs
    template<typename T, typename U>
    constexpr vector4<std::common_type_t<T,U>>
      operator-( const vector4<T>& lhs, const vector4<U>& rhs ) noexcept;

    /// \brief Multiplies a vector4 by a scalar multiplier
    ///
    /// \param lhs the left vector4
    /// \param scalar the scalar to multiply by
    /// \return the result of \p lhs * \c scalar
    template<typename T, typename U>
    constexpr vector4<std::common_type_t<T,U>>
      operator*( const vector4<T>& lhs, U&& scalar ) noexcept;

    /// \brief Multiplies a vector4 by a scalar multiplier
    ///
    /// \param lhs the left vector4
    /// \param scalar the scalar to multiply by
    /// \return the result of \p scalar * \c rhs
    template<typename T, typename U>
    constexpr vector4<std::common_type_t<T,U>>
      operator*( U&& scalar, const vector4<T>& rhs ) noexcept;

    /// \brief Divides a vector4 by a scalar constant
    ///
    /// \param lhs the left vector4
    /// \param scalar the scalar to multiply by
    /// \return the result of \p lhs / \c scalar
    template<typename T, typename U>
    constexpr vector4<std::common_type_t<T,U>>
      operator/( const vector4<T>& lhs, U&& scalar ) noexcept;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Performs the dot product between \p lhs and \p rhs
    ///
    /// \param lhs the left vector4
    /// \param rhs the right vector4
    /// \return
    template<typename T, typename U>
    constexpr std::common_type_t<T,U>
      dot( const vector4<T>& lhs, const vector4<U>& rhs ) noexcept;

    /// \brief Calculates the magnitude of the vector4 \p vec
    ///
    /// \param vec the vector4 to calculate the magnitude from
    /// \return the magnitude
    template<typename T>
    typename vector4<T>::value_type magnitude( const vector4<T>& vec ) noexcept;

    /// \brief Swaps \p lhs with \p rhs
    ///
    /// \param lhs the left vector4 to swap
    /// \param rhs the right vector4 to swap
    template<typename T>
    constexpr void swap( vector4<T>& lhs, vector4<T>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Determines exact equality between two vector4
    ///
    /// \param lhs the left vector4
    /// \param rhs the right vector4
    /// \return \c true if the two vector4 contain identical values
    template<typename T, typename U>
    constexpr bool operator == ( const vector4<T>& lhs, const vector4<U>& rhs ) noexcept;

    /// \brief Determines exact inequality between two vector4
    ///
    /// \param lhs the left vector4
    /// \param rhs the right vector4
    /// \return \c true if the two vector4 contain at least 1 different value
    template<typename T, typename U>
    constexpr bool operator != ( const vector4<T>& lhs, const vector4<U>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two vector4 relative to \ref default_tolerance
    ///
    /// \param lhs the left vector4
    /// \param rhs the right vector4
    /// \return \c true if the two vector4 contain almost equal values
    template<typename T, typename U>
    constexpr bool almost_equal( const vector4<T>& lhs, const vector4<U>& rhs ) noexcept;

    /// \brief Determines equality between two vector4 relative to \ref tolerance
    ///
    /// \param lhs the left vector4
    /// \param rhs the right vector4
    /// \return \c true if the two vector4 contain almost equal values
    template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const vector4<T>& lhs,
                                 const vector4<U>& rhs,
                                 Arithmetic tolerance ) noexcept;

  } // namespace math
} // namespace bit

#include "vector4.inl"

#endif /* BIT_MATH_DETAIL_VECTOR_VECTOR4_HPP */
