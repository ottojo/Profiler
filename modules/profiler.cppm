module;

#include <filesystem>
#include <string>
#include <map>
#include <mutex>
#include <simdjson.h>

export module profiler;

import profiler.scope;

import :traceevent;
import :traceeventfile;

export class Profiler;

/**
 * RAII class for timing the duration of the ScopeEvent's lifetime (usually the containing scope)
 */
export class ScopeEvent {
public:
    /**
     * Creates a duration start event
     */
    ScopeEvent(Profiler &profiler, std::string name);

    ScopeEvent(const ScopeEvent &other) = delete;

    ScopeEvent &operator=(const ScopeEvent &rhs) = delete;

    /**
     * Creates a duration end event
     */
    ~ScopeEvent();

private:
    Profiler &p;
};


/**
 * Class for manually creating duration events.
 * See also ScopeEvent
 */
export class DurationEvent {
public:
    DurationEvent(Profiler &p, std::string name);

    void start();

    void stop();

private:
    Profiler &p;
    std::string name;
    bool started = false;
};

class ProfilerBackend {
public:

    std::string name;
    std::filesystem::path outputPath;
    std::unique_ptr<TraceEventFile> eventFile;
    std::mutex eventListMutex;

    ProfilerBackend(std::string name,
                    std::filesystem::path outputPath);

    void save();

    void submitEvent(const TraceEvent &event);
};

export class Profiler {
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

private:
    ProfilerBackend backend;
};
