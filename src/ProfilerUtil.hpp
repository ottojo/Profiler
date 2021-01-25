/**
 * @file Time.hpp.h
 * @author ottojo
 * @date 1/23/21
 */

#ifndef PROFILER_PROFILERUTIL_HPP
#define PROFILER_PROFILERUTIL_HPP

#include <chrono>      // for chrono, high_resolution_clock
#include <sys/types.h> // for pid_t
#include <thread>      // for thread, thread::id

namespace profilerUtil {
    using namespace std::chrono;
    using Clock = high_resolution_clock;

    std::size_t micros();

    pid_t pid();

    std::thread::id tid();

    std::size_t tidHash();
} // namespace profilerUtil
#endif // PROFILER_PROFILERUTIL_HPP
