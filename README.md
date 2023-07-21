# Profiler
This is a library for collecting timing information for display in the chrome builtin trace
viewer from a C++ program. Results are collected in json files that can be loaded and visualized
on chrome://tracing.

## Integration
This library is best integrated into another CMake project as a subdirectory:

```cmake
add_subdirectory(external/Profiler)

add_executable(myProgram main.cpp)
target_link_libraries(myProgram PRIVATE profilerLib)
```
By default, only the libraries, excluding the examples and the merge-tool for combining multiple json
files is built.
To enable building the executables enable the `BUILD_EXECUTABLES` CMake option:
```bash
cmake -DBUILD_EXECUTABLES=On ..
```
Or from a parent CMake config:
```cmake
set(BUILD_EXECUTABLES ON CACHE BOOL "build executable" FORCE)
add_subdirectory(external/Profiler)
```

To get the library from GitHub directly, use:
```cmake
include(FetchContent)
FetchContent_Declare(
        profiler
        GIT_REPOSITORY https://github.com/ottojo/Profiler
        GIT_TAG main
)
FetchContent_MakeAvailable(profiler)
```

## Usage
Below is a quick overview over the essential functions. Examples are provided in the [app](app) directory. The
[first](app/example.main.cpp) example showcases multiple methods of using the library. The
[second](app/example-transform.main.cpp) example uses the library to evaluate the parallel STL algorithms.
### Profiler
Create a `Profiler` instance for every module that should create its own output file.
A utility for combining multiple such files is provided.
```c++
Profiler p("Profiler Name", "traceOutput.json");
```
The profiler automatically saves the results on destruction.

The name of the process and each thread can be set in the profiler:
```c++
p.setProcessName("Worker Process");
p.setThreadName("Threadpool thread nr. " + std::to_string(i));
```
Those functions need to be called from the corresponding thread.

### Events
There are multiple ways of submitting events to the Profiler.

#### DurationEvent
The DurationEvent allows timing of a single task after the DurationEvent is constructed:
```c++
DurationEvent event(p, "Duration Event Nr. 1");
...
event.start();
...
event.stop();
```
The `start` and `stop` functions immediately submit an event to the Profiler. After the event has stopped,
calling `start` again is possible and creates a new event with the same name. A missing `stop` event
leads to broken results.

#### ScopeEvent
The `ScopeEvent` is often a useful alternative to the `DurationEvent`. Timing automatically starts on
construction and ends on destruction. This is similar to other "RAII" types such as `std::lock_guard`.
```c++
void myFunction() {
    ScopeEvent event(p, "My Function");
    ...
}
```

#### Instant event
Events with a time, but no duration, can be directly submitted to the `Profiler`:
```c++
p.submitInstantEvent("Event A occured", Scope::Process);
```
The `Scope` can be one of `Global, Process, Thread` which impacts visualization in the viewer, `Global`
being the most visible option.

#### Counter
Counter events support tracking time series of numbers. One counter may contain multiple series of data.
Counter events are directly submitted to the `Profiler`:
```c++
p.submitCounterEvent("My Counter", {{"a", a}, {"b", b}});
```

#### Flow Events
Flow events are displayed as arrows between points in the trace viewer.
The start of a flow can be recorded using:
```c++
p.submitFlowStartEvent("FlowEventName", "FlowCategory", "flowID-1");
```
And the end of a flow:
```c++
p.submitFlowEndEvent("FlowEventName", "FlowCategory", "flowID-1");
```
Flow start and end need to have the same name, ID and category.
The trace viewer has checkboxes to show/hide specific categories.

### Merging
There may be multiple `Profiler` instances creating multiple json files during the execution of a single
program. When building with `-DBUILD_EXECUTABLES=On` a `merge` tool is built to combine those:
```bash
mkdir build
cd build
cmake -DBUILD_EXECUTABLES=On ..
cmake --build .
 ./app/profilerMerge file1.json file2.json > combined.json
```
