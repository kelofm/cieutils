// --- Internal Includes ---
#include "packages/concurrency/inc/ThreadPoolSingleton.hpp"
#include "packages/macros/inc/checks.hpp"

// --- STL Includes ---
#include <thread>
#include <algorithm>


namespace cie::mp {


std::optional<ThreadPoolBase::UniquePointer> ThreadPoolSingleton::_p_pool;


Ref<ThreadPoolBase> ThreadPoolSingleton::getBase()
{
    if (!_p_pool)
        _p_pool.emplace(new ThreadPoolBase);

    return *_p_pool.value();
}


void ThreadPoolSingleton::shutDown()
{
    if (_p_pool) [[likely]]
    {
        const auto& r_threads = _p_pool.value()->threads();
        //CIE_CHECK(
        //    std::find_if(
        //        r_threads.begin(),
        //        r_threads.end(),
        //        [](const auto& r_thread) {return r_thread.get_id() == std::this_thread::get_id();}
        //    ) != r_threads.end(),
        //    "ThreadPoolSingleton::shutDown must be called from the master thread"
        //)

        _p_pool.reset();
    }
}


ThreadPool<> ThreadPoolSingleton::get()
{
    return ThreadPool<>(ThreadPoolSingleton::getBase());
}


} // namespace cie::mp
