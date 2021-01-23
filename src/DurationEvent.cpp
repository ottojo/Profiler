/**
 * @file DurationEvent.cpp.cc
 * @author ottojo
 * @date 1/23/21
 * Description here TODO
 */

#include <ProfilerLib/DurationEvent.hpp>
#include <utility>

DurationEvent::DurationEvent(Profiler &p, std::string name) : p{p}, name{std::move(name)} {
}

void DurationEvent::start() {
    assert(not started);
    TraceEvent e;
    e.ph = TraceEventType::DurationBegin;
    e.name = name;
    p.submitEvent(e);
    started = true;
}

void DurationEvent::stop() {
    assert(started);
    TraceEvent e;
    e.ph = TraceEventType::DurationEnd;
    e.name = name;
    p.submitEvent(e);
    started = false;
}
