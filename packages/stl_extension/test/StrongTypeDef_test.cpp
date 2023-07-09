// --- Utility Includes ---
#include "packages/testing/inc/essentials.hpp"
#include "packages/stl_extension/inc/DynamicArray.hpp"

// --- Internal Includes ---
#include "packages/stl_extension/inc/StrongTypeDef.hpp"

// --- STL Includes ---
#include <vector>


namespace cie::utils {


// Define overloaded functions to check types

using STDVectorBase = std::vector<int>;
using VectorBase    = DynamicArray<int>;
using IntBase       = int;
using PtrBase   = int*;

CIE_STRONG_TYPEDEF(STDVectorBase, SubSTDVector1)
CIE_STRONG_TYPEDEF(STDVectorBase, SubSTDVector2)

CIE_STRONG_TYPEDEF( VectorBase, SubVector1 )
CIE_STRONG_TYPEDEF( VectorBase, SubVector2 )

CIE_STRONG_TYPEDEF( IntBase, SubInt1 )
CIE_STRONG_TYPEDEF( IntBase, SubInt2 )

CIE_STRONG_TYPEDEF( PtrBase, SubPtr1 )
CIE_STRONG_TYPEDEF( PtrBase, SubPtr2 )

struct TestClass
{
    CIE_STRONG_TYPEDEF( VectorBase, MemberVector )
    CIE_STRONG_TYPEDEF( IntBase, MemberInt )
    CIE_STRONG_TYPEDEF( PtrBase, MemberPtr )
    CIE_STRONG_TYPEDEF(STDVectorBase,MemberSTDVector)
};

int testFunction( VectorBase value )                { return 0; }
int testFunction( SubVector1 value )                { return 1; }
int testFunction( SubVector2 value )                { return 2; }
int testFunction( TestClass::MemberVector value )   { return 3; }

int testFunction( IntBase value )                   { return 4; }
int testFunction( SubInt1 value )                   { return 5; }
int testFunction( SubInt2 value )                   { return 6; }
int testFunction( TestClass::MemberInt value )      { return 7; }

int testFunction( PtrBase value )               { return 8; }
int testFunction( SubPtr1 value )               { return 9; }
int testFunction( SubPtr2 value )               { return 10; }
int testFunction( TestClass::MemberPtr value )  { return 11; }

int testFunction(STDVectorBase value)               {return 12;}
int testFunction(SubSTDVector1 value)               {return 13;}
int testFunction(SubSTDVector2 value)               {return 14;}
int testFunction(TestClass::MemberSTDVector value)  {return 15;}


template <class T, class TT>
concept ConvertibleTo
= requires ( T t, const T ct, TT tt )
{
    {TT(t)};    {TT(ct)};
    {tt = t};   {tt = ct};
};

template <class T, class TT>
concept NotConvertibleTo
= !ConvertibleTo<T,TT>;

template <class T, class TT>
bool convertibleTo( T a, TT b )
requires ConvertibleTo<T,TT>
{
    return true;
}

template <class T, class TT>
bool convertibleTo( T a, TT b )
requires NotConvertibleTo<T,TT>
{
    return false;
}







CIE_TEST_CASE( "CIE_STRONG_TYPEDEF", "[stl_extension]" )
{
    CIE_TEST_CASE_INIT( "CIE_STRONG_TYPEDEF" )

    {
        CIE_TEST_CASE_INIT( "DynamicVector" )
        VectorBase              base;
        SubVector1              sub1;
        SubVector2              sub2;
        TestClass::MemberVector member;

        VectorBase tmp1(sub1);
        SubVector1 tmp2(base);
        SubVector1 tmp3 = base;

        CIE_TEST_CHECK( testFunction(base) == 0 );
        CIE_TEST_CHECK( testFunction(sub1) == 1 );
        CIE_TEST_CHECK( testFunction(sub2) == 2 );
        CIE_TEST_CHECK( testFunction(member) == 3 );

        CIE_TEST_CHECK( convertibleTo(base, sub1) );
        CIE_TEST_CHECK( convertibleTo(sub1, base) );
        CIE_TEST_CHECK( !convertibleTo(sub1, sub2) );
    }

    {
        CIE_TEST_CASE_INIT( "int" )
        IntBase              base = 0;
        SubInt1              sub1;
        SubInt2              sub2;
        TestClass::MemberInt member;

        CIE_TEST_CHECK( testFunction(base) == 4 );
        CIE_TEST_CHECK( testFunction(sub1) == 5 );
        CIE_TEST_CHECK( testFunction(sub2) == 6 );
        CIE_TEST_CHECK( testFunction(member) == 7 );

        CIE_TEST_CHECK( convertibleTo(base, sub1) );
        //CIE_TEST_CHECK( convertibleTo(sub1, base) ); // can't inherit from- or manipulate integral types :/
        CIE_TEST_CHECK( !convertibleTo(sub1, sub2) );
    }

    {
        CIE_TEST_CASE_INIT( "int*" )
        PtrBase              base = nullptr;
        SubPtr1              sub1;
        SubPtr2              sub2;
        TestClass::MemberPtr member;

        CIE_TEST_CHECK( testFunction(base) == 8 );
        CIE_TEST_CHECK( testFunction(sub1) == 9 );
        CIE_TEST_CHECK( testFunction(sub2) == 10 );
        CIE_TEST_CHECK( testFunction(member) == 11 );

        // Ptr initialization works differently than for other objects because of
        // pointer decay (arguments are treated as initializers for each component in the "array").
        // So this part can't be checked like this.
        //CIE_TEST_CHECK( convertibleTo(base, sub1) );
        //CIE_TEST_CHECK( convertibleTo(sub1, base) );
        //CIE_TEST_CHECK( !convertibleTo(sub1, sub2) );
    }

    {
        CIE_TEST_CASE_INIT( "std::vector" )
        STDVectorBase              base;
        SubSTDVector1              sub1;
        SubSTDVector2              sub2;
        TestClass::MemberSTDVector member;

        SubVector1 tmp(base);

        CIE_TEST_CHECK( testFunction(base) == 12 );
        CIE_TEST_CHECK( testFunction(sub1) == 13 );
        CIE_TEST_CHECK( testFunction(sub2) == 14 );
        CIE_TEST_CHECK( testFunction(member) == 15 );

        CIE_TEST_CHECK( convertibleTo(base, sub1) );
        CIE_TEST_CHECK( convertibleTo(sub1, base) );
        CIE_TEST_CHECK( !convertibleTo(sub1, sub2) );
    }
    
} // CIE_TEST_CASE CIE_STRONG_TYPEDEF


} // namespace cie::utils