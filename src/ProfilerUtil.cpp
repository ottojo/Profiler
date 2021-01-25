/**
 * @file Time.cpp.c
 * @author ottojo
 * @date 1/23/21
 */

#include "ProfilerUtil.hpp"

#include <unistd.h>

namespace profilerUtil {
    std::size_t micros() {
        return duration_cast<microseconds>(Clock::now().time_since_epoch()).count();
    }

    pid_t pid() {
        return getpid();
    }

    std::thread::id tid() {
        return std::this_thread::get_id();
    }

    std::size_t tidHash() {
        return std::hash<std::thread::id>{}(tid());
    }
} // namespace profilerUtil
