/**
 * @file Profiler.cpp.cc
 * @author ottojo
 * @date 1/23/21
 */

#include "ProfilerLib/Profiler.hpp"

#include <fstream>
#include <iomanip>           // for operator<<, setw
#include <iostream>          // for basic_ostream, operator<<, endl
#include <nlohmann/json.hpp> // for basic_json<>::object_t, json, opera...
#include <utility>           // for move

#include "ProfilerLib/Scope.hpp" // for Scope, Scope::Global
#include "TraceEvent.hpp"        // for TraceEvent, TraceEventType, TraceEv...
#include "TraceEventFile.hpp"    // for TraceEventFile, to_json

Profiler::Profiler(std::string name, std::filesystem::path outputPath) :
    name{std::move(name)},
    outputPath{std::move(outputPath)},
    eventFile{std::make_unique<TraceEventFile>()} {
    submitInstantEvent("Profiler \"" + this->name + "\" starting", Scope::Global);
}

void Profiler::submitEvent(const TraceEvent &event) {
    std::lock_guard<std::mutex> lock(eventListMutex);
    auto e = event;
    eventFile->traceEvents.emplace_back(e);
}

Profiler::~Profiler() {
    if (this->enabled) {
        save();
    }
}

void Profiler::setProcessName(const std::string &processName) {
    TraceEvent e;
    e.ph = TraceEventType::Metadata;
    e.name = "process_name";
    e.args["name"] = processName;
    submitEvent(e);
}

void Profiler::setThreadName(const std::string &threadName) {
    TraceEvent e;
    e.ph = TraceEventType::Metadata;
    e.name = "thread_name";
    e.args["name"] = threadName;
    submitEvent(e);
}

void Profiler::submitInstantEvent(const std::string &eventName, Scope scope) {
    if (!this->enabled) {
        return;
    }

    TraceEvent e;
    e.ph = TraceEventType::Instant;
    e.s = scope;
    e.name = eventName;
    submitEvent(e);
}

void Profiler::submitCounterEvent(const std::string &counterName, const std::map<std::string, int> &data) {
    if (!this->enabled) {
        return;
    }

    TraceEvent e;
    e.ph = TraceEventType::Counter;
    e.name = counterName;
    e.args = data;
    submitEvent(e);
}

void Profiler::submitFlowStartEvent(const std::string &eventName, const std::string &category, const std::string &id) {
    if (!this->enabled) {
        return;
    }

    TraceEvent e;
    e.ph = TraceEventType::FlowStart;
    e.cat = category;
    e.id = id;
    e.name = eventName;
    submitEvent(e);
}

void Profiler::submitFlowEndEvent(const std::string &eventName, const std::string &category, const std::string &id) {
    if (!this->enabled) {
        return;
    }

    TraceEvent e;
    e.ph = TraceEventType::FlowEnd;
    e.cat = category;
    e.id = id;
    e.name = eventName;
    e.bp = "e"; // Associate with encapsulating slice
    submitEvent(e);
}

void Profiler::save() {
    std::cout << "Profiler \"" << name << "\" saving data to " << outputPath << std::endl;
    nlohmann::json j = *eventFile;
    std::ofstream o(outputPath);
    o << std::setw(4) << j << std::endl;
}

void Profiler::disable() {
    this->enabled = false;
}

[[nodiscard]] bool Profiler::isEnabled() const {
    return enabled;
};
