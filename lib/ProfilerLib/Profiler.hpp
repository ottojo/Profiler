/**
 * @file Profiler.hpp.h
 * @author ottojo
 * @date 1/23/21
 * Description here TODO
 */

#ifndef PROFILER_PROFILER_HPP
#define PROFILER_PROFILER_HPP

#include <string>
#include <filesystem>
#include <vector>

#include "TraceEvent.hpp"
#include "TraceEventFile.hpp"

class Profiler {
    public:
        Profiler(std::string name, std::filesystem::path outputPath);
        void submitEvent(const TraceEvent &event);
        ~Profiler();
    private:
        std::string name;
        std::filesystem::path outputPath;
        TraceEventFile eventFile;
};

#endif //PROFILER_PROFILER_HPP
