/**
 * @file Profiler.cpp.cc
 * @author ottojo
 * @date 1/23/21
 * Description here TODO
 */

#include "Profiler.hpp"

#include <iostream>
#include <utility>
#include <fstream>
#include <nlohmann/json.hpp>

Profiler::Profiler(std::string name, std::filesystem::path outputPath) :
        name{std::move(name)},
        outputPath{std::move(outputPath)} {
    TraceEvent e;
    e.ph = TraceEventType::Instant;
    e.name = "Profiler " + name + " starting";
    e.s = Scope::Global;
    submitEvent(e);
}

void Profiler::submitEvent(const TraceEvent &event) {
    eventFile.traceEvents.emplace_back(event);
}

Profiler::~Profiler() {
    nlohmann::json j = eventFile;
    std::ofstream o(outputPath);
    o << std::setw(4) << j << std::endl;
}
