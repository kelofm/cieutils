#ifndef CIE_UTILS_TESTING_CONSTRUCTOR_TRACKER_HPP
#define CIE_UTILS_TESTING_CONSTRUCTOR_TRACKER_HPP

// --- Internal Includes ---
#include "packages/types/inc/types.hpp"

// --- STL Includes ---
#include <mutex>


namespace cie::utils {


template <class Tag = void>
class ConstructorTracker
{
public:
    using tag_type = Tag;

public:
    ConstructorTracker();

    ConstructorTracker(ConstructorTracker&& r_rhs);

    ConstructorTracker(const ConstructorTracker& r_rhs);

    ConstructorTracker& operator=(ConstructorTracker&& r_rhs);

    ConstructorTracker& operator=(const ConstructorTracker& r_rhs);

    ~ConstructorTracker();

    static const Size numberOfActiveInstances();

    static const Size numberOfDefaultConstructorCalls();

    static const Size numberOfMoveConstructorCalls();

    static const Size numberOfCopyConstructorCalls();

    static const Size numberOfMoveAssignmentCalls();

    static const Size numberOfCopyAssignmentCalls();

    static const Size numberOfDestructorCalls();

    static void reset();

private:
    static Size _numberOfActiveInstances;

    static Size _numberOfDefaultConstructorCalls;

    static Size _numberOfMoveConstructorCalls;

    static Size _numberOfCopyConstructorCalls;

    static Size _numberOfMoveAssignmentCalls;

    static Size _numberOfCopyAssignmentCalls;

    static Size _numberOfDestructorCalls;

    static std::mutex _mutex;
};


} // namespace cie::utils

#include "packages/testing/impl/ConstructorTracker_impl.hpp"

#endif