/**
 * @file DurationEvent.hpp.h
 * @author ottojo
 * @date 1/23/21
 */

#ifndef PROFILER_DURATIONEVENT_HPP
#define PROFILER_DURATIONEVENT_HPP

#include <string> // for string
class Profiler;

/**
 * Class for manually creating duration events.
 * See also ScopeEvent
 */
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

#endif // PROFILER_DURATIONEVENT_HPP
