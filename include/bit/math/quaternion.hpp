/**
 * \file quaternion.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_QUATERNION_HPP
#define BIT_MATH_QUATERNION_HPP

#include "angles.hpp"
#include "vector.hpp"
#include "matrix.hpp"

#include <utility>
#include <tuple>

namespace bit {
  namespace math {
    namespace detail {
      struct reproject_axis{};
    }
    /// \brief Function used for tag dispatch
#ifndef BIT_DOXYGEN_BUILD
    inline void reproject_axis( detail::reproject_axis ){}
#else
    void reproject_axis( /* implementation defined */ );
#endif

    /// \brief Type used for tag dispatching reprojecting the axis
#ifndef BIT_DOXYGEN_BUILD
    using reproject_axis_t = void(*)( detail::reproject_axis );
#else
    using reproject_axis_t = void(*)( /* implementation defined */ );
#endif

    //////////////////////////////////////////////////////////////////////////
    /// \brief A quaternion is a mathematical construct representing
    ///        4-dimensions of a rotation about the x,y,z axis.
    ///
    /// A quaternion is conventionally represented as q = {x,y,z,w}, where
    /// x,y, and z represent rotations around the respective axes
    /// (representing roll, pitch, and yaw respectively).
    //////////////////////////////////////////////////////////////////////////
    class quaternion
    {
      //----------------------------------------------------------------------
      // Public member Types
      //----------------------------------------------------------------------
    public:

#ifdef BIT_MATH_DOUBLE_PRECISION
      using value_type = double; ///< The underlying value type
#else
      using value_type = float;  ///< The underlying value type
#endif
      using pointer         = value_type*;       ///< The pointer type
      using reference       = value_type&;       ///< The reference type
      using const_pointer   = const value_type*; ///< The const reference type
      using const_reference = const value_type&; ///< The const pointer type

      using size_type  = std::size_t;           ///< The type used for sizes
      using index_type = std::ptrdiff_t;        ///< The type used for indices

      using vector_type  = vector3<value_type>; ///< The vector type
      using matrix3_type = matrix3<value_type>; ///< The 3x3 matrix type
      using matrix4_type = matrix4<value_type>; ///< The 4x4 matrix type

      //----------------------------------------------------------------------
      // Public Constants
      //----------------------------------------------------------------------
    public:

      static const quaternion zero;     ///<
      static const quaternion identity; ///<

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a quaternion with an angle of 0
      ///
      /// \note This constructor is \c explicit to disallow instantiation of
      ///       the form \code bit::math::quaternion q = {} \endcode
      explicit quaternion() noexcept;

      /// Constructs a quaternion around an axis
      ///
      /// \param angle the angle of the quaternion
      /// \param axis  the axis of the rotation
      quaternion( radian angle, const vector_type& axis ) noexcept;

      /// \brief Constructs a quaternion from the \p yaw, \p pitch, and
      ///        \p roll angles
      ///
      /// \param yaw the yaw angle
      /// \param pitch the pitch angle
      /// \param roll the roll angle
      quaternion( radian yaw, radian pitch, radian roll ) noexcept;

      /// \brief Constructs a quaternion with only 1 real component
      ///
      /// \param x the real component of the quaternion
      quaternion( value_type x ) noexcept;

      /// \brief Constructs a quaternion with 4 angle components
      ///
      /// \param x the real component of the quaternion
      /// \param y the first imaginary component of the quaternion
      /// \param z the second imaginary component of the quaternion
      /// \param w the final imaginary component of the quaternion
      quaternion( value_type x, value_type y, value_type z, value_type w ) noexcept;

      /// Constructs a quaternion with 3 axis vectors
      ///
      /// \param x_axis Vector of the x-axis rotation
      /// \param y_axis Vector of the y-axis rotation
      /// \param z_axis Vector of the z-axis rotation
      quaternion( const vector_type& x_axis,
                  const vector_type& y_axis,
                  const vector_type& z_axis ) noexcept;

      /// \brief Constructs a quaternion out of a 3-component rotation
      ///        matrix
      ///
      /// \param rot 3x3 rotation matrix
      explicit quaternion( const matrix3_type& rot ) noexcept;

      /// \brief Constructs a quaternion out of a 4-component rotation
      ///        matrix
      ///
      /// \param rot 4x4 rotation matrix
      explicit quaternion( const matrix4_type& rot ) noexcept;

      /// \brief Copy-constructs a quaternion from another quaternion
      ///
      /// \param other the other quaternion to copy
      quaternion( const quaternion& other ) noexcept = default;

      /// \brief Move-constructs a quaternion from another quaternion
      ///
      /// \param other the other quaternion to move
      quaternion( quaternion&& other ) = default;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns the quaternion
      ///
      /// \param other the quaternion to copy
      /// \return reference to \c (*this)
      quaternion& operator=( const quaternion& other ) noexcept = default;

      /// \brief Move-assigns the quaternion
      ///
      /// \param other the quaternion to move
      /// \return reference to \c (*this)
      quaternion& operator=( quaternion&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the number of components in the vector2
      ///
      /// \return the number of components in the vector2
      size_type size() const noexcept;

      /// \brief Gets the w component of this quaternion
      ///
      /// \return reference to the w component
      reference w() noexcept;

      /// \copydoc quaternion::w()
      const_reference w() const noexcept;

      /// \brief Gets the x component of this quaternion
      ///
      /// \return reference to the x component
      reference x() noexcept;

      /// \copydoc vector2::x()
      const_reference x() const noexcept;

      /// \brief Gets the y component of this quaternion
      ///
      /// \return reference to the y component
      reference y() noexcept;

      /// \copydoc vector2::y()
      const_reference y() const noexcept;

      /// \brief Gets the z component of this quaternion
      ///
      /// \return reference to the z component
      reference z() noexcept;

      /// \copydoc quaternion::z()
      const_reference z() const noexcept;

      /// \brief Gets a pointer to the underlying data
      ///
      /// \return a pointer to the data
      pointer data() noexcept;

      /// \copydoc vector2::ptr()
      const_pointer data() const noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// Retrieves the element of the quaternion at \p n
      ///
      /// \throw std::out_of_range if indx is out of range
      ///
      /// \param n the element index
      /// \return a reference to the entry
      reference at( index_type n );

      /// \copydoc quaternion::at( index_type )
      const_reference at( index_type n ) const;

      //----------------------------------------------------------------------

      /// Retrieves the element of the quaternion at \p n
      ///
      /// \param n the element index
      /// \return a reference to the entry
      reference operator[] ( index_type n ) noexcept;

      /// \copydoc quaternion::operator[]( index_type )
      const_reference operator[] ( index_type n ) const noexcept;

      //----------------------------------------------------------------------

      /// \brief Retrieves the x-axis from this quaternion
      ///
      /// \return the x-axis
      vector_type x_axis() const noexcept;

      /// \brief Retrieves the y-axis from this quaternion
      ///
      /// \return the y-axis
      vector_type y_axis() const noexcept;

      /// \brief Retrieves the z-axis from this quaternion
      ///
      /// \return the z-axis
      vector_type z_axis() const noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates and returns the 3x3 rotation matrix
      ///
      /// \return the rotation matrix
      matrix3_type rotation_matrix() const noexcept;

      /// \brief Calculates and returns the rotation angle and axis
      ///
      /// \return a tuple containing the angle and the axis
      std::tuple<radian,vector_type> angle_axis() const noexcept;

      /// \brief Calculates and returns the x, y, and z axss as vectors
      ///
      /// \return a tuple containing the x, y, and z vector axes
      std::tuple<vector_type,vector_type,vector_type> axes() const noexcept;

      //----------------------------------------------------------------------

      /// \brief Gets the normalized quaternion of \c this
      ///
      /// \param the normalized quaternion of \c this
      quaternion normalized() const noexcept;

      /// \brief Gets the inverse of \c this quaternion
      ///
      /// \return the inverse of \c this quaternion
      quaternion inverse() const noexcept;

      //----------------------------------------------------------------------
      // Extraction
      //----------------------------------------------------------------------
    public:

      /// \brief Extracts a 3x3 rotation matrix from this quaternion
      ///
      /// \param rot pointer to the rotation matrix to extract into
      void extract_rotation_matrix( matrix3_type* rot ) const noexcept;

      /// \brief Extracts a 4x4 rotation matrix from this quaternion
      ///
      /// \param rot pointer to the rotation matrix to extract into
      void extract_rotation_matrix( matrix4_type* rot ) const noexcept;

      //----------------------------------------------------------------------

      /// \brief Extracts the \p angle and \p axis from this quaternion
      ///
      /// \param angle the angle to extract into
      /// \param axis the vector to extract into
      void extract_angle_axis( radian* angle, vector_type* axis ) const noexcept;

      /// \copydoc quaternion::extract_angle_axis( radian*, vector_type* )
      void extract_angle_axis( degree* angle, vector_type* axis ) const noexcept;

      //----------------------------------------------------------------------

      /// \brief Extracts the x, y, and z axes
      ///
      /// \param x_axis pointer to the x-axis vector
      /// \param y_axis pointer to the y-axis vector
      /// \param z_axis pointer to the z-axis vector
      void extract_axes( vector_type* x_axis,
                         vector_type* y_axis,
                         vector_type* z_axis ) const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps the quaternion from \c this to \p other
      ///
      /// \param other the other entry to swap
      void swap( quaternion& other ) noexcept;

      /// \brief Normalizes this quaternion and returns a reference to \c (*this)
      ///
      /// \return the reference to \c (*this)
      quaternion& normalize() noexcept;

      /// \brief Inverts this quaternion and returns a reference to \c (*this)
      ///
      /// \return the reference to \c (*this)
      quaternion& invert() noexcept;

      //----------------------------------------------------------------------
      // Quantifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Computes the dot-product of \p rhs and \c this
      ///
      /// \param rhs the quaternion to perform the dot product with
      /// \return the result of the dot product
      value_type dot( const quaternion& rhs ) const noexcept;

      /// \brief Computes the magnitude of this quaternion
      ///
      /// \return the magnitude
      value_type magnitude() const noexcept;

      //----------------------------------------------------------------------

      /// \brief Computes the roll angle by reprojecting the axis
      ///
      /// \param reproject tag used for tag dispatch
      /// \return the roll angle
      radian roll( reproject_axis_t reproject ) const noexcept;

      /// \brief Computes the roll angle by reprojecting the axis
      ///
      /// \return the roll angle
      radian roll() const noexcept;

      //----------------------------------------------------------------------

      /// \brief Computes the pitch angle by reprojecting the axis
      ///
      /// \param reproject tag used for tag dispatch
      /// \return the pitch angle
      radian pitch( reproject_axis_t ) const noexcept;

      /// \brief Computes the pitch angle by reprojecting the axis
      ///
      /// \return the pitch angle
      radian pitch() const noexcept;

      //----------------------------------------------------------------------

      /// \brief Computes the yaw angle by reprojecting the axis
      ///
      /// \param reproject tag used for tag dispatch
      /// \return the yaw angle
      radian yaw( reproject_axis_t ) const noexcept;

      /// \brief Computes the yaw angle by reprojecting the axis
      ///
      /// \return the yaw angle
      radian yaw() const noexcept;

      //----------------------------------------------------------------------
      // Unary Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Returns this quaternion unaltered
      ///
      /// \return this quaternion
      quaternion operator+() const noexcept;

      /// \brief Returns a negated copy of this quaternion
      ///
      /// \return a negated copy of this quaternion
      quaternion operator-() const noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      /// \brief Adds \c rhs quaternion to \p this
      ///
      /// \param rhs the quaternion to add
      /// \return reference to \c (*this)
      quaternion& operator += ( const quaternion& rhs ) noexcept;

      /// \brief Subtracts \c this quaternion by \p rhs
      ///
      /// \param rhs the quaternion to subtract
      /// \return reference to \c (*this)
      quaternion& operator -= ( const quaternion& rhs ) noexcept;

      /// \brief Multiplies \c this quaternion by \p rhs
      ///
      /// \param rhs the quaternion to multiply by
      /// \return reference to \c (*this)
      quaternion& operator *= ( const quaternion& rhs ) noexcept;

      /// \brief Multiplies \p this quaternion by the scalar \p rhs
      ///
      /// \param rhs the scalar to multiply each element by
      /// \return reference to \c (*this)
      quaternion& operator *= ( value_type rhs ) noexcept;

      /// \brief Divides \p this quaternion by the scalar \p rhs
      ///
      /// \param rhs the scalar to divide each element by
      /// \return reference to \c (*this)
      quaternion& operator /= ( value_type rhs ) noexcept;

      /// \brief Divides \c this quaternion by \p rhs
      ///
      /// \note This is semantically equivalent to (*this) * rhs.inverse()
      ///
      /// \param rhs the quaternion to multiply by
      /// \return reference to \c (*this)
      quaternion& operator /= ( const quaternion& rhs ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_data[4]; ///< The data (w + i*x + j*y + k*z)

      //----------------------------------------------------------------------
      // Private Member Functions
      //----------------------------------------------------------------------
    private:

      /// \brief Initializes the quaternion from a \p angle and \p axis
      ///
      /// \param angle the angle
      /// \param axis the axis
      void from_angle_axis( radian angle, const vector_type& axis ) noexcept;

      /// \brief Initializes the quaternion from a \p yaw, \p pitch, and
      ///        \p roll
      ///
      /// \param yaw the yaw angle
      /// \param pitch the pitch angle
      /// \param roll the roll angle
      void from_angles( radian yaw, radian pitch, radian roll ) noexcept;

      /// \brief Initializes the quaternion from a 3x3 rotation matrix
      ///
      /// \param rot the rotation matrix
      void from_rotation_matrix( const matrix3_type& rot ) noexcept;

      /// \brief Initializes the quaternion from a 4x4 rotation matrix
      ///
      /// \param rot the rotation matrix
      void from_rotation_matrix( const matrix4_type& rot ) noexcept;

    };

    //------------------------------------------------------------------------
    // Free Functions
    //------------------------------------------------------------------------

    /// \brief Swaps two quaternions
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    void swap( quaternion& lhs, quaternion& rhs ) noexcept;

    /// \brief Performs the dot product between \p lhs and \p rhs
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    /// \return the result of the dot product
    quaternion::value_type dot( const quaternion& lhs, const quaternion& rhs ) noexcept;

    /// \brief Computes the magnitude of \p x
    ///
    /// \return the magnitude of \p x
    quaternion::value_type magnitude( const quaternion& x ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Adds two quaternions together, returning the sum
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    /// \return quaternion containing the sum
    quaternion operator + ( const quaternion& lhs, const quaternion& rhs ) noexcept;

    /// \brief Subtracts one quaternion from the other, returning the
    ///        difference
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    /// \return quaternion containing the difference
    quaternion operator - ( const quaternion& lhs, const quaternion& rhs ) noexcept;

    /// \brief Multiplies two quaternions together, returning the product
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    /// \return quaternion containing the product
    quaternion operator * ( const quaternion& lhs, const quaternion& rhs ) noexcept;

    /// \brief Divides two quaternions together, returning the quotient
    ///
    /// \note Strictly speaking, this isn't exactly dividing so much as it
    ///       is multiplying by the inverse of \p rhs
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    /// \return quaternion containing the quotient
    quaternion operator / ( const quaternion& lhs, const quaternion& rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Multiplies the quaternion \p lhs by the scalar multiplier
    ///        \p rhs
    ///
    /// \param lhs the quaternion
    /// \param rhs the scalar to scale the quaternion by
    /// \return the scaled quaternion
    quaternion operator * ( const quaternion& lhs, quaternion::value_type rhs ) noexcept;

    /// \brief Multiplies the quaternion \p rhs by the scalar multiplier
    ///        \p lhs
    ///
    /// \param lhs the scalar to scale the quaternion by
    /// \param rhs the quaternion
    /// \return the scaled quaternion
    quaternion operator * ( quaternion::value_type lhs, const quaternion& rhs ) noexcept;

    /// \brief Performs a vector rotation by multiplying by a quaternion
    ///
    /// \param lhs the quaternion to use for rotation
    /// \param rhs the vector to rotate
    /// \return the rotated vector
    quaternion::vector_type
      operator * ( const quaternion& lhs, const quaternion::vector_type& rhs ) noexcept;

    /// \brief Divides the quaternion \p lhs by the scalar divisor \p rhs
    ///
    /// \param lhs the quaternion
    /// \param rhs the scalar to divide each component by
    /// \return the scaled quaternion
    quaternion operator / ( const quaternion& lhs, quaternion::value_type rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Performs equality comparison between \p lhs and \p rhs
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    /// \return \c true if \p lhs == \p rhs
    bool operator == ( const quaternion& lhs, const quaternion& rhs ) noexcept;

    /// \brief Performs inequality comparison between \p lhs and \p rhs
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    /// \return \c true if \p lhs != \p rhs
    bool operator != ( const quaternion& lhs, const quaternion& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Determines whether two quaternions are almost equal, relative to
    ///        \ref default_tolerance
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    /// \return \c true if \p lhs almost equals \p rhs
    bool almost_equal( const quaternion& lhs, const quaternion& rhs ) noexcept;

    /// \brief Determines whether two quaternions are almost equal, v to
    ///        \p tolerance
    ///
    /// \param lhs the left quaternion
    /// \param rhs the right quaternion
    /// \return \c true if \p lhs almost equals \p rhs
    template<typename Arithmetic, std::enable_if_t<std::is_arithmetic<Arithmetic>::value>* = nullptr>
    bool almost_equal( const quaternion& lhs,
                       const quaternion& rhs,
                       Arithmetic tolerance ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref quaternion
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_quaternion : std::false_type{};

    template<> struct is_quaternion<quaternion> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_quaternion
    template<typename T>
    constexpr bool is_quaternion_v = is_quaternion<T>::value;

  } // namespace math
} // namespace bit

#include "detail/quaternion.inl"

#endif /* BIT_MATH_QUATERNION_HPP */
