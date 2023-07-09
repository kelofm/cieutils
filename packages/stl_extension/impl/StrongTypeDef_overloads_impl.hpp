#ifndef CIE_UTILS_STRONG_TYPEDEF_OVERLOADS_IMPL_HPP
#define CIE_UTILS_STRONG_TYPEDEF_OVERLOADS_IMPL_HPP

namespace cie::utils {


/* --- LOGICAL OPERATORS --- */

template <class T, class Tag>
inline bool
operator==(const StrongTypeDef<T,Tag>& r_lhs,
           const StrongTypeDef<T,Tag>& r_rhs)
{
    return static_cast<const T&>(r_lhs) == static_cast<const T&>(r_rhs);
}

template <class T, class Tag>
inline bool
operator==(const StrongTypeDef<T,Tag>& r_lhs,
           const T& r_rhs)
{
    return static_cast<const T&>(r_lhs) == r_rhs;
}

template <class T, class Tag>
inline bool
operator==(const T& r_lhs,
           const StrongTypeDef<T,Tag>& r_rhs)
{
    return r_lhs == static_cast<const T&>(r_rhs);
}


template <class T, class Tag>
inline bool
operator!=(const StrongTypeDef<T,Tag>& r_lhs,
           const StrongTypeDef<T,Tag>& r_rhs)
{
    return static_cast<const T&>(r_lhs) != static_cast<const T&>(r_rhs);
}

template <class T, class Tag>
inline bool
operator!=(const StrongTypeDef<T,Tag>& r_lhs,
           const T& r_rhs)
{
    return static_cast<const T&>(r_lhs) != r_rhs;
}

template <class T, class Tag>
inline bool
operator!=(const T& r_lhs,
           const StrongTypeDef<T,Tag>& r_rhs)
{
    return r_lhs == static_cast<const T&>(r_rhs);
}


template <class T, class Tag>
inline bool
operator<(const StrongTypeDef<T,Tag>& r_lhs,
          const StrongTypeDef<T,Tag>& r_rhs)
{
    return static_cast<const T&>(r_lhs) < static_cast<const T&>(r_rhs);
}

template <class T,class Tag>
inline bool
operator<(const StrongTypeDef<T,Tag>& r_lhs,
          const T& r_rhs)
{
    return static_cast<const T&>(r_lhs) < r_rhs;
}

template <class T, class Tag>
inline bool
operator<(const T& r_lhs,
          const StrongTypeDef<T,Tag>& r_rhs)
{
    return r_lhs < static_cast<const T&>(r_rhs);
}

template <class T, class Tag>
inline bool
operator>(const StrongTypeDef<T,Tag>& r_lhs,
          const StrongTypeDef<T,Tag>& r_rhs)
{
    return static_cast<const T&>(r_lhs) > static_cast<const T&>(r_rhs);
}

template <class T,class Tag>
inline bool
operator>(const StrongTypeDef<T,Tag>& r_lhs,
          const T& r_rhs)
{
    return static_cast<const T&>(r_lhs) > r_rhs;
}

template <class T, class Tag>
inline bool
operator>(const T& r_lhs,
          const StrongTypeDef<T,Tag>& r_rhs)
{
    return r_lhs > static_cast<const T&>(r_rhs);
}


template <class T, class Tag>
inline bool
operator<=(const StrongTypeDef<T,Tag>& r_lhs,
           const StrongTypeDef<T,Tag>& r_rhs)
{
    return static_cast<const T&>(r_lhs) <= static_cast<const T&>(r_rhs);
}

template <class T,class Tag>
inline bool
operator<=(const StrongTypeDef<T,Tag>& r_lhs,
           const T& r_rhs)
{
    return static_cast<const T&>(r_lhs) <= r_rhs;
}

template <class T, class Tag>
inline bool
operator<=(const T& r_lhs,
           const StrongTypeDef<T,Tag>& r_rhs)
{
    return r_lhs <= static_cast<const T&>(r_rhs);
}

template <class T, class Tag>
inline bool
operator>=(const StrongTypeDef<T,Tag>& r_lhs,
           const StrongTypeDef<T,Tag>& r_rhs)
{
    return static_cast<const T&>(r_lhs) >= static_cast<const T&>(r_rhs);
}

template <class T,class Tag>
inline bool
operator>=(const StrongTypeDef<T,Tag>& r_lhs,
           const T& r_rhs)
{
    return static_cast<const T&>(r_lhs) >= r_rhs;
}

template <class T, class Tag>
inline bool
operator>=(const T& r_lhs,
           const StrongTypeDef<T,Tag>& r_rhs)
{
    return r_lhs >= static_cast<const T&>(r_rhs);
}


/* --- ARITHMETIC OPERATORS --- */



/* --- STREAM OPERATORS --- */


} // namespace cie::utils

#endif