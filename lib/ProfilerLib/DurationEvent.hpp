/**
 * @file DurationEvent.hpp.h
 * @author ottojo
 * @date 1/23/21
 * Description here TODO
 */

#ifndef PROFILER_DURATIONEVENT_HPP
#define PROFILER_DURATIONEVENT_HPP


#include "Profiler.hpp"

class DurationEvent {
    public:
        DurationEvent(Profiler &p, std::string name);

        void start();

        void stop();

    private:
        Profiler &p;
        std::string name;
        bool started = false;
};


#endif //PROFILER_DURATIONEVENT_HPP
