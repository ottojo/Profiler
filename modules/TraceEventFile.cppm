/**
 * @file TraceEventFile.hpp.h
 * @author ottojo
 * @date 1/23/21
 */

module;

#include <boost/json.hpp>

#include <string>            // for allocator, string
#include <vector>            // for vector


module profiler:traceeventfile;

import :traceevent;

struct TraceEventFile {
    std::vector<TraceEvent> traceEvents;
    std::string displayTimeUnit = "ms";
    std::vector<std::tuple<std::string, boost::json::value>> metaData = {
            {"producedBy", "https://github.com/ottojo/Profiler"}};
};


export void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, TraceEventFile const &f) {
    boost::json::object jo = {{"traceEvents",     boost::json::value_from(f.traceEvents)},
                              {"displayTimeUnit", f.displayTimeUnit}};
    // Additional metadata is appended to the other fields, not kept in a metadata object
    for (const auto &[k, v]: f.metaData) {
        jo[k] = v;
    }
    jv = jo;
}

