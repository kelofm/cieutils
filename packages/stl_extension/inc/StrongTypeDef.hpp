#ifndef CIE_UTILS_STL_EXTENSION_STRONG_TYPEDEF_HPP
#define CIE_UTILS_STL_EXTENSION_STRONG_TYPEDEF_HPP

// --- Utility Includes ---
#include "packages/compile_time/packages/concepts/inc/basic_concepts.hpp"


namespace cie::utils {


template <class T, class Tag>
class StrongTypeDef {};


/** Wrapper class for creating non-interchangable typedefs
 * 
 *              Base
 *             /    \
 *            /      \
 *           /        \
 *          /          \
 *         /            \
 *    TypeDef1---X---TypeDef2
 *
 *  - Typedefd classes are constructible from and convertible to the Base class
 *  - Typedefd classes (TypeDef1 and TypeDef2) sharing the same Base are not
 *    implicitly convertible (though can be converted by explicitly casting through Base)
 *  - Typedefd classes share (almost*) all functionality of the Base class
 * 
 *  @note * operator overloads (templated ones especially) need a bit of explicit nudging
 *  to get picked up by the compiler. Also, there's no efficient and general way to get list
 *  initialization working.
 */
template <concepts::Deriveable T, class Tag>
class StrongTypeDef<T,Tag> : public T
{
public:
    /// Inherit all base constructors
    using T::T;

    StrongTypeDef(T&& r_rhs) requires concepts::MoveConstructible<T>
        : T(std::move(r_rhs))
    {}

    /// Allow move constructor if possible
    StrongTypeDef(StrongTypeDef<T,Tag>&& r_rhs) requires concepts::MoveConstructible<T>
        : T(std::move(r_rhs))
    {}

    StrongTypeDef(const T& r_rhs) requires concepts::CopyConstructible<T>
        : T(r_rhs)
    {}

    StrongTypeDef(T& r_rhs) requires concepts::CopyConstructible<T>
        : T(r_rhs)
    {}

    /// Allow copy constructor if possible
    StrongTypeDef(const StrongTypeDef<T,Tag>& r_rhs) requires concepts::CopyConstructible<T>
        : T(r_rhs)
    {}

    /// Inherit all base class assignment operators
    using T::operator=;

    StrongTypeDef<T,Tag>& operator=(T&& r_rhs) requires concepts::MoveAssignable<T>
    {return static_cast<T&>(*this) = std::move(r_rhs);}

    /// Allow move assignment operator if possible
    StrongTypeDef<T,Tag>& operator=(StrongTypeDef<T,Tag>&& r_rhs) requires concepts::MoveAssignable<T>
    {return static_cast<T&>(*this) = std::move(static_cast<T&&>(r_rhs));}

    StrongTypeDef<T,Tag>& operator=(const T& r_rhs) requires concepts::CopyAssignable<T>
    {return static_cast<T&>(*this) = r_rhs;}

    StrongTypeDef<T,Tag>& operator=(T& r_rhs) requires concepts::CopyAssignable<T>
    {return static_cast<T&>(*this) = r_rhs;}

    /// Allow copy assignment operator if possible
    StrongTypeDef<T,Tag>& operator=(const StrongTypeDef<T,Tag>& r_rhs) requires concepts::CopyAssignable<T>
    {return static_cast<T&>(*this) = static_cast<const T&>(r_rhs);}

    StrongTypeDef<T,Tag>& operator=(StrongTypeDef<T,Tag>& r_rhs) requires concepts::CopyAssignable<T>
    {return static_cast<T&>(*this) = static_cast<const T&>(r_rhs);}

    /// Delete every assignment operator that's not in the base class, move or copy assignment operator
    template <class TT>
    StrongTypeDef<T,Tag>& operator=(TT&& r_rhs) = delete;

    operator T&()
    {return static_cast<T&>(*this);}

    operator const T&() const
    {return static_cast<const T&>(*this);}
};


template <concepts::Integral T, class Tag>
class StrongTypeDef<T,Tag>
{
public:
    StrongTypeDef()
    {}

    StrongTypeDef(T wrapped)
        : _wrapped(wrapped)
    {}

    template <class TT>
    StrongTypeDef(TT tt) = delete;

    StrongTypeDef<T,Tag>& operator=(T rhs)
    {return _wrapped = rhs;}

    operator T() const
    {return _wrapped;}

    operator const T() const
    {return _wrapped;}

    operator T&()
    {return _wrapped;}

    operator const T&() const
    {return _wrapped;}

private:
    T _wrapped;
};


} // namespace cie::utils


#define CIE_STRONG_TYPEDEF( BaseType, SubType )                                                 \
    struct _typedef_ ## SubType ## _ ## BaseType ## _tag {};                                \
    typedef cie::utils::StrongTypeDef<                                                   \
                            BaseType ,                                                      \
                           _typedef_  ## SubType ## _ ## BaseType ## _tag> SubType;


#include "packages/stl_extension/inc/StrongTypeDef_overloads.hpp"

#endif