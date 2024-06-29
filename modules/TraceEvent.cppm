/**
 * @author ottojo
 * @date 1/23/21
 */
module;


#include <boost/json.hpp>
#include <string>
#include <vector>
#include <optional>

module profiler:traceevent;

import profiler.scope;
import :utils;


export enum class TraceEventType {
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


export void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, TraceEventType const &c) {
    static const std::pair<TraceEventType, boost::json::value> m[] = {{TraceEventType::DurationBegin,    "B"},
                                                                      {TraceEventType::DurationEnd,      "E"},
                                                                      {TraceEventType::Complete,         "X"},
                                                                      {TraceEventType::Instant,          "i"},
                                                                      {TraceEventType::Counter,          "C"},
                                                                      {TraceEventType::AsyncStart,       "b"},
                                                                      {TraceEventType::AsyncInstant,     "n"},
                                                                      {TraceEventType::AsyncEnd,         "e"},
                                                                      {TraceEventType::FlowStart,        "s"},
                                                                      {TraceEventType::FlowStep,         "t"},
                                                                      {TraceEventType::FlowEnd,          "f"},
                                                                      {TraceEventType::ObjectCreated,    "N"},
                                                                      {TraceEventType::ObjectSnapshot,   "O"},
                                                                      {TraceEventType::ObjectDestroyed,  "D"},
                                                                      {TraceEventType::Metadata,         "M"},
                                                                      {TraceEventType::MemoryDumpGlobal, "V"},
                                                                      {TraceEventType::MemoryDumpLocal,  "v"},
                                                                      {TraceEventType::Mark,             "R"},
                                                                      {TraceEventType::ClockSync,        "c"},
                                                                      {TraceEventType::ContextEnter,     "("},
                                                                      {TraceEventType::ContextLeave,     ")"}};
    auto it = std::find_if(std::begin(m), std::end(m),
                           [c](const std::pair<TraceEventType, boost::json::value> &ej_pair) -> bool {
                               return ej_pair.first == c;
                           });
    jv = ((it != std::end(m)) ? it : std::begin(m))->second;
}

export struct TraceEvent {
    std::string name;
    std::string cat;
    TraceEventType ph;
    std::size_t ts = profilerUtil::micros();
    pid_t pid = profilerUtil::pid();
    std::size_t tid = profilerUtil::tidHash();
    std::optional<Scope> s;
    std::optional<std::string> id;
    std::optional<std::string> bp; // Binding point, flow events
    boost::json::object args;
};

export void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, TraceEvent const &c) {
    boost::json::object json_obj;
    json_obj["name"] = c.name;
    json_obj["cat"] = c.cat;
    json_obj["ph"] = boost::json::value_from(c.ph);
    json_obj["ts"] = c.ts;
    json_obj["pid"] = c.pid;
    json_obj["tid"] = c.tid;
    if (c.s.has_value()) {
        json_obj["s"] = boost::json::value_from(c.s.value());
    }
    if (c.id.has_value()) {
        json_obj["id"] = c.id.value();
    }
    if (c.bp.has_value()) {
        json_obj["bp"] = c.bp.value();
    }
    json_obj["args"] = c.args;
    jv = json_obj;
}
