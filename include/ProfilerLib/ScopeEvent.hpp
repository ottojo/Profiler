/**
 * @file ScopeEvent.hpp.h
 * @author ottojo
 * @date 1/23/21
 */

#ifndef PROFILER_SCOPEEVENT_HPP
#define PROFILER_SCOPEEVENT_HPP

#include <string> // for string
class Profiler;

/**
 * RAII class for timing the duration of the ScopeEvent's lifetime (usually the containing scope)
 */
class ScopeEvent {
  public:
    /**
     * Creates a duration start event
     */
    ScopeEvent(Profiler &profiler, std::string name);

    ScopeEvent(const ScopeEvent &other) = delete;

    ScopeEvent &operator=(const ScopeEvent &rhs) = delete;

    /**
     * Creates a duration end event
     */
    ~ScopeEvent();

  private:
    Profiler &p;
};


#endif // PROFILER_SCOPEEVENT_HPP
