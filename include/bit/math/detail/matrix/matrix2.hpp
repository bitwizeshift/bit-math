/**
 * \file matrix2.hpp
 *
 * \brief This header defines a 2x2 matrix class
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_MATH_DETAIL_MATRIX_MATRIX2_HPP
#define BIT_MATH_DETAIL_MATRIX_MATRIX2_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief Defines a 2x2 Matrix
    ///
    /// The matrix is accessed in column-major format (e.g. mat[col][row]) as
    /// opposed to the native [row][col] way that C++ handles 2d arrays
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class matrix2
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

      static const matrix2<T> identity; ///< Identity matrix

      static constexpr bool column_major = false;
      static constexpr bool row_major    = true;

      static constexpr index_type rows = 2;
      static constexpr index_type columns = 2;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs a matrix2.
      ///
      /// A default constructs matrix2 has an undefined default value
      constexpr matrix2() noexcept = default;

      /// \brief Constructs a matrix2 from 2 row vectors
      ///
      /// This constructor is to allow a fluid interface for construction:
      /// \code
      /// auto mat = matrix2<float> { { 1, 0 },
      ///                             { 0, 1 } };
      /// \endcode
      ///
      /// \param v0 the first row vector
      /// \param v1 the second row vector
      constexpr matrix2( const vector2<T>& v0, const vector2<T>& v1 ) noexcept;

      /// \brief Constructs a matrix2 from an array of 4 entries
      ///
      /// \param array the 1-dimensional array
      constexpr matrix2( const value_type(&array)[4] ) noexcept;

      /// \brief Constructs a matrix2 from a 2-dimensional array
      ///
      /// \param array the 2-dimensional array
      constexpr matrix2( const value_type(&array)[2][2] ) noexcept;

      /// \brief Constructs a matrix2 from value entries
      ///
      /// \param m00 the entry at coordinate (0,0)
      /// \param m01 the entry at coordinate (0,1)
      /// \param m10 the entry at coordinate (1,0)
      /// \param m11 the entry at coordinate (1,1)
      constexpr matrix2( value_type m00, value_type m01,
                         value_type m10, value_type m11 ) noexcept;

      /// \brief Copy-constructs a matrix2 from another matrix2
      ///
      /// \param other the other matrix2 to copy
      constexpr matrix2( const matrix2& other ) noexcept = default;

      /// \brief Move-constructs a matrix2 from another matrix2
      ///
      /// \param other the other matrix2 to move
      constexpr matrix2( matrix2&& other ) noexcept = default;

      /// \brief Copy-converts a matrix2 from another matrix2
      ///
      /// \param other the other matrix2 to copy-convert
      template<typename U>
      constexpr matrix2( const matrix2<U>& other ) noexcept;

      /// \brief Move-converts a matrix2 from another matrix2
      ///
      /// \param other the other matrix2 to move-convert
      template<typename U>
      constexpr matrix2( matrix2<U>&& other ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a matrix2 from another matrix2
      ///
      /// \param other the other entry to copy
      /// \return reference to \c (*this)
      matrix2& operator=( const matrix2& other ) = default;


      /// \brief Move-assigns a matrix2 from another matrix2
      ///
      /// \param other the other entry to move
      /// \return reference to \c (*this)
      matrix2& operator=( matrix2&& other ) = default;

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

      /// \copydoc matrix2::at( index_type, index_type )
      constexpr const_reference at( index_type r, index_type c ) const;

      //----------------------------------------------------------------------

      /// \brief Retrieves the matrix entry at column \p c, and returns a
      ///        proxy to that row
      ///
      /// \param c the column
      /// \return a proxy to the row
      constexpr reference
        operator()( index_type r, index_type c ) noexcept;

      /// \copydoc matrix2::at( index-type )
      constexpr const_reference
        operator()( index_type r, index_type c ) const noexcept;

      //----------------------------------------------------------------------

      /// \brief Retrieves the vector at row \p r
      ///
      /// \param r the row index to retrieve
      constexpr vector2<T> row( index_type r ) const noexcept;

      /// \brief Retrieves the vector at row \p c
      ///
      /// \param c the column index to retrieve
      constexpr vector2<T> column( index_type c ) const noexcept;

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

      /// \copydoc matrix2::data()
      constexpr const_pointer data() const noexcept;

      //----------------------------------------------------------------------
      // Quantifiers
      //----------------------------------------------------------------------
    public:

      /// Calculates the determinant for this matrix2
      ///
      /// \returns the determinant of this matrix
      constexpr value_type determinant() const noexcept;

      /// Calculates the trace for this matrix2
      ///
      /// \returns the trace of this matrix
      constexpr value_type trace() const noexcept;

      /// \brief Computes the inverse of this matrix2
      ///
      /// If no inverse is possible, this returns \ref matrix2::identity
      ///
      /// \return the inverse of this matrix2
      constexpr matrix2 inverse() const noexcept;

      /// \brief Computes the transpose of this matrix2
      ///
      /// \return the transpose of this matrix2
      constexpr matrix2 transposed() const noexcept;

      /// \brief Combines \c (*this) with \p vec
      ///
      /// \param vec the vector to combine
      /// \return the result of \c vec * matrix
      template<typename U>
      constexpr vector2<std::common_type_t<T,U>>
        combine( const vector2<U>& vec ) const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps the matrix2 from \c this to \p other
      ///
      /// \param other the other entry to swap
      constexpr void swap( matrix2& other ) noexcept;

      /// \brief Inverts this current matrix2, and returns a reference to
      ///        \c (*this)
      ///
      /// If there is no inverse possible, this function returns a
      /// reference to \ref matrix2::identity, and the current matrix2
      /// is left unmodified
      ///
      /// \return reference to \c (*this)
      constexpr matrix2& invert() noexcept;

      /// \brief Transposes this current matrix2, returning a reference to
      ///        \c (*this)
      ///
      /// \return reference to \c (*this)
      constexpr matrix2& transpose() noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Performs matrix addition between \c (*this) matrix2 and
      ///        \p rhs
      ///
      /// \param rhs the matrix2 to add
      /// \return reference to \c (*this)
      template<typename U>
      matrix2& operator+=( const matrix2<U>& rhs ) noexcept;

      /// \brief Performs matrix subtraction between \c (*this) matrix2 and
      ///        \p rhs
      ///
      /// \param rhs the matrix2 to subtract
      /// \return reference to \c (*this)
      template<typename U>
      matrix2& operator-=( const matrix2<U>& rhs ) noexcept;

      /// \brief Performs matrix multiplication between \c (*this) matrix2 and
      ///        \p rhs
      ///
      /// \param rhs the matrix2 to multiply
      /// \return reference to \c (*this)
      template<typename U>
      matrix2& operator*=( const matrix2<U>& rhs ) noexcept;

      /// \brief Performs matrix multiplication with a scalar value
      ///
      /// \param scalar the scalar to multiply
      /// \return reference to \c (*this)
      template<typename U>
      matrix2& operator*=( U scalar ) noexcept;

      /// \brief Performs matrix multiplication with a scalar divisor
      ///
      /// \param scalar the scalar to divide by
      /// \return reference to \c (*this)
      template<typename U>
      matrix2& operator/=( U scalar ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_matrix[rows][columns]; ///< Linear array that represents the matrix

      template<typename> friend class matrix2;

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

      /// \copydoc matrix2::get( index_type, index_type )
      constexpr const_reference get( index_type r, index_type c ) const noexcept;

    };


    //------------------------------------------------------------------------
    // Aliases
    //------------------------------------------------------------------------

    using matrix2f  = matrix2<float>;
    using matrix2d  = matrix2<double>;
    using matrix2ld = matrix2<long double>;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps \p lhs with \p rhs
    ///
    /// \param lhs the left matrix to swap
    /// \param rhs the right matrix to swap
    template<typename T>
    constexpr void swap( matrix2<T>& lhs, matrix2<T>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Free Operators
    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr matrix2<std::common_type_t<T,U>>
      operator+( const matrix2<T>& lhs, const matrix2<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr matrix2<std::common_type_t<T,U>>
      operator-( const matrix2<T>& lhs, const matrix2<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr matrix2<std::common_type_t<T,U>>
      operator*( const matrix2<T>& lhs, const matrix2<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr vector2<std::common_type_t<T,U>>
      operator*( const vector2<T>& lhs, const matrix2<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

#ifndef BIT_DOXYGEN_BUILD
    template<typename T, typename U, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
#else
    template<typename T, typename U>
#endif
    constexpr matrix2<std::common_type_t<T,U>>
      operator*( T lhs, const matrix2<U>& rhs ) noexcept;

    //------------------------------------------------------------------------

#ifndef BIT_DOXYGEN_BUILD
    template<typename T, typename U, std::enable_if_t<std::is_arithmetic<U>::value>* = nullptr>
#else
    template<typename T, typename U>
#endif
    constexpr matrix2<std::common_type_t<T,U>>
      operator*( const matrix2<T>& lhs, U rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Determines exact equality between two matrix2
    ///
    /// \param lhs the left matrix2
    /// \param rhs the right matrix2
    /// \return \c true if the two matrix2 contain identical values
    template<typename T, typename U>
    constexpr bool operator == ( const matrix2<T>& lhs, const matrix2<U>& rhs ) noexcept;

    /// \brief Determines exact inequality between two matrix2
    ///
    /// \param lhs the left matrix2
    /// \param rhs the right matrix2
    /// \return \c true if the two matrix2 contain at least 1 different value
    template<typename T, typename U>
    constexpr bool operator != ( const matrix2<T>& lhs, const matrix2<U>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two matrix2 relative to \ref default_tolerance
    ///
    /// \param lhs the left matrix2
    /// \param rhs the right matrix2
    /// \return \c true if the two matrix2 contain almost equal values
    template<typename T, typename U>
    constexpr bool almost_equal( const matrix2<T>& lhs, const matrix2<U>& rhs ) noexcept;

    /// \brief Determines equality between two matrix2 relative to \ref tolerance
    ///
    /// \param lhs the left matrix2
    /// \param rhs the right matrix2
    /// \return \c true if the two matrix2 contain almost equal values
    template<typename T, typename U, typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const matrix2<T>& lhs,
                                 const matrix2<U>& rhs,
                                 Arithmetic tolerance ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref matrix2
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_matrix2 : std::false_type{};

    template<typename T> struct is_matrix2<matrix2<T>> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_matrix2
    template<typename T>
    constexpr bool is_matrix2_v = is_matrix2<T>::value;

  } // namespace math
} // namespace bit

#include "matrix2.inl"

#endif /* BIT_MATH_DETAIL_MATRIX_MATRIX2_HPP */
