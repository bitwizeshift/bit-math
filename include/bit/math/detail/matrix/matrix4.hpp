/**
 * \file matrix4.hpp
 *
 * \brief This header defines a 4x4 matrix class
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_MATH_DETAIL_MATRIX_MATRIX4_HPP
#define BIT_MATH_DETAIL_MATRIX_MATRIX4_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief Defines a 4x4 Matrix
    ///
    /// The matrix is accessed in column-major format (e.g. mat[col][row]) as
    /// opposed to the native [row][col] way that C++ handles 2d arrays
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class matrix4
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

      static const matrix4<T> identity; ///< Identity matrix

      static constexpr bool column_major = false;
      static constexpr bool row_major    = true;

      static constexpr size_type rows    = 4;
      static constexpr size_type columns = 4;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs a matrix4.
      ///
      /// A default constructs matrix4 has an undefined default value
      constexpr matrix4() noexcept = default;

      /// \brief Constructs a matrix4 from 4 row vectors
      ///
      /// This constructor is to allow a fluid interface for construction:
      /// \code
      /// auto mat = matrix4<float> { { 1, 0, 0, 0 },
      ///                             { 0, 1, 0, 0 },
      ///                             { 0, 0, 1, 0 },
      ///                             { 0, 0, 0, 1 } };
      /// \endcode
      ///
      /// \param v0 the first row vector
      /// \param v1 the second row vector
      /// \param v2 the third row vector
      /// \param v3 the fourth row vector
      constexpr matrix4( const vector4<T>& v0,
                         const vector4<T>& v1,
                         const vector4<T>& v2,
                         const vector4<T>& v3 ) noexcept;

      /// \brief Constructs a matrix4 from an array of 4 entries
      ///
      /// \param array the 1-dimensional array
      constexpr matrix4( const value_type(&array)[16] ) noexcept;

      /// \brief Constructs a matrix4 from a 2-dimensional array
      ///
      /// \param array the 2-dimensional array
      constexpr matrix4( const value_type(&array)[4][4] ) noexcept;

      /// \brief Constructs a matrix4 from value entries
      ///
      /// \param m00 the entry at coordinate (0,0)
      /// \param m01 the entry at coordinate (0,1)
      /// \param m02 the entry at coordinate (0,2)
      /// \param m03 the entry at coordinate (0,3)
      /// \param m10 the entry at coordinate (1,0)
      /// \param m11 the entry at coordinate (1,1)
      /// \param m12 the entry at coordinate (1,2)
      /// \param m13 the entry at coordinate (1,3)
      /// \param m20 the entry at coordinate (2,0)
      /// \param m21 the entry at coordinate (2,1)
      /// \param m22 the entry at coordinate (2,2)
      /// \param m23 the entry at coordinate (2,3)
      /// \param m30 the entry at coordinate (3,0)
      /// \param m31 the entry at coordinate (3,1)
      /// \param m32 the entry at coordinate (3,2)
      /// \param m33 the entry at coordinate (3,3)
      constexpr matrix4( value_type m00, value_type m01, value_type m02, value_type m03,
                         value_type m10, value_type m11, value_type m12, value_type m13,
                         value_type m20, value_type m21, value_type m22, value_type m23,
                         value_type m30, value_type m31, value_type m32, value_type m33 ) noexcept;

      /// \brief Copy-constructs a matrix4 from another matrix4
      ///
      /// \param other the other matrix4 to copy
      constexpr matrix4( const matrix4& other ) noexcept = default;

      /// \brief Move-constructs a matrix4 from another matrix4
      ///
      /// \param other the other matrix4 to move
      constexpr matrix4( matrix4&& other ) noexcept = default;

      /// \brief Copy-converts a matrix4 from another matrix4
      ///
      /// \param other the other matrix4 to copy-convert
      template<typename U>
      constexpr matrix4( const matrix4<U>& other ) noexcept;

      /// \brief Move-converts a matrix4 from another matrix4
      ///
      /// \param other the other matrix4 to move-convert
      template<typename U>
      constexpr matrix4( matrix4<U>&& other ) noexcept;

      /// \brief Constructs a 3x3 mapped matrix in this 4x4 matrix
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
      constexpr matrix4( value_type m00, value_type m01, value_type m02,
                         value_type m10, value_type m11, value_type m12,
                         value_type m20, value_type m21, value_type m22  ) noexcept;

      /// \brief Constructs a 3x3 mapped matrix in this 4x4 matrix
      ///
      /// \param v0 the first row vector of the 3x3 matrix
      /// \param v1 the second row vector of the 3x3 matrix
      /// \param v2 the third row vector of the 3x3 matrix
      constexpr matrix4( const vector3<T>& v0,
                         const vector3<T>& v1,
                         const vector3<T>& v2 ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a matrix4 from another matrix4
      ///
      /// \param other the other entry to copy
      /// \return reference to \c (*this)
      matrix4& operator=( const matrix4& other ) = default;


      /// \brief Move-assigns a matrix4 from another matrix4
      ///
      /// \param other the other entry to move
      /// \return reference to \c (*this)
      matrix4& operator=( matrix4&& other ) = default;

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

      /// \copydoc matrix4::at( index_type, index_type )
      constexpr const_reference at( index_type r, index_type c ) const;

      //----------------------------------------------------------------------

      /// \brief Retrieves the matrix entry at column \p c, and returns a
      ///        proxy to that row
      ///
      /// \param c the column
      /// \return a proxy to the row
      constexpr reference
        operator()( index_type r, index_type c ) noexcept;

      /// \copydoc matrix4::at( index-type )
      constexpr const_reference
        operator()( index_type r, index_type c ) const noexcept;

      //----------------------------------------------------------------------

      /// \brief Retrieves the vector at row \p r
      ///
      /// \param r the row index to retrieve
      constexpr vector4<T> row( index_type r ) const noexcept;

      /// \brief Retrieves the vector at row \p c
      ///
      /// \param c the column index to retrieve
      constexpr vector4<T> column( index_type c ) const noexcept;

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

      /// \copydoc matrix4::data()
      constexpr const_pointer data() const noexcept;

      //----------------------------------------------------------------------
      // Quantifiers
      //----------------------------------------------------------------------
    public:

      /// Calculates the determinant for this matrix4
      ///
      /// \returns the determinant of this matrix
      constexpr value_type determinant() const noexcept;

      /// Calculates the trace for this matrix4
      ///
      /// \returns the trace of this matrix
      constexpr value_type trace() const noexcept;

      /// \brief Computes the inverse of this matrix4
      ///
      /// If no inverse is possible, this returns \ref matrix4::identity
      ///
      /// \return the inverse of this matrix4
      constexpr matrix4 inverse() const noexcept;

      /// \brief Computes the transpose of this matrix4
      ///
      /// \return the transpose of this matrix4
      constexpr matrix4 transposed() const noexcept;

      /// \brief Combines \c (*this) with \p vec
      ///
      /// \param vec the vector to combine
      /// \return the result of \c vec * matrix
      template<typename U>
      constexpr vector4<std::common_type_t<T,U>>
        combine( const vector4<U>& vec ) const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps the matrix4 from \c this to \p other
      ///
      /// \param other the other entry to swap
      constexpr void swap( matrix4& other ) noexcept;

      /// \brief Inverts this current matrix4, and returns a reference to
      ///        \c (*this)
      ///
      /// If there is no inverse possible, this function returns a
      /// reference to \ref matrix4::identity, and the current matrix4
      /// is left unmodified
      ///
      /// \return reference to \c (*this)
      constexpr matrix4& invert() noexcept;

      /// \brief Transposes this current matrix4, returning a reference to
      ///        \c (*this)
      ///
      /// \return reference to \c (*this)
      constexpr matrix4& transpose() noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Performs matrix addition between \c (*this) matrix4 and
      ///        \p rhs
      ///
      /// \param rhs the matrix4 to add
      /// \return reference to \c (*this)
      template<typename U>
      matrix4& operator+=( const matrix4<U>& rhs ) noexcept;

      /// \brief Performs matrix subtraction between \c (*this) matrix4 and
      ///        \p rhs
      ///
      /// \param rhs the matrix4 to subtract
      /// \return reference to \c (*this)
      template<typename U>
      matrix4& operator-=( const matrix4<U>& rhs ) noexcept;

      /// \brief Performs matrix multiplication between \c (*this) matrix4 and
      ///        \p rhs
      ///
      /// \param rhs the matrix4 to multiply
      /// \return reference to \c (*this)
      template<typename U>
      matrix4& operator*=( const matrix4<U>& rhs ) noexcept;

      /// \brief Performs matrix multiplication with a scalar value
      ///
      /// \param scalar the scalar to multiply
      /// \return reference to \c (*this)
      template<typename U>
      matrix4& operator*=( U scalar ) noexcept;

      /// \brief Performs matrix multiplication with a scalar divisor
      ///
      /// \param scalar the scalar to divide by
      /// \return reference to \c (*this)
      template<typename U>
      matrix4& operator/=( U scalar ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      alignas(16) value_type m_matrix[rows][columns]; ///< Linear array that represents the matrix

      template<typename> friend class matrix4;

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

      /// \copydoc matrix4::get( index_type, index_type )
      constexpr const_reference get( index_type r, index_type c ) const noexcept;

    };

    //------------------------------------------------------------------------
    // Aliases
    //------------------------------------------------------------------------

    using matrix4f  = matrix4<float>;
    using matrix4d  = matrix4<double>;
    using matrix4ld = matrix4<long double>;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps \p lhs with \p rhs
    ///
    /// \param lhs the matrix on the left
    /// \param rhs the matrix on the right
    template<typename T>
    constexpr void swap( matrix4<T>& lhs, matrix4<T>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Free Operators
    //------------------------------------------------------------------------

    /// \brief Adds two \p matrix4 objects together
    ///
    /// \param lhs the left matrix4
    /// \param rhs the right matrix4
    /// \return the sum of \p lhs + \p rhs
    template<typename T, typename U>
    constexpr matrix4<std::common_type_t<T,U>>
      operator+( const matrix4<T>& lhs, const matrix4<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Subtracts one \p matrix4 object from another
    ///
    /// \param lhs the left matrix4
    /// \param rhs the right matrix4
    /// \return the sum of \p lhs - \p rhs
    template<typename T, typename U>
    constexpr matrix4<std::common_type_t<T,U>>
      operator-( const matrix4<T>& lhs, const matrix4<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Performs matrix multiplication between \p lhs and \p rhs
    ///
    /// \param lhs the left matrix4
    /// \param rhs the right matrix4
    /// \return the result of the matrix multiplication
    template<typename T, typename U>
    constexpr matrix4<std::common_type_t<T,U>>
      operator*( const matrix4<T>& lhs, const matrix4<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Performs vector multiplication with a matrix
    ///
    /// \param lhs the left matrix4
    /// \param rhs the right matrix4
    /// \return the result of the vector multiplication
    template<typename T, typename U>
    constexpr vector4<std::common_type_t<T,U>>
      operator*( const vector4<T>& lhs, const matrix4<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Multiplies a matrix4 by a scalar value
    ///
    /// \param lhs the scalar to multiply
    /// \param rhs the matrix4
    /// \result the product of \p rhs and \p lhs
#ifndef BIT_DOXYGEN_BUILD
    template<typename T, typename U, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
#else
    template<typename T, typename U>
#endif
    constexpr matrix4<std::common_type_t<T,U>>
      operator*( T lhs, const matrix4<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Multiplies a matrix4 by a scalar value
    ///
    /// \param lhs the matrix4
    /// \param rhs the scalar to multiply
    /// \result the product of \p rhs and \p lhs
#ifndef BIT_DOXYGEN_BUILD
    template<typename T, typename U, std::enable_if_t<std::is_arithmetic<U>::value>* = nullptr>
#else
    template<typename T, typename U>
#endif
    constexpr matrix4<std::common_type_t<T,U>>
      operator*( const matrix4<T>& lhs, U rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Determines exact equality between two matrix4
    ///
    /// \param lhs the left matrix4
    /// \param rhs the right matrix4
    /// \return \c true if the two matrix4 contain identical values
    template<typename T, typename U>
    constexpr bool operator == ( const matrix4<T>& lhs, const matrix4<U>& rhs ) noexcept;

    /// \brief Determines exact inequality between two matrix4
    ///
    /// \param lhs the left matrix4
    /// \param rhs the right matrix4
    /// \return \c true if the two matrix4 contain at least 1 different value
    template<typename T, typename U>
    constexpr bool operator != ( const matrix4<T>& lhs, const matrix4<U>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two matrix4 relative to \ref default_tolerance
    ///
    /// \param lhs the left matrix4
    /// \param rhs the right matrix4
    /// \return \c true if the two matrix4 contain almost equal values
    template<typename T, typename U>
    constexpr bool almost_equal( const matrix4<T>& lhs, const matrix4<U>& rhs ) noexcept;

    /// \brief Determines equality between two matrix4 relative to \ref tolerance
    ///
    /// \param lhs the left matrix4
    /// \param rhs the right matrix4
    /// \return \c true if the two matrix4 contain almost equal values
    template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const matrix4<T>& lhs,
                                 const matrix4<U>& rhs,
                                 Arithmetic tolerance ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref matrix4
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_matrix4 : std::false_type{};

    template<typename T> struct is_matrix4<matrix4<T>> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_matrix4
    template<typename T>
    constexpr bool is_matrix4_v = is_matrix4<T>::value;

  } // namespace math
} // namespace bit

#include "matrix4.inl"

#endif /* BIT_MATH_DETAIL_MATRIX_MATRIX4_HPP */
