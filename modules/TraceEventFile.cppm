/**
 * @file TraceEventFile.hpp.h
 * @author ottojo
 * @date 1/23/21
 */

module;

#include <simdjson.h>

//#include <nlohmann/json.hpp> // for json_ref, json
#include <string>            // for allocator, string
#include <vector>            // for vector


module profiler:traceeventfile;

import :traceevent;

struct TraceEventFile {
    std::vector<TraceEvent> traceEvents;
    std::string displayTimeUnit = "ms";
    //nlohmann::json metaData = {{"producedBy", "https://github.com/ottojo/Profiler"}};
};

/*
void to_json(nlohmann::json &j, const TraceEventFile &f) {
    j = {{"traceEvents", f.traceEvents}, {"displayTimeUnit", f.displayTimeUnit}};
    // Additional metadata is appended to the other fields, not kept in a metadata object
    for (const auto &e : f.metaData.get<nlohmann::json::object_t>()) {
        j[e.first] = e.second;
    }
}
 */
