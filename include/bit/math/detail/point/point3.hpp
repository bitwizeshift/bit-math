/*****************************************************************************
 * \file
 * \brief This header contains an implementation of a 3d point location
 *****************************************************************************/

/*
  The MIT License (MIT)

  Bit Math Library.
  https://github.com/bitwizeshift/bit-math

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef BIT_MATH_DETAIL_GEOMETRY_POINT_POINT3_HPP
#define BIT_MATH_DETAIL_GEOMETRY_POINT_POINT3_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief This class represents a coordinate in 3d space
    ///
    //////////////////////////////////////////////////////////////////////////
    class point3
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

      static const point3 origin; ///< Point at the origin of coordinate system

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs a point3 at the origin
      constexpr point3() noexcept;

      /// \brief Constructs a point3 at coordinates \c {x,y,z}
      ///
      /// \param x the x-coordinate
      /// \param y the y-coordinate
      constexpr point3( value_type x, value_type y, value_type z ) noexcept;

      /// \brief Move-constructs a point3 from another point3
      ///
      /// \param other the other point3 to move
      point3( point3&& other ) noexcept = default;

      /// \brief Copy-constructs a point3 from another point3
      ///
      /// \param other the other point3 to copy
      point3( const point3& other ) noexcept = default;

      //----------------------------------------------------------------------

      /// \brief Move-assigns a point3 from another point3
      ///
      /// \param other the other point3 to move
      /// \return reference to \c (*this)
      point3& operator=( point3&& other ) noexcept = default;

      /// \brief Copy-assigns a point3 from another point3
      ///
      /// \param other the other point3 to copy
      /// \return reference to \c (*this)
      point3& operator=( const point3& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Translates this point3 by the components of \p rhs
      ///
      /// \param rhs the direction to translate this point
      /// \return reference to \c (*this)
      template<typename T>
      point3& operator+=( const vector3<T>& rhs ) noexcept;

      /// \brief Translates this point3 by the components of \p rhs
      ///
      /// \param rhs the direction to translate this point
      /// \return reference to \c (*this)
      template<typename T>
      point3& operator-=( const vector3<T>& rhs ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the x component of this point
      ///
      /// \return reference to the x component
      constexpr reference x() noexcept;

      /// \copydoc point3::x()
      constexpr const_reference x() const noexcept;

      /// \brief Gets the y component of this point
      ///
      /// \return reference to the y component
      constexpr reference y() noexcept;

      /// \copydoc point3::y()
      constexpr const_reference y() const noexcept;

      /// \brief Gets the z component of this point
      ///
      /// \return reference to the z component
      constexpr reference z() noexcept;

      /// \copydoc point3::z()
      constexpr const_reference z() const noexcept;


      /// \brief Gets a pointer to the underlying data
      ///
      /// \return a pointer to the data
      constexpr pointer data() noexcept;

      /// \copydoc point3::data()
      constexpr const_pointer data() const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps this point3 with \p other
      ///
      /// \param other the other point3 to swap with
      void swap( point3& other ) noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      value_type m_data[3];
    };

    //------------------------------------------------------------------------
    // Free Operators
    //------------------------------------------------------------------------

    vector3<float_t> operator - ( const point3& lhs, const point3& rhs ) noexcept;

    template<typename T>
    point3 operator + ( const point3& lhs, const vector3<T>& rhs ) noexcept;

    template<typename T>
    point3 operator - ( const point3& lhs, const vector3<T>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps \p lhs with \p rhs
    ///
    /// \param lhs the left point3 to swap
    /// \param rhs the right point3 to swap
    constexpr void swap( point3& lhs, point3& rhs ) noexcept;

    /// \{
    /// \brief Performs the dot product between \p lhs and \p rhs
    ///
    /// \param lhs the left operand
    /// \param rhs the right operand
    /// \return the result of the dot product
    constexpr float_t dot( const point3& lhs, const point3& rhs ) noexcept;
    constexpr float_t dot( const vec3& lhs, const point3& rhs ) noexcept;
    constexpr float_t dot( const point3& lhs, const vec3& rhs ) noexcept;
    /// \}

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Determines exact equality between two point3
    ///
    /// \param lhs the left point3
    /// \param rhs the right point3
    /// \return \c true if the two point3 contain identical values
    constexpr bool operator==( const point3& lhs, const point3& rhs ) noexcept;

    /// \brief Determines exact inequality between two point3
    ///
    /// \param lhs the left point3
    /// \param rhs the right point3
    /// \return \c true if the two point3 contain at least 1 different value
    constexpr bool operator!=( const point3& lhs, const point3& rhs ) noexcept;

    constexpr bool operator<=( const point3& lhs, const point3& rhs ) noexcept;

    constexpr bool operator>=( const point3& lhs, const point3& rhs ) noexcept;

    constexpr bool operator<( const point3& lhs, const point3& rhs ) noexcept;

    constexpr bool operator>( const point3& lhs, const point3& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines equality between two point3 relative to \ref default_tolerance
    ///
    /// \param lhs the left point3
    /// \param rhs the right point3
    /// \return \c true if the two point3 contain almost equal values
    constexpr bool almost_equal( const point3& lhs, const point3& rhs ) noexcept;

    /// \brief Determines equality between two point3 relative to \ref tolerance
    ///
    /// \param lhs the left point3
    /// \param rhs the right point3
    /// \return \c true if the two point3 contain almost equal values
    template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    constexpr bool almost_equal( const point3& lhs,
                                 const point3& rhs,
                                 Arithmetic tolerance ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref point3
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_point3 : std::false_type{};

    template<> struct is_point3<point3> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_point3
    template<typename T>
    constexpr bool is_point3_v = is_point3<T>::value;

  } // namespace math
} // namespace bit

#include "point3.inl"

#endif /* BIT_MATH_DETAIL_GEOMETRY_POINT_POINT3_HPP */
