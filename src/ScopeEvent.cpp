/**
 * @file ScopeEvent.cpp.cc
 * @author ottojo
 * @date 1/23/21
 */

#include "ProfilerLib/ScopeEvent.hpp"

#include <utility> // for move

#include "ProfilerLib/Profiler.hpp" // for Profiler
#include "TraceEvent.hpp"           // for TraceEvent, TraceEventType, Trac...

ScopeEvent::ScopeEvent(Profiler &profiler, std::string name) : p{profiler} {
    active = p.isEnabled();
    if (!active) {
        return;
    }
    TraceEvent e;
    e.ph = TraceEventType::DurationBegin;
    e.name = p.name + ": " + std::move(name);
    p.submitEvent(e);
}

ScopeEvent::~ScopeEvent() {
    if (!active) {
        // Prevent submitting DurationEnd when the profiler was disabled at DurationBegin
        return;
    }
    TraceEvent e;
    e.ph = TraceEventType::DurationEnd;
    // Submit the event even if profiler was disabled in the meantime (only consider enabled state at start)
    p.submitEvent(e, true);
}
