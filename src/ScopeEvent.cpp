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
    TraceEvent e;
    e.ph = TraceEventType::DurationBegin;
    e.name = std::move(name);
    p.submitEvent(e);
}

ScopeEvent::~ScopeEvent() {
    TraceEvent e;
    e.ph = TraceEventType::DurationEnd;
    p.submitEvent(e);
}
