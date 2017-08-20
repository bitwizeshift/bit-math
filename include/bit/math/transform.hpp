/**
 * \file transform.hpp
 *
 * \brief This header contains a wrapper around mathematical (graphical)
 *        transformation logic
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_TRANSFORM_HPP
#define BIT_MATH_TRANSFORM_HPP

#include "angles.hpp"     // bit::math::radian
#include "vector.hpp"     // bit::math::vec3
#include "matrix.hpp"     // bit::math::mat4
#include "quaternion.hpp" // bit::math::quaternion

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    //////////////////////////////////////////////////////////////////////////
    class transform
    {
      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      transform() noexcept;

      transform( const transform& other ) noexcept = default;

      transform( transform&& other ) noexcept = default;

      //----------------------------------------------------------------------

      transform& operator=( const transform& other ) noexcept = default;

      transform& operator=( transform&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      void translate( float_t x, float_t y, float_t z ) noexcept;
      void translate( const vec3& translation ) noexcept;

      void translate_x( float_t x ) noexcept;
      void translate_y( float_t y ) noexcept;
      void translate_z( float_t z ) noexcept;

      //----------------------------------------------------------------------

      void set_position( float_t x, float_t y, float_t z ) noexcept;
      void set_position( const vec3& position ) noexcept;

      void set_position_x( float_t x ) noexcept;
      void set_position_y( float_t y ) noexcept;
      void set_position_z( float_t z ) noexcept;

      //----------------------------------------------------------------------

      void rotate( radian yaw, radian pitch, radian roll ) noexcept;
      void rotate( radian angle, const vec3& axis ) noexcept;
      void rotate( const quaternion& rotation ) noexcept;

      void rotate_yaw( radian angle ) noexcept;
      void rotate_pitch( radian angle ) noexcept;
      void rotate_roll( radian angle ) noexcept;

      //----------------------------------------------------------------------

      void set_rotation( radian yaw, radian pitch, radian roll ) noexcept;
      void set_rotation( radian angle, const vec3& axis ) noexcept;
      void set_rotation( const quaternion& rotation ) noexcept;

      void set_angle_roll( radian angle ) noexcept;
      void set_angle_pitch( radian angle ) noexcept;
      void set_angle_yaw( radian angle ) noexcept;

      //----------------------------------------------------------------------

      void scale( float_t x, float_t y, float_t z ) noexcept;
      void scale( vec3 scale ) noexcept;

      void scale_x( float_t scale ) noexcept;
      void scale_y( float_t scale ) noexcept;
      void scale_z( float_t scale ) noexcept;

      //----------------------------------------------------------------------

      void set_scale( float_t x, float_t y, float_t z ) noexcept;
      void set_scale( vec3 scale ) noexcept;

      void set_scale_x( float_t scale ) noexcept;
      void set_scale_y( float_t scale ) noexcept;
      void set_scale_z( float_t scale ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      const vec3& scale() const noexcept;
      const vec3& position() const noexcept;
      const quaternion& rotation() const noexcept;

      float_t scale_x() const noexcept;
      float_t scale_y() const noexcept;
      float_t scale_z() const noexcept;

      float_t x() const noexcept;
      float_t y() const noexcept;
      float_t z() const noexcept;

      radian roll() const noexcept;
      radian pitch() const noexcept;
      radian yaw() const noexcept;

      const mat4& data() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      mutable mat4 m_transform;   ///< The cached transformation
      quaternion   m_rotation;    ///< Rotation of the model
      vec3         m_translation; ///< Position of the model
      vec3         m_scale;       ///< Scale of the model
      mutable bool m_is_dirty;    ///< flag indicating a dirty transform

      //----------------------------------------------------------------------
      // Private Member Functions
      //----------------------------------------------------------------------
    private:

      void update() const noexcept;

    };
  } // namespace math
} // namespace bit

#include "detail/transform.inl"

#endif /* BIT_MATH_TRANSFORM_HPP */
