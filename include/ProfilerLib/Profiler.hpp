/**
 * @file Profiler.hpp.h
 * @author ottojo
 * @date 1/23/21
 */

#ifndef PROFILER_PROFILER_HPP
#define PROFILER_PROFILER_HPP

#include <atomic>
#include <filesystem> // for path
#include <map>        // for map
#include <memory>     // for unique_ptr
#include <mutex>      // for mutex
#include <string>     // for string

#include "Scope.hpp" // for Scope

class DurationEvent;
class ScopeEvent;
struct TraceEvent;
struct TraceEventFile;

/**
 * The profiler class is responsible for collecting events and writing them to a file on destruction.
 */
class Profiler {
    // Friend classes used to hide submitEvent from user, who should use public functions of Profiler instead
    friend class ScopeEvent;
    friend class DurationEvent;

  public:
    Profiler(std::string name, std::filesystem::path outputPath);
    ~Profiler();

    /**
     * Creates a metadata event setting the name of the calling process
     */
    void setProcessName(const std::string &processName);

    /**
     * Creates a metadata event setting the name of the calling thread
     */
    void setThreadName(const std::string &threadName);

    void submitInstantEvent(const std::string &eventName, Scope scope);

    /**
     * @param counterName Name of the counter instance
     * @param data        Values of multiple series at the current time
     */
    void submitCounterEvent(const std::string &counterName, const std::map<std::string, int> &data);

    /**
     * @param eventName Name
     * @param category  Display category in web interface
     * @param id        Correlates Start and End events
     */
    void submitFlowStartEvent(const std::string &eventName, const std::string &category, const std::string &id);

    /**
     * @param eventName Name
     * @param category  Display category in web interface
     * @param id        Correlates Start and End events
     */
    void submitFlowEndEvent(const std::string &eventName, const std::string &category, const std::string &id);

    void disable();

    [[nodiscard]] bool isEnabled() const;

  private:
    void save();
    void submitEvent(const TraceEvent &event);

    std::string name;
    std::filesystem::path outputPath;
    std::unique_ptr<TraceEventFile> eventFile;
    std::mutex eventListMutex;
    std::atomic_bool enabled = true;
};

#endif // PROFILER_PROFILER_HPP
