/**
 * \file angles.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_ANGLES_HPP
#define BIT_MATH_ANGLES_HPP

#include "math.hpp"

// IWYU pragma: begin_exports
#include "detail/angles/radian.hpp"
#include "detail/angles/degree.hpp"
#include "detail/angles/gradian.hpp"
// IWYU pragma: end_exports

namespace bit {
  namespace math {

    //------------------------------------------------------------------------
    // Literals
    //------------------------------------------------------------------------

    inline namespace literals {
      inline namespace angle_literals {

        constexpr radian operator""_rad( long double angle ) noexcept;

        constexpr gradian operator""_grad( long double angle ) noexcept;

        constexpr degree operator""_deg( long double angle ) noexcept;

      } // inline namespace angle_literals
    } // inline namespace literals

    template<typename T>
    struct is_angle : std::false_type{};

    template<> struct is_angle<radian> : std::true_type{};
    template<> struct is_angle<gradian> : std::true_type{};
    template<> struct is_angle<degree> : std::true_type{};

    //------------------------------------------------------------------------
    // Casting
    //------------------------------------------------------------------------

    inline namespace casts {
      inline namespace angle_casts {

        /// \{
        /// \brief Performs a cast between angle types
        ///
        /// \tparam To the angle type to cast to
        /// \param from the angle to cast from
        /// \return the casted angle
        template<typename To, typename From>
        constexpr To angle_cast( From from ) noexcept;

        template<> constexpr radian angle_cast( radian from ) noexcept;
        template<> constexpr degree angle_cast( radian from ) noexcept;
        template<> constexpr gradian angle_cast( radian from ) noexcept;

        template<> constexpr degree angle_cast( degree from ) noexcept;
        template<> constexpr radian angle_cast( degree from ) noexcept;
        template<> constexpr gradian angle_cast( degree from ) noexcept;

        template<> constexpr gradian angle_cast( gradian from ) noexcept;
        template<> constexpr radian angle_cast( gradian from ) noexcept;
        template<> constexpr degree angle_cast( gradian from ) noexcept;
        /// \}
      } // inline namespace math_casts
    } // inline namespace casts

    //------------------------------------------------------------------------
    // Rounding
    //------------------------------------------------------------------------

    /// \brief Rounds a given \ref radian \p rad
    ///
    /// \param rad the radian to round
    /// \return the rounded radian
    radian round( radian rad ) noexcept;

    /// \brief Rounds a given \ref gradian \p grad
    ///
    /// \param grad the gradian to round
    /// \return the rounded gradian
    gradian round( gradian grad ) noexcept;

    /// \brief Rounds a given \ref degree \p deg
    ///
    /// \param deg the degree to round
    /// \return the rounded degree
    degree round( degree deg ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Rounds a given \ref radian \p rad up as if by calling
    ///        \code ceil( rad.value() ) \endcode
    ///
    /// \param rad the radian to round up
    /// \return the rounded radian
    radian ceil( radian rad ) noexcept;

    /// \brief Rounds a given \ref gradian \p rad up as if by calling
    ///        \code ceil( grad.value() ) \endcode
    ///
    /// \param grad the gradian to round up
    /// \return the rounded gradian
    gradian ceil( gradian grad ) noexcept;

    /// \brief Rounds a given \ref degree \p deg up as if by calling
    ///        \code ceil( deg.value() ) \endcode
    ///
    /// \param deg the degree to round up
    /// \return the rounded degree
    degree ceil( degree deg ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Rounds a given \ref radian \p rad up as if by calling
    ///        \code floor( rad.value() ) \endcode
    ///
    /// \param rad the radian to round down
    /// \return the rounded radian
    radian floor( radian rad ) noexcept;

    /// \brief Rounds a given \ref gradian \p grad up as if by calling
    ///        \code floor( grad.value() ) \endcode
    ///
    /// \param grad the gradian to round down
    /// \return the rounded radian
    gradian floor( gradian grad ) noexcept;

    /// \brief Rounds a given \ref degree \p deg up as if by calling
    ///        \code floor( deg.value() ) \endcode
    ///
    /// \param deg the degree to round down
    /// \return the rounded degree
    degree floor( degree deg ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Truncates the given \ref radian \p rad as if by calling
    ///        \code trunc( rad.value() ) \endcode
    ///
    /// \param rad the radian to truncate
    /// \return the rounded radian
    radian trunc( radian rad ) noexcept;

    /// \brief Truncates the given \ref gradian \p grad as if by calling
    ///        \code trunc( grad.value() ) \endcode
    ///
    /// \param grad the gradian to truncate
    /// \return the rounded gradian
    gradian trunc( gradian rad ) noexcept;

    /// \brief Truncates the given \ref degree \p deg as if by calling
    ///        \code trunc( deg.value() ) \endcode
    ///
    /// \param deg the degree to truncate
    /// \return the rounded degree
    degree trunc( degree deg ) noexcept;

    //------------------------------------------------------------------------
    // Absolute Values
    //------------------------------------------------------------------------

    /// \brief Retrieves the absolute value of the given \ref radian \p rad
    ///        as if by calling \code abs( rad.value() ) \endcode
    ///
    /// \param rad the radian to retrieve the absolute value of
    /// \return the rounded radian
    radian abs( radian rad ) noexcept;

    /// \brief Retrieves the absolute value of the given \ref gradian \p grad
    ///        as if by calling \code abs( grad.value() ) \endcode
    ///
    /// \param rad the gradian to retrieve the absolute value of
    /// \return the rounded gradian
    gradian abs( gradian grad ) noexcept;

    /// \brief Retrieves the absolute value of the given \ref degree \p deg
    ///        as if by calling \code abs( deg.value() ) \endcode
    ///
    /// \param deg the degree to retrieve the absolute value of
    /// \return the rounded degree
    degree abs( degree deg ) noexcept;

    //------------------------------------------------------------------------
    // Runtime Trigonometry
    //------------------------------------------------------------------------

#ifndef BIT_MATH_CACHED_TRIG
    inline
#endif
    namespace runtime {

      //----------------------------------------------------------------------
      // Trigonometry
      //----------------------------------------------------------------------

      /// \brief Calculates the cosine of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c cos(rad)
      float_t cos( radian rad ) noexcept;

      /// \brief Calculates the cosine of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c cos(grad)
      float_t cos( gradian grad ) noexcept;

      /// \brief Calculates the cosine of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c cos(deg)
      float_t cos( degree deg ) noexcept;

      /// \copydoc cos( radian )
      float_t cos( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the sine of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c sin(rad)
      float_t sin( radian rad ) noexcept;

      /// \brief Calculates the sine of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c sin(grad)
      float_t sin( gradian grad ) noexcept;

      /// \brief Calculates the sine of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c sin(deg)
      float_t sin( degree deg ) noexcept;

      /// \copydoc sin( radian )
      float_t sin( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the tangent of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c tan(rad)
      float_t tan( radian rad ) noexcept;

      /// \brief Calculates the tangent of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c tan(grad)
      float_t tan( gradian grad ) noexcept;

      /// \brief Calculates the tangent of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c tan(deg)
      float_t tan( degree deg ) noexcept;

      /// \copydoc tan( radian )
      float_t tan( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the secant of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c sec(rad)
      float_t sec( radian rad ) noexcept;

      /// \brief Calculates the secant of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c sec(grad)
      float_t sec( gradian grad ) noexcept;

      /// \brief Calculates the secant of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c sec(deg)
      float_t sec( degree deg ) noexcept;

      /// \copydoc sec( radian )
      float_t sec( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the cosecant of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c csc(rad)
      float_t csc( radian rad ) noexcept;

      /// \brief Calculates the cosecant of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c csc(grad)
      float_t csc( gradian grad ) noexcept;

      /// \brief Calculates the cosecant of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c csc(deg)
      float_t csc( degree deg ) noexcept;

      /// \copydoc csc( radian )
      float_t csc( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the cotangent of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c cot(rad)
      float_t cot( radian rad ) noexcept;

      /// \brief Calculates the cotangent of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c cot(grad)
      float_t cot( gradian grad ) noexcept;

      /// \brief Calculates the cotangent of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c cot(deg)
      float_t cot( degree deg ) noexcept;

      /// \copydoc cot( radian )
      float_t cot( float_t rad ) noexcept;

    } // [inline] namespace runtime

    //------------------------------------------------------------------------
    // Cached Trigonometry
    //------------------------------------------------------------------------

#ifdef BIT_MATH_CACHED_TRIG
    inline
#endif
    namespace cached {

      namespace detail {

        float_t sin_lookup( float_t angle ) noexcept;

        float_t tan_lookup( float_t angle ) noexcept;

      } // namespace detail


      //----------------------------------------------------------------------
      // Trigonometry
      //----------------------------------------------------------------------

      /// \brief Calculates the cosine of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c cos(rad)
      float_t cos( radian rad ) noexcept;

      /// \brief Calculates the cosine of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c cos(grad)
      float_t cos( gradian grad ) noexcept;

      /// \brief Calculates the cosine of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c cos(deg)
      float_t cos( degree deg ) noexcept;

      /// \copydoc cos( radian )
      float_t cos( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the sine of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c sin(rad)
      float_t sin( radian rad ) noexcept;

      /// \brief Calculates the sine of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c sin(grad)
      float_t sin( gradian grad ) noexcept;

      /// \brief Calculates the sine of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c sin(deg)
      float_t sin( degree deg ) noexcept;

      /// \copydoc sin( radian )
      float_t sin( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the tangent of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c tan(rad)
      float_t tan( radian rad ) noexcept;

      /// \brief Calculates the tangent of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c tan(grad)
      float_t tan( gradian grad ) noexcept;

      /// \brief Calculates the tangent of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c tan(deg)
      float_t tan( degree deg ) noexcept;

      /// \copydoc tan( radian )
      float_t tan( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the secant of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c sec(rad)
      float_t sec( radian rad ) noexcept;

      /// \brief Calculates the secant of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c sec(grad)
      float_t sec( gradian grad ) noexcept;

      /// \brief Calculates the secant of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c sec(deg)
      float_t sec( degree deg ) noexcept;

      /// \copydoc sec( radian )
      float_t sec( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the cosecant of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c csc(rad)
      float_t csc( radian rad ) noexcept;

      /// \brief Calculates the cosecant of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c csc(grad)
      float_t csc( gradian grad ) noexcept;

      /// \brief Calculates the cosecant of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c csc(deg)
      float_t csc( degree deg ) noexcept;

      /// \copydoc csc( radian )
      float_t csc( float_t rad ) noexcept;

      //----------------------------------------------------------------------

      /// \brief Calculates the cotangent of the given \ref radian angle, \p rad
      ///
      /// \param rad the angle
      /// \return the result of \c cot(rad)
      float_t cot( radian rad ) noexcept;

      /// \brief Calculates the cotangent of the given \ref gradian angle, \p grad
      ///
      /// \param grad the angle
      /// \return the result of \c cot(grad)
      float_t cot( gradian grad ) noexcept;

      /// \brief Calculates the cotangent of the given \ref degree angle, \p deg
      ///
      /// \param deg the angle
      /// \return the result of \c cot(deg)
      float_t cot( degree deg ) noexcept;

      /// \copydoc cot( radian )
      float_t cot( float_t rad ) noexcept;

    } // [inline] namespace cached

    //------------------------------------------------------------------------
    // Inverse Trigonometry
    //------------------------------------------------------------------------

    radian arccos( float_t f ) noexcept;
    radian arcsin( float_t f ) noexcept;
    radian arctan( float_t f ) noexcept;
    radian arctan2( float_t f1, float_t f2 ) noexcept;

  } // namespace math

  // Note: Below is a pair of namespace aliases + using directives. Normally
  // in headers, using directives are an anti-pattern; but this is done
  // to import inline namespaces into a new inline namespace

  inline namespace literals {
    namespace angle_literals = math::literals::angle_literals;
    using namespace angle_literals;
  } // inline namespace literals

  inline namespace casts {
    namespace angle_casts = math::casts::angle_casts;
    using namespace angle_casts;
  } // inline namespace casts

} // namespace bit

#include "detail/angles.inl"

#endif /* BIT_MATH_ANGLES_HPP */
