#ifndef CIE_UTILS_STL_EXTENSION_STATIC_ARRAY_HPP
#define CIE_UTILS_STL_EXTENSION_STATIC_ARRAY_HPP

// --- Internal Includes ---
#include "packages/stl_extension/inc/STLContainerBase.hpp"

// --- STL Includes ---
#include <array>


namespace cie {


template <class TValue, Size ArraySize>
using StaticArray = STLContainerBase<std::array<TValue,ArraySize>>;


template <class T>
struct StaticArrayTraits
{};


template <class T, Size S>
struct StaticArrayTraits<StaticArray<T,S>>
{
    static constexpr const Size size = S;
};


template <class T, Size S>
struct StaticArrayTraits<std::array<T,S>>
{
    static constexpr const Size size = S;
};


} // namespace cie


#endif