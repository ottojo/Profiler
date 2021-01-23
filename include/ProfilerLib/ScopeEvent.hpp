/**
 * @file ScopeEvent.hpp.h
 * @author ottojo
 * @date 1/23/21
 * Description here TODO
 */

#ifndef PROFILER_SCOPEEVENT_HPP
#define PROFILER_SCOPEEVENT_HPP

#include "Profiler.hpp"

class ScopeEvent {
    public:
        ScopeEvent(Profiler &profiler, std::string name);

        ScopeEvent(const ScopeEvent &other) = delete;

        ScopeEvent &operator=(const ScopeEvent &rhs) = delete;

        ~ScopeEvent();

    private:
        Profiler &p;
};


#endif //PROFILER_SCOPEEVENT_HPP
