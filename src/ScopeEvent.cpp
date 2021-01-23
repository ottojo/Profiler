/**
 * @file ScopeEvent.cpp.cc
 * @author ottojo
 * @date 1/23/21
 * Description here TODO
 */

#include "ProfilerLib/ProfilerUtil.hpp"
#include "ProfilerLib/ScopeEvent.hpp"
#include <utility>

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
