/**
 * \file matrix3.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_DETAIL_MATRIX_MATRIX3_HPP
#define BIT_MATH_DETAIL_MATRIX_MATRIX3_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief Defines a 3x3 Matrix
    ///
    /// The matrix is accessed in column-major format (e.g. mat[col][row]) as
    /// opposed to the native [row][col] way that C++ handles 2d arrays
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class matrix3
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

      static const matrix3<T> identity; ///< Identity matrix

      static constexpr bool column_major = false;
      static constexpr bool row_major    = true;

      static constexpr size_type rows    = 3;
      static constexpr size_type columns = 3;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs a matrix3.
      ///
      /// A default constructs matrix3 has an undefined default value
      constexpr matrix3() noexcept = default;

      /// \brief Constructs a matrix3 from 2 row vectors
      ///
      /// This constructor is to allow a fluid interface for construction:
      /// \code
      /// auto mat = matrix3<float> { { 1, 0 },
      ///                             { 0, 1 } };
      /// \endcode
      ///
      /// \param v0 the first row vector
      /// \param v1 the second row vector
      constexpr matrix3( const vector3<T>& v0,
                         const vector3<T>& v1,
                         const vector3<T>& v2 ) noexcept;

      /// \brief Constructs a matrix3 from an array of 4 entries
      ///
      /// \param array the 1-dimensional array
      constexpr matrix3( const value_type(&array)[9] ) noexcept;

      /// \brief Constructs a matrix3 from a 2-dimensional array
      ///
      /// \param array the 2-dimensional array
      constexpr matrix3( const value_type(&array)[3][3] ) noexcept;

      /// \brief Constructs a matrix3 from value entries
      ///
      /// \param m00 the entry at coordinate (0,0)
      /// \param m01 the entry at coordinate (0,1)
      /// \param m02 the entry at coordinate (0,2)
      /// \param m10 the entry at coordinate (1,0)
      /// \param m11 the entry at coordinate (1,1)
      /// \param m12 the entry at coordinate (1,2)
      /// \param m20 the entry at coordinate (2,0)
      /// \param m21 the entry at coordinate (2,1)
      /// \param m22 the entry at coordinate (2,2)
      constexpr matrix3( value_type m00, value_type m01, value_type m02,
                         value_type m10, value_type m11, value_type m12,
                         value_type m20, value_type m21, value_type m22 ) noexcept;

      /// \brief Copy-constructs a matrix3 from another matrix3
      ///
      /// \param other the other matrix3 to copy
      constexpr matrix3( const matrix3& other ) noexcept = default;

      /// \brief Move-constructs a matrix3 from another matrix3
      ///
      /// \param other the other matrix3 to move
      constexpr matrix3( matrix3&& other ) noexcept = default;

      /// \brief Copy-converts a matrix3 from another matrix3
      ///
      /// \param other the other matrix3 to copy-convert
      template<typename U>
      constexpr matrix3( const matrix3<U>& other ) noexcept;

      /// \brief Move-converts a matrix3 from another matrix3
      ///
      /// \param other the other matrix3 to move-convert
      template<typename U>
      constexpr matrix3( matrix3<U>&& other ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a matrix3 from another matrix3
      ///
      /// \param other the other entry to copy
      /// \return reference to \c (*this)
      matrix3& operator=( const matrix3& other ) = default;


      /// \brief Move-assigns a matrix3 from another matrix3
      ///
      /// \param other the other entry to move
      /// \return reference to \c (*this)
      matrix3& operator=( matrix3&& other ) = default;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Retrieves the matrix entry at column \p c and row \p r
      ///
      /// \throw std::out_of_range if \p c or \p r is greater than 2, or less
      ///        than 0.
      ///
      /// \param r the row to retrieve
      /// \param c the column to retrieve
      /// \return the reference to the entry
      constexpr reference at( index_type r, index_type c );

      /// \copydoc matrix3::at( index_type, index_type )
      constexpr const_reference at( index_type r, index_type c ) const;

      //----------------------------------------------------------------------

      /// \brief Retrieves the matrix entry at column \p c, and returns a
      ///        proxy to that row
      ///
      /// \param c the column
      /// \return a proxy to the row
      constexpr reference
        operator()( index_type r, index_type c ) noexcept;

      /// \copydoc matrix3::at( index-type )
      constexpr const_reference
        operator()( index_type r, index_type c ) const noexcept;

      //----------------------------------------------------------------------

      /// \brief Retrieves the vector at row \p r
      ///
      /// \param r the row index to retrieve
      constexpr vector3<T> row( index_type r ) const noexcept;

      /// \brief Retrieves the vector at row \p c
      ///
      /// \param c the column index to retrieve
      constexpr vector3<T> column( index_type c ) const noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Retrieves the number of entries in this matrix
      ///
      /// \return the size of the matrix
      constexpr size_type size() const noexcept;

      /// \brief Gets a pointer to the underlying data
      ///
      /// \return a pointer to the data
      constexpr pointer data() noexcept;

      /// \copydoc matrix3::data()
      constexpr const_pointer data() const noexcept;

      //----------------------------------------------------------------------
      // Quantifiers
      //----------------------------------------------------------------------
    public:

      /// Calculates the determinant for this matrix3
      ///
      /// \returns the determinant of this matrix
      constexpr value_type determinant() const noexcept;

      /// Calculates the trace for this matrix3
      ///
      /// \returns the trace of this matrix
      constexpr value_type trace() const noexcept;

      /// \brief Computes the inverse of this matrix3
      ///
      /// If no inverse is possible, this returns \ref matrix3::identity
      ///
      /// \return the inverse of this matrix3
      constexpr matrix3 inverse() const noexcept;

      /// \brief Computes the transpose of this matrix3
      ///
      /// \return the transpose of this matrix3
      constexpr matrix3 transposed() const noexcept;

      /// \brief Combines \c (*this) with \p vec
      ///
      /// \param vec the vector to combine
      /// \return the result of \c vec * matrix
      template<typename U>
      constexpr vector3<std::common_type_t<T,U>>
        combine( const vector3<U>& vec ) const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps the matrix3 from \c this to \p other
      ///
      /// \param other the other entry to swap
      constexpr void swap( matrix3& other ) noexcept;

      /// \brief Inverts this current matrix3, and returns a reference to
      ///        \c (*this)
      ///
      /// If there is no inverse possible, this function returns a
      /// reference to \ref matrix3::identity, and the current matrix3
      /// is left unmodified
      ///
      /// \return reference to \c (*this)
      constexpr matrix3& invert() noexcept;

      /// \brief Transposes this current matrix3, returning a reference to
      ///        \c (*this)
      ///
      /// \return reference to \c (*this)
      constexpr matrix3& transpose() noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Performs matrix addition between \c (*this) matrix3 and
      ///        \p rhs
      ///
      /// \param rhs the matrix3 to add
      /// \return reference to \c (*this)
      template<typename U>
      matrix3& operator+=( const matrix3<U>& rhs ) noexcept;

      /// \brief Performs matrix subtraction between \c (*this) matrix3 and
      ///        \p rhs
      ///
      /// \param rhs the matrix3 to subtract
      /// \return reference to \c (*this)
      template<typename U>
      matrix3& operator-=( const matrix3<U>& rhs ) noexcept;

      /// \brief Performs matrix multiplication between \c (*this) matrix3 and
      ///        \p rhs
      ///
      /// \param rhs the matrix3 to multiply
      /// \return reference to \c (*this)
      template<typename U>
      matrix3& operator*=( const matrix3<U>& rhs ) noexcept;

      /// \brief Performs matrix multiplication with a scalar value
      ///
      /// \param scalar the scalar to multiply
      /// \return reference to \c (*this)
      template<typename U>
      matrix3& operator*=( U scalar ) noexcept;

      /// \brief Performs matrix multiplication with a scalar divisor
      ///
      /// \param scalar the scalar to divide by
      /// \return reference to \c (*this)
      template<typename U>
      matrix3& operator/=( U scalar ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_matrix[rows][columns]; ///< Linear array that represents the matrix

      template<typename> friend class matrix3;

      //----------------------------------------------------------------------
      // Private Member Functions
      //----------------------------------------------------------------------
    private:

      /// \brief Non-throwing matrix element access
      ///
      /// \param r the row
      /// \param c the column
      /// \return reference to the entry
      constexpr reference get( index_type r, index_type c ) noexcept;

      /// \copydoc matrix3::get( index_type, index_type )
      constexpr const_reference get( index_type r, index_type c ) const noexcept;

    };

    //------------------------------------------------------------------------
    // Aliases
    //------------------------------------------------------------------------

    using matrix3f  = matrix3<float>;
    using matrix3d  = matrix3<double>;
    using matrix3ld = matrix3<long double>;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps \p lhs with \p rhs
    ///
    /// \param lhs the matrix on the left
    /// \param rhs the matrix on the right
    template<typename T>
    constexpr void swap( matrix3<T>& lhs, matrix3<T>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Free Operators
    //------------------------------------------------------------------------

    /// \brief Adds two \p matrix3 objects together
    ///
    /// \param lhs the left matrix3
    /// \param rhs the right matrix3
    /// \return the sum of \p lhs + \p rhs
    template<typename T, typename U>
    constexpr matrix3<std::common_type_t<T,U>>
      operator+( const matrix3<T>& lhs, const matrix3<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Subtracts one \p matrix3 object from another
    ///
    /// \param lhs the left matrix3
    /// \param rhs the right matrix3
    /// \return the sum of \p lhs - \p rhs
    template<typename T, typename U>
    constexpr matrix3<std::common_type_t<T,U>>
      operator-( const matrix3<T>& lhs, const matrix3<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Performs matrix multiplication between \p lhs and \p rhs
    ///
    /// \param lhs the left matrix3
    /// \param rhs the right matrix3
    /// \return the result of the matrix multiplication
    template<typename T, typename U>
    constexpr matrix3<std::common_type_t<T,U>>
      operator*( const matrix3<T>& lhs, const matrix3<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Performs vector multiplication with a matrix
    ///
    /// \param lhs the left matrix3
    /// \param rhs the right matrix3
    /// \return the result of the vector multiplication
    template<typename T, typename U>
    constexpr vector3<std::common_type_t<T,U>>
      operator*( const vector3<T>& lhs, const matrix3<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Multiplies a matrix3 by a scalar value
    ///
    /// \param lhs the scalar to multiply
    /// \param rhs the matrix3
    /// \result the product of \p rhs and \p lhs
#ifndef BIT_DOXYGEN_BUILD
    template<typename T, typename U, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
#else
    template<typename T, typename U>
#endif
    constexpr matrix3<std::common_type_t<T,U>>
      operator*( T lhs, const matrix3<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Multiplies a matrix3 by a scalar value
    ///
    /// \param lhs the matrix3
    /// \param rhs the scalar to multiply
    /// \result the product of \p rhs and \p lhs
#ifndef BIT_DOXYGEN_BUILD
    template<typename T, typename U, std::enable_if_t<std::is_arithmetic<U>::value>* = nullptr>
#else
    template<typename T, typename U>
#endif
    constexpr matrix3<std::common_type_t<T,U>>
      operator*( const matrix3<T>& lhs, U rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Determines exact equality between two matrix3
    ///
    /// \param lhs the left matrix3
    /// \param rhs the right matrix3
    /// \return \c true if the two matrix3 contain identical values
    template<typename T, typename U>
    constexpr bool operator == ( const matrix3<T>& lhs, const matrix3<U>& rhs ) noexcept;

    /// \brief Determines exact inequality between two matrix3
    ///
    /// \param lhs the left matrix3
    /// \param rhs the right matrix3
    /// \return \c true if the two matrix3 contain at least 1 different value
    template<typename T, typename U>
    constexpr bool operator != ( const matrix3<T>& lhs, const matrix3<U>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two matrix3 relative to \ref default_tolerance
    ///
    /// \param lhs the left matrix3
    /// \param rhs the right matrix3
    /// \return \c true if the two matrix3 contain almost equal values
    template<typename T, typename U>
    constexpr bool almost_equal( const matrix3<T>& lhs, const matrix3<U>& rhs ) noexcept;

    /// \brief Determines equality between two matrix3 relative to \ref tolerance
    ///
    /// \param lhs the left matrix3
    /// \param rhs the right matrix3
    /// \return \c true if the two matrix3 contain almost equal values
    template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const matrix3<T>& lhs,
                                 const matrix3<U>& rhs,
                                 Arithmetic tolerance ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref matrix3
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_matrix3 : std::false_type{};

    template<typename T> struct is_matrix3<matrix3<T>> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_matrix3
    template<typename T>
    constexpr bool is_matrix3_v = is_matrix3<T>::value;

  } // namespace math
} // namespace bit

#include "matrix3.inl"

#endif /* BIT_MATH_DETAIL_MATRIX_MATRIX3_HPP */
