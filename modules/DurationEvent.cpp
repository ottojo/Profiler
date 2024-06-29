/**
 * @file DurationEvent.cpp.cc
 * @author ottojo
 * @date 1/23/21
 */

module;

#include <cassert> // for assert
#include <utility> // for move
#include <string>

module profiler;

DurationEvent::DurationEvent(Profiler &p, std::string name) : p{p}, name{std::move(name)} {
}

void DurationEvent::start() {
    assert(not started);
    TraceEvent e;
    e.ph = TraceEventType::DurationBegin;
    e.name = p.backend.name + ": " + name;
    p.backend.submitEvent(e);
    started = true;
}

void DurationEvent::stop() {
    assert(started);
    TraceEvent e;
    e.ph = TraceEventType::DurationEnd;
    e.name = p.backend.name + ": " + name;
    p.backend.submitEvent(e);
    started = false;
}
