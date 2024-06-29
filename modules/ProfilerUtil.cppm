/**
 * @author ottojo
 * @date 1/23/21
 */
 module;


#include <chrono>      // for chrono, high_resolution_clock
#include <sys/types.h> // for pid_t
#include <thread>      // for thread, thread::id


module profiler:utils;


namespace profilerUtil {
    using namespace std::chrono;
    using Clock = high_resolution_clock;

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
