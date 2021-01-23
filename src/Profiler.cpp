/**
 * @file Profiler.cpp.cc
 * @author ottojo
 * @date 1/23/21
 * Description here TODO
 */

#include "ProfilerLib/Profiler.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <utility>

Profiler::Profiler(std::string name, std::filesystem::path outputPath) :
    name{std::move(name)},
    outputPath{std::move(outputPath)} {
    submitInstantEvent("Profiler " + name + " starting", Scope::Global);
}

void Profiler::submitEvent(const TraceEvent &event) {
    std::lock_guard<std::mutex> lock(eventListMutex);
    eventFile.traceEvents.emplace_back(event);
}

Profiler::~Profiler() {
    save();
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
    TraceEvent e;
    e.ph = TraceEventType::Instant;
    e.s = scope;
    e.name = eventName;
    submitEvent(e);
}

void Profiler::submitCounterEvent(const std::string &counterName, const std::map<std::string, int> &data) {
    TraceEvent e;
    e.ph = TraceEventType::Counter;
    e.name = counterName;
    e.args = data;
    submitEvent(e);
}

void Profiler::save() {
    std::cout << "Profiler saving data" << std::endl;
    nlohmann::json j = eventFile;
    std::ofstream o(outputPath);
    o << std::setw(4) << j << std::endl;
}
