/**
 * \file vector3.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_DETAIL_VECTOR_VECTOR3_HPP
#define BIT_MATH_DETAIL_VECTOR_VECTOR3_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class vector3
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

      static const vector3<T> zero;   ///< A zero-length vector
      static const vector3<T> unit_x; ///< A unit-vector in the x-direction
      static const vector3<T> unit_y; ///< A unit-vector in the y-direction
      static const vector3<T> unit_z; ///< A unit-vector in the z-direction

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a vector3 with an undefined value
      constexpr vector3() = default;

      /// \brief Constructs a vector3 with a given \p scalar value per
      ///        component
      ///
      /// \param scalar the value to issue per component
      constexpr explicit vector3( value_type scalar ) noexcept;

      /// \brief Constructs a vector3 with components \p x and \p y
      ///
      /// \param x the x-component of the vector3
      /// \param y the y-component of the vector3
      /// \param z the z-component of the vector3
      constexpr vector3( value_type x, value_type y, value_type z ) noexcept;

      /// \brief Copy-constructs a vector3 with the value of another
      ///        vector3
      ///
      /// \param other the other vector3 to copy
      constexpr vector3( const vector3& other ) noexcept = default;

      /// \brief Move-constructs a vector3 with the value of another
      ///        vector3
      ///
      /// \param other the other vector3 to move
      constexpr vector3( vector3&& other ) noexcept = default;

      /// \brief Copy-converts a vector3 with the value of another
      ///        vector3
      ///
      /// \param other the other vector3 to copy
      template<typename U>
      constexpr vector3( const vector3<U>& other ) noexcept;

      /// \brief Move-converts a vector3 with the value of another
      ///        vector3
      ///
      /// \param other the other vector3 to move
      template<typename U>
      constexpr vector3( vector3<U>&& other ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns \p other to \c this
      ///
      /// \param other the other vector3 to copy
      /// \return reference to \c (*this)
      vector3& operator=( const vector3& other ) = default;

      /// \brief Move-assigns \p other to \c this
      ///
      /// \param other the other vector3 to move
      /// \return reference to \c (*this)
      vector3& operator=( vector3&& other ) = default;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the number of components in the vector3
      ///
      /// \return the number of components in the vector3
      constexpr size_type size() const noexcept;

      /// \brief Gets the x component of this vector
      ///
      /// \return reference to the x component
      constexpr reference x() noexcept;

      /// \copydoc vector3::x()
      constexpr const_reference x() const noexcept;

      /// \brief Gets the y component of this vector
      ///
      /// \return reference to the y component
      constexpr reference y() noexcept;

      /// \copydoc vector3::y()
      constexpr const_reference y() const noexcept;

      /// \brief Gets the z component of this vector
      ///
      /// \return reference to the z component
      constexpr reference z() noexcept;

      /// \copydoc vector3::z()
      constexpr const_reference z() const noexcept;

      /// \brief Gets a pointer to the underlying data
      ///
      /// \return a pointer to the data
      constexpr pointer data() noexcept;

      /// \copydoc vector3::ptr()
      constexpr const_pointer data() const noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the entry at the \p n position
      ///
      /// \throw std::out_of_range if \p n >= 3
      ///
      /// \return reference to the \p n entry
      constexpr reference at( index_type n );

      /// \copydoc vector3::at( index_type )
      constexpr const_reference at( index_type n ) const;

      /// \brief Gets the entry at the \p n position
      ///
      /// \note Undefined behaviour if \p n >= 3
      ///
      /// \return reference to the \p n entry
      constexpr reference operator[]( index_type n ) noexcept;

      /// \copydoc vector3::operator[]( index_type )
      constexpr const_reference operator[]( index_type n ) const noexcept;

      //----------------------------------------------------------------------
      // Quantifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Determines the dot-product of \c this and \p rhs
      ///
      /// \param rhs the other vector3 to perform the dot-product with
      /// \return the dot product of \c this and \p rhs
      template<typename U>
      constexpr std::common_type_t<T,U>
        dot( const vector3<U>& rhs ) const noexcept;

      /// \brief Calculates the cross-product of \c this and \p rhs
      ///
      /// \param rhs the other vector3 to perform the cross-product with
      /// \return the cross product of \c this and \p rhs
      template<typename U>
      constexpr bit::math::vector3<std::common_type_t<T,U>>
        cross( const vector3<U>& rhs ) const noexcept;

      /// \brief Gets the magnitude of this vector3
      ///
      /// \return the magnitude of the vector3
      value_type magnitude() const noexcept;

      /// \brief Gets the midpoint between \c this and \p vec
      ///
      /// \param vec the vector3 to get the midpoint from
      /// \return the midpoint between \c this and \p vec
      template<typename U>
      constexpr vector3<std::common_type_t<T,U>>
        midpoint( const vector3<U>& vec ) const noexcept;

      /// \brief Gets the reflection vector3 of \c this reflected through the
      ///        \p normal
      ///
      /// \param normal the normal vector3
      /// \return the reflection
      template<typename U>
      constexpr vector3<std::common_type_t<T,U>>
        reflection( const vector3<U>& normal ) const noexcept;

      /// \brief Gets the perpendicular of this vector3
      ///
      /// \return the perpendicular vector3 to \c this
      constexpr vector3<T> perpendicular() const noexcept;

      /// \brief Gets the normalized vector3 of \c this
      ///
      /// \param the normalized vector3 of \c this
      vector3<T> normalized() const noexcept;

      /// \brief Gets the inverse of \c this vector3
      ///
      /// \return the inverse of \c this vector3
      constexpr vector3<T> inverse() const noexcept;

      /// \brief Determines the angle between \c this and \p other
      ///
      /// \param other the other vector to determine the angle between
      /// \return the angle between \c this and \p other
      template<typename U>
      radian angle_between( const vector3<U>& other ) const noexcept;

      /// \brief Determines the angle from \p to \p other
      ///
      /// \param other the other vector to get the angle to
      /// \return the angle from \c this to \p other
      template<typename U>
      radian angle_to( const vector3<U>& other ) const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps the vector3 from \c this to \p other
      ///
      /// \param other the other entry to swap
      constexpr void swap( vector3& other ) noexcept;

      /// \brief Normalizes this vector3 and returns a reference to \c (*this)
      ///
      /// \return the reference to \c (*this)
      constexpr vector3<T>& normalize() noexcept;

      /// \brief Inverts this vector3 and returns a reference to \c (*this)
      ///
      /// \return the reference to \c (*this)
      constexpr vector3<T>& invert() noexcept;

      //----------------------------------------------------------------------
      // Unary Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Unary + operator
      ///
      /// \return A reference to \c (*this)
      constexpr const vector3<T>& operator+() const noexcept;

      /// \brief Negates this vector3's magnitude and direction
      ///
      /// \return the inverse of this vector3
      constexpr vector3<T> operator-() const noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Adds \p rhs to \c this
      ///
      /// \param rhs the vector3 to add to \c this
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector3<T>& operator+=( const vector3<U>& rhs ) noexcept;

      /// \brief Subtracts \p rhs from \c this
      ///
      /// \param rhs the vector3 to subtract from \c this
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector3<T>& operator-=( const vector3<U>& rhs ) noexcept;

      /// \brief Multiplies \c this by \p scalar
      ///
      /// \param scalar the scalar multiplier to modify this vector3 by
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector3<T>& operator*=( U&& scalar ) noexcept;

      /// \brief Divides \c this by \p scalar
      ///
      /// \param scalar the scalar divisor to modify this vector3 by
      /// \return reference to \c (*this)
      template<typename U>
      constexpr vector3<T>& operator/=( U&& scalar ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_data[3]; ///< The storage data
    };

    //------------------------------------------------------------------------
    // Free Operators
    //------------------------------------------------------------------------

    /// \brief Adds two vector3s
    ///
    /// \param lhs the left vector3
    /// \param rhs the right vector3
    /// \return the result of \p lhs + \p rhs
    template<typename T, typename U>
    constexpr vector3<std::common_type_t<T,U>>
      operator+( const vector3<T>& lhs, const vector3<U>& rhs ) noexcept;

    /// \brief Subtracts two vector3s
    ///
    /// \param lhs the left vector3
    /// \param rhs the right vector3
    /// \return the result of \p lhs - \p rhs
    template<typename T, typename U>
    constexpr vector3<std::common_type_t<T,U>>
      operator-( const vector3<T>& lhs, const vector3<U>& rhs ) noexcept;

    /// \brief Multiplies a vector3 by a scalar multiplier
    ///
    /// \param lhs the left vector3
    /// \param scalar the scalar to multiply by
    /// \return the result of \p lhs * \c scalar
    template<typename T, typename U>
    constexpr vector3<std::common_type_t<T,U>>
      operator*( const vector3<T>& lhs, U&& scalar ) noexcept;

    /// \brief Multiplies a vector3 by a scalar multiplier
    ///
    /// \param lhs the left vector3
    /// \param scalar the scalar to multiply by
    /// \return the result of \p scalar * \c rhs
    template<typename T, typename U>
    constexpr vector3<std::common_type_t<T,U>>
      operator*( U&& scalar, const vector3<T>& rhs ) noexcept;

    /// \brief Divides a vector3 by a scalar constant
    ///
    /// \param lhs the left vector3
    /// \param scalar the scalar to multiply by
    /// \return the result of \p lhs / \c scalar
    template<typename T, typename U>
    constexpr vector3<std::common_type_t<T,U>>
      operator/( const vector3<T>& lhs, U&& scalar ) noexcept;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Performs the dot product between \p lhs and \p rhs
    ///
    /// \param lhs the left vector3
    /// \param rhs the right vector3
    /// \return
    template<typename T, typename U>
    constexpr std::common_type_t<T,U>
      dot( const vector3<T>& lhs, const vector3<U>& rhs ) noexcept;

    /// \brief Calculates the magnitude of the vector3 \p vec
    ///
    /// \param vec the vector3 to calculate the magnitude from
    /// \return the magnitude
    template<typename T>
    typename vector3<T>::value_type magnitude( const vector3<T>& vec ) noexcept;

    /// \brief Swaps \p lhs with \p rhs
    ///
    /// \param lhs the left vector3 to swap
    /// \param rhs the right vector3 to swap
    template<typename T>
    constexpr void swap( vector3<T>& lhs, vector3<T>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Determines exact equality between two vector3
    ///
    /// \param lhs the left vector3
    /// \param rhs the right vector3
    /// \return \c true if the two vector3 contain identical values
    template<typename T, typename U>
    constexpr bool operator == ( const vector3<T>& lhs, const vector3<U>& rhs ) noexcept;

    /// \brief Determines exact inequality between two vector3
    ///
    /// \param lhs the left vector3
    /// \param rhs the right vector3
    /// \return \c true if the two vector3 contain at least 1 different value
    template<typename T, typename U>
    constexpr bool operator != ( const vector3<T>& lhs, const vector3<U>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two vector3 relative to \ref default_tolerance
    ///
    /// \param lhs the left vector3
    /// \param rhs the right vector3
    /// \return \c true if the two vector3 contain almost equal values
    template<typename T, typename U>
    constexpr bool almost_equal( const vector3<T>& lhs, const vector3<U>& rhs ) noexcept;

    /// \brief Determines equality between two vector3 relative to \ref tolerance
    ///
    /// \param lhs the left vector3
    /// \param rhs the right vector3
    /// \return \c true if the two vector3 contain almost equal values
    template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const vector3<T>& lhs,
                                 const vector3<U>& rhs,
                                 Arithmetic tolerance ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref vector3
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_vector3 : std::false_type{};

    template<typename T> struct is_vector3<vector3<T>> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_vector3
    template<typename T>
    constexpr bool is_vector3_v = is_vector3<T>::value;

  } // namespace math
} // namespace bit

#include "vector3.inl"

#endif /* BIT_MATH_DETAIL_VECTOR_VECTOR3_HPP */
