/**
 * \file clamped.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_CLAMPED_HPP
#define BIT_MATH_CLAMPED_HPP

#include <utility>

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A runtime clamped type that ensures that the value range sits
    ///        between [0,1]
    ///
    /// This adds the overhead of a ternary check on construction to clamp the
    /// values
    ///
    /// \tparam T the type of the underlying clamped
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class clamped
    {
      //----------------------------------------------------------------------
      // Public Types
      //----------------------------------------------------------------------
    public:

      using value_type = T;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a clamped from a given \p value
      ///
      /// \param value the value to clamp
      constexpr clamped( const T& value ) noexcept;

      /// \copydoc clamped::clamped( const T& )
      constexpr clamped( T&& value ) noexcept;

      /// \brief Constructs a clamped from a clamped of a different type
      ///
      /// \param other the other clamped
      template<typename U>
      constexpr clamped( const clamped<U>& other ) noexcept;

      /// \copydoc clamped::clamped( const clamped<U>& )
      template<typename U>
      constexpr clamped( clamped<U>&& other ) noexcept;

      /// \brief Copy-constructs a clamped from another clamped
      ///
      /// \param other the other clamped
      constexpr clamped( const clamped& other ) noexcept = default;

      /// \brief Move-constructs a clamped from another clamped
      ///
      /// \param other the other clamped
      constexpr clamped( clamped&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a clamped from another clamped
      ///
      /// \param other the other clamped to copy
      /// \return reference to \c (*this)
      clamped& operator=( const clamped& other ) noexcept = default;

      /// \brief Move-assigns a clamped from another clamped
      ///
      /// \param other the other clamped to move
      /// \return reference to \c (*this)
      clamped& operator=( clamped& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Conversion
      //----------------------------------------------------------------------
    public:

      /// \brief Conversion to the underlying type
      constexpr operator T() const noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------
    public:

      constexpr clamped& operator+=( const clamped& rhs ) noexcept;

      template<typename U>
      constexpr clamped& operator+=( U&& scalar ) noexcept;

      constexpr clamped& operator-=( const clamped& rhs ) noexcept;

      template<typename U>
      constexpr clamped& operator-=( U&& scalar ) noexcept;

      constexpr clamped& operator*=( const clamped& rhs ) noexcept;

      template<typename U>
      constexpr clamped& operator*=( U&& scalar ) noexcept;

      constexpr clamped& operator/=( const clamped& rhs ) noexcept;

      template<typename U>
      constexpr clamped& operator/=( U&& scalar ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_value; ///< The value of the clamped

      template<typename>
      friend class clamped;

    };

    //------------------------------------------------------------------------
    // Operators
    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator+( const clamped<T>& lhs, const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator+( T&& lhs, const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator+( const clamped<T>& lhs, U&& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator-( const clamped<T>& lhs, const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator-( T&& lhs, const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator-( const clamped<T>& lhs, U&& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator*( const clamped<T>& lhs, const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator*( T&& lhs, const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator*( const clamped<T>& lhs, U&& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator/( const clamped<T>& lhs, const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator/( T&& lhs, const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr clamped<std::common_type_t<T,U>>
      operator/( const clamped<T>& lhs, U&& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    template<typename T, typename U>
    constexpr bool operator==( const clamped<T>& lhs,
                               const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr bool operator!=( const clamped<T>& lhs,
                               const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr bool operator<( const clamped<T>& lhs,
                              const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr bool operator>( const clamped<T>& lhs,
                              const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr bool operator<=( const clamped<T>& lhs,
                               const clamped<U>& rhs ) noexcept;

    template<typename T, typename U>
    constexpr bool operator>=( const clamped<T>& lhs,
                               const clamped<U>& rhs ) noexcept;

    //----------------------------------------------------------------------------
    // Type Traits
    //----------------------------------------------------------------------------

    /// \brief Trait to detect whether \p T is a \ref clamped
    ///
    /// The result is aliased as \c ::value
    template<typename T> struct is_clamped : std::false_type{};

    template<typename T> struct is_clamped<clamped<T>> : std::true_type{};

    /// \brief Helper variable template to retrieve the result of \ref is_clamped
    template<typename T>
    constexpr bool is_clamped_v = is_clamped<T>::value;
  } // namespace math
} // namespace bit

#include "detail/clamped.inl"

#endif /* BIT_MATH_CLAMPED_HPP */
