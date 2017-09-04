/**
 * \file point2.hpp
 *
 * \brief This header contains an implementation of a 2d point location
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_MATH_DETAIL_POINT_POINT2_HPP
#define BIT_MATH_DETAIL_POINT_POINT2_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief This class represents a coordinate in 2d space
    ///
    //////////////////////////////////////////////////////////////////////////
    class point2
    {
      //----------------------------------------------------------------------
      // Public Types
      //----------------------------------------------------------------------
    public:

      using value_type      = float_t;
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

      static const point2 origin; ///< Point at the origin of coordinate system

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs a point2 at the origin
      constexpr point2() noexcept;

      /// \brief Constructs a point2 at coordinates \c {x,y}
      ///
      /// \param x the x-coordinate
      /// \param y the y-coordinate
      constexpr point2( value_type x, value_type y ) noexcept;


      /// \brief Move-constructs a point2 from another point2
      ///
      /// \param other the other point2 to move
      point2( point2&& other ) noexcept = default;

      /// \brief Copy-constructs a point2 from another point2
      ///
      /// \param other the other point2 to copy
      point2( const point2& other ) noexcept = default;

      //----------------------------------------------------------------------

      /// \brief Move-assigns a point2 from another point2
      ///
      /// \param other the other point2 to move
      /// \return reference to \c (*this)
      point2& operator=( point2&& other ) noexcept = default;

      /// \brief Copy-assigns a point2 from another point2
      ///
      /// \param other the other point2 to copy
      /// \return reference to \c (*this)
      point2& operator=( const point2& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Translates this point2 by the components of \p rhs
      ///
      /// \param rhs the direction to translate this point
      /// \return reference to \c (*this)
      template<typename T>
      point2& operator+=( const vector2<T>& rhs ) noexcept;

      /// \brief Translates this point2 by the components of \p rhs
      ///
      /// \param rhs the direction to translate this point
      /// \return reference to \c (*this)
      template<typename T>
      point2& operator-=( const vector2<T>& rhs ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the x component of this point
      ///
      /// \return reference to the x component
      constexpr reference x() noexcept;

      /// \copydoc point::x()
      constexpr const_reference x() const noexcept;

      /// \brief Gets the y component of this point
      ///
      /// \return reference to the y component
      constexpr reference y() noexcept;

      /// \copydoc point::y()
      constexpr const_reference y() const noexcept;

      /// \brief Gets a pointer to the underlying data
      ///
      /// \return a pointer to the data
      constexpr pointer data() noexcept;

      /// \copydoc point::data()
      constexpr const_pointer data() const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps this point2 with \p other
      ///
      /// \param other the other point2 to swap with
      void swap( point2& other ) noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      value_type m_data[2];
    };

    //------------------------------------------------------------------------
    // Free Operators
    //------------------------------------------------------------------------

    vector2<float_t> operator - ( const point2& lhs, const point2& rhs ) noexcept;

    template<typename T>
    point2 operator + ( const point2& lhs, const vector2<T>& rhs ) noexcept;

    template<typename T>
    point2 operator - ( const point2& lhs, const vector2<T>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps \p lhs with \p rhs
    ///
    /// \param lhs the left point2 to swap
    /// \param rhs the right point2 to swap
    constexpr void swap( point2& lhs, point2& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Determines exact equality between two point2
    ///
    /// \param lhs the left point2
    /// \param rhs the right point2
    /// \return \c true if the two point2 contain identical values
    constexpr bool operator==( const point2& lhs, const point2& rhs ) noexcept;

    /// \brief Determines exact inequality between two point2
    ///
    /// \param lhs the left point2
    /// \param rhs the right point2
    /// \return \c true if the two point2 contain at least 1 different value
    constexpr bool operator!=( const point2& lhs, const point2& rhs ) noexcept;

    constexpr bool operator<=( const point2& lhs, const point2& rhs ) noexcept;

    constexpr bool operator>=( const point2& lhs, const point2& rhs ) noexcept;

    constexpr bool operator<( const point2& lhs, const point2& rhs ) noexcept;

    constexpr bool operator>( const point2& lhs, const point2& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two point2 relative to \ref default_tolerance
    ///
    /// \param lhs the left point2
    /// \param rhs the right point2
    /// \return \c true if the two point2 contain almost equal values
    constexpr bool almost_equal( const point2& lhs, const point2& rhs ) noexcept;

    /// \brief Determines equality between two point2 relative to \ref tolerance
    ///
    /// \param lhs the left point2
    /// \param rhs the right point2
    /// \return \c true if the two point2 contain almost equal values
    template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const point2& lhs,
                                 const point2& rhs,
                                 Arithmetic tolerance ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref point2
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_point2 : std::false_type{};

    template<> struct is_point2<point2> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_point2
    template<typename T>
    constexpr bool is_point2_v = is_point2<T>::value;

  } // namespace math
} // namespace bit

#include "point2.inl"

#endif /* BIT_MATH_DETAIL_POINT_POINT2_HPP */
