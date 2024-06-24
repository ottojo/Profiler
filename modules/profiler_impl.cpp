module;

#include <string>
#include <filesystem>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <optional>
#include <simdjson.h>

module profiler;

Profiler::Profiler(std::string name, std::filesystem::path outputPath) : backend{name, outputPath} {
    submitInstantEvent("Profiler \"" + this->backend.name + "\" starting", Scope::Global);
}

ProfilerBackend::ProfilerBackend(std::string name,
                                 std::filesystem::path outputPath) : name{std::move(name)},
                                                                     outputPath{std::move(outputPath)},
                                                                     eventFile{std::make_unique<TraceEventFile>()} {

}

void ProfilerBackend::submitEvent(const TraceEvent &event) {
    std::lock_guard<std::mutex> lock(eventListMutex);
    auto e = event;
    eventFile->traceEvents.emplace_back(e);
}


Profiler::~Profiler() {
    backend.save();
}

void Profiler::setProcessName(const std::string &processName) {

    TraceEvent e;
    e.ph = TraceEventType::Metadata;
    e.name = "process_name";
    //e.args["name"] = processName;
    backend.submitEvent(e);

}

void Profiler::setThreadName(const std::string &threadName) {

    TraceEvent e;
    e.ph = TraceEventType::Metadata;
    e.name = "thread_name";
    //e.args["name"] = threadName;
    backend.submitEvent(e);

}

void Profiler::submitInstantEvent(const std::string &eventName, Scope scope) {
    TraceEvent e;
    e.ph = TraceEventType::Instant;
    e.s = scope;
    e.name = eventName;
    backend.submitEvent(e);
}

void Profiler::submitCounterEvent(const std::string &counterName, const std::map<std::string, int> &data) {
    TraceEvent e;
    e.ph = TraceEventType::Counter;
    e.name = counterName;
    //e.args = data;
    backend.submitEvent(e);
}

void Profiler::submitFlowStartEvent(const std::string &eventName, const std::string &category, const std::string &id) {
    TraceEvent e;
    e.ph = TraceEventType::FlowStart;
    e.cat = category;
    e.id = id;
    e.name = eventName;
    backend.submitEvent(e);
}

void Profiler::submitFlowEndEvent(const std::string &eventName, const std::string &category, const std::string &id) {
    TraceEvent e;
    e.ph = TraceEventType::FlowEnd;
    e.cat = category;
    e.id = id;
    e.name = eventName;
    e.bp = "e"; // Associate with encapsulating slice
    backend.submitEvent(e);
}

void ProfilerBackend::save() {
    std::cout << "Profiler \"" << name << "\" saving data to " << outputPath << std::endl;

    for (const TraceEvent &event: eventFile->traceEvents) {
        std::cout << event.ts << std::endl;
    }

    /*  nlohmann::json j = *eventFile;
      std::ofstream o(outputPath);
      o << std::setw(4) << j << std::endl;*/
}
