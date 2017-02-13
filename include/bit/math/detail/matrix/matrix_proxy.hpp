/**
 * \file matrix_proxy.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_MATH_DETAIL_MATRIX_MATRIX_PROXY_HPP
#define BIT_MATH_DETAIL_MATRIX_MATRIX_PROXY_HPP

namespace bit {
  namespace math {

    //////////////////////////////////////////////////////////////////////////
    ///
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class matrix_proxy
    {
      //----------------------------------------------------------------------
      // Public Types
      //----------------------------------------------------------------------
    public:

      using value_type = std::decay_t<T>;
      using reference  = value_type&;

      using size_type  = std::size_t;
      using index_type = std::ptrdiff_t;

      //------------------------------------------------------------------------
      // Constructors
      //------------------------------------------------------------------------
    public:

      /// \brief Constructs a matrix_proxy with the given pointer
      ///
      /// \param ptr pointer to the proxy entry
      constexpr explicit matrix_proxy( T* ptr ) noexcept;

      //------------------------------------------------------------------------
      // Element Access
      //------------------------------------------------------------------------
    public:

      /// \brief Retrieves the entry at the given index
      ///
      /// \param row the row to access
      /// \return reference to the entry
      constexpr reference operator[]( index_type row ) const noexcept;

      //------------------------------------------------------------------------
      // Private Members
      //------------------------------------------------------------------------
    private:

      T* const m_data; ///< Pointer to the proxy data
    };

  } // namespace math
} // namespace bit

#include "matrix_proxy.inl"

#endif /* BIT_MATH_DETAIL_MATRIX_MATRIX_PROXY_HPP */
