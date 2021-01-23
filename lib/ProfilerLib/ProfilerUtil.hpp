/**
 * @file Time.hpp.h
 * @author ottojo
 * @date 1/23/21
 * Description here TODO
 */

#ifndef PROFILER_PROFILERUTIL_HPP
#define PROFILER_PROFILERUTIL_HPP

#include <chrono>
#include <thread>

namespace profilerUtil {
    using namespace std::chrono;
    using Clock = high_resolution_clock;

    std::size_t micros();

    pid_t pid();

    std::thread::id tid();

    std::size_t tidHash();
}
#endif //PROFILER_PROFILERUTIL_HPP
