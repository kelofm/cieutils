#ifndef CIE_UTILS_STRONG_TYPEDEF_OVERLOADS_HPP
#define CIE_UTILS_STRONG_TYPEDEF_OVERLOADS_HPP

// --- Internal Includes ---
#include "packages/stl_extension/inc/StrongTypeDef.hpp"


namespace cie::utils {


/* --- LOGICAL OPERATORS --- */

template <class T, class Tag>
bool operator==(const StrongTypeDef<T,Tag>& r_lhs,
                const StrongTypeDef<T,Tag>& r_rhs);

template <class T, class Tag>
bool operator==(const StrongTypeDef<T,Tag>& r_lhs,
                const T& r_rhs);

template <class T, class Tag>
bool operator==(const T& r_lhs,
                const StrongTypeDef<T,Tag>& r_rhs);


template <class T, class Tag>
bool operator!=(const StrongTypeDef<T,Tag>& r_lhs,
                const StrongTypeDef<T,Tag>& r_rhs);

template <class T, class Tag>
bool operator!=(const StrongTypeDef<T,Tag>& r_lhs,
                const T& r_rhs);

template <class T, class Tag>
bool operator!=(const T& r_lhs,
                const StrongTypeDef<T,Tag>& r_rhs);


template <class T, class Tag>
bool operator<(const StrongTypeDef<T,Tag>& r_lhs,
               const StrongTypeDef<T,Tag>& r_rhs);

template <class T,class Tag>
bool operator<(const StrongTypeDef<T,Tag>& r_lhs,
               const T& r_rhs);

template <class T, class Tag>
bool operator<(const T& r_lhs,
               const StrongTypeDef<T,Tag>& r_rhs);

template <class T, class Tag>
bool operator>(const StrongTypeDef<T,Tag>& r_lhs,
               const StrongTypeDef<T,Tag>& r_rhs);

template <class T,class Tag>
bool operator>(const StrongTypeDef<T,Tag>& r_lhs,
               const T& r_rhs);

template <class T, class Tag>
bool operator>(const T& r_lhs,
               const StrongTypeDef<T,Tag>& r_rhs);


template <class T, class Tag>
bool operator<=(const StrongTypeDef<T,Tag>& r_lhs,
                const StrongTypeDef<T,Tag>& r_rhs);

template <class T,class Tag>
bool operator<=(const StrongTypeDef<T,Tag>& r_lhs,
                const T& r_rhs);

template <class T, class Tag>
bool operator<=(const T& r_lhs,
                const StrongTypeDef<T,Tag>& r_rhs);

template <class T, class Tag>
bool operator>=(const StrongTypeDef<T,Tag>& r_lhs,
                const StrongTypeDef<T,Tag>& r_rhs);

template <class T,class Tag>
bool operator>=(const StrongTypeDef<T,Tag>& r_lhs,
                const T& r_rhs);

template <class T, class Tag>
bool operator>=(const T& r_lhs,
                const StrongTypeDef<T,Tag>& r_rhs);


/* --- ARITHMETIC OPERATORS --- */

// TODO


/* --- STREAM OPERATORS --- */

// TODO


} // namespace cie::utils

#include "packages/stl_extension/impl/StrongTypeDef_overloads_impl.hpp"

#endif