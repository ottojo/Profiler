/**
 * @file TraceEvent.hpp.h
 * @author ottojo
 * @date 1/23/21
 */

#ifndef PROFILER_TRACEEVENT_HPP
#define PROFILER_TRACEEVENT_HPP

#include <ProfilerLib/Scope.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "OptionalSerialization.hpp"
#include "ProfilerUtil.hpp"

NLOHMANN_JSON_SERIALIZE_ENUM(Scope, {{Scope::Global, "g"}, {Scope::Process, "p"}, {Scope::Thread, "t"}})

enum class TraceEventType {
    DurationBegin,
    DurationEnd,
    Complete,
    Instant,
    Counter,
    AsyncStart,
    AsyncInstant,
    AsyncEnd,
    FlowStart,
    FlowStep,
    FlowEnd,
    Sample,
    ObjectCreated,
    ObjectSnapshot,
    ObjectDestroyed,
    Metadata,
    MemoryDumpGlobal,
    MemoryDumpLocal,
    Mark,
    ClockSync,
    ContextEnter,
    ContextLeave
};

NLOHMANN_JSON_SERIALIZE_ENUM(TraceEventType,
                             {{TraceEventType::DurationBegin, "B"},   {TraceEventType::DurationEnd, "E"},
                              {TraceEventType::Complete, "X"},        {TraceEventType::Instant, "i"},
                              {TraceEventType::Counter, "C"},         {TraceEventType::AsyncStart, "b"},
                              {TraceEventType::AsyncInstant, "n"},    {TraceEventType::AsyncEnd, "e"},
                              {TraceEventType::FlowStart, "s"},       {TraceEventType::FlowStep, "t"},
                              {TraceEventType::FlowEnd, "f"},         {TraceEventType::ObjectCreated, "N"},
                              {TraceEventType::ObjectSnapshot, "O"},  {TraceEventType::ObjectDestroyed, "D"},
                              {TraceEventType::Metadata, "M"},        {TraceEventType::MemoryDumpGlobal, "V"},
                              {TraceEventType::MemoryDumpLocal, "v"}, {TraceEventType::Mark, "R"},
                              {TraceEventType::ClockSync, "c"},       {TraceEventType::ContextEnter, "("},
                              {TraceEventType::ContextLeave, ")"}})

struct TraceEvent {
    std::string name;
    std::string cat;
    TraceEventType ph;
    std::size_t ts = profilerUtil::micros();
    pid_t pid = profilerUtil::pid();
    std::size_t tid = profilerUtil::tidHash();
    std::optional<Scope> s;
    std::optional<std::string> id;
    std::optional<std::string> bp; // Binding point, flow events
    nlohmann::json args;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TraceEvent, name, cat, ph, ts, pid, tid, s, id, bp, args)
};

#endif // PROFILER_TRACEEVENT_HPP
