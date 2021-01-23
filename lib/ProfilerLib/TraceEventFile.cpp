/**
 * @file TraceEventFile.cpp.c
 * @author ottojo
 * @date 1/23/21
 * Description here TODO
 */

#include "TraceEventFile.hpp"

void to_json(nlohmann::json &j, const TraceEventFile &f) {
    j = {{"traceEvents",     f.traceEvents},
         {"displayTimeUnit", f.displayTimeUnit}};
    // Additional metadata is appended to the other fields, not kept in a metadata object
    for (const auto &e: f.metaData.get<nlohmann::json::object_t>()) {
        j[e.first] = e.second;
    }
}

