/**
 * @author ottojo
 * @date 1/23/21
 */

module;


#include <utility> // for move
#include <string>
#include <simdjson.h>

module profiler;


ScopeEvent::ScopeEvent(Profiler &profiler, std::string name) : p{profiler} {
    TraceEvent e;
    e.ph = TraceEventType::DurationBegin;
    e.name = p.backend.name + ": " + std::move(name);
    p.backend.submitEvent(e);
}

ScopeEvent::~ScopeEvent() {
    TraceEvent e;
    e.ph = TraceEventType::DurationEnd;
    p.backend.submitEvent(e);
}
