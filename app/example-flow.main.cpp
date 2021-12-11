/**
 * @file example-flow.main.cpp
 * @author ottojo
 * @date 12/11/21
 * @brief Example for using flow events
 */

#include <thread>
#include <ProfilerLib/Profiler.hpp>
#include <ProfilerLib/ScopeEvent.hpp>

using namespace std;
using namespace chrono_literals;

Profiler p{"Flow Example", "flow.json"};

void t1Func() {
    ScopeEvent t1e(p, "t1Func()");
    p.setThreadName("t1");
    {
        ScopeEvent e(p, "part 1");
        p.submitFlowStartEvent("t1 -> t2", "exampleCategory", "1");
        this_thread::sleep_for(5ms);
        p.submitFlowStartEvent("t1 -> t2", "exampleCategory", "2");
        this_thread::sleep_for(10ms);
    }
    this_thread::sleep_for(20ms);
    {
        ScopeEvent e(p, "part 2");
        this_thread::sleep_for(3ms);
        p.submitFlowEndEvent("t2 -> t1", "exampleCategory", "1");
        this_thread::sleep_for(5ms);
        p.submitFlowEndEvent("t2 -> t1", "exampleCategory", "2");
        this_thread::sleep_for(10ms);
    }
}

void t2Func() {
    ScopeEvent t2e(p, "t2Func()");
    p.setThreadName("t2");
    this_thread::sleep_for(5ms);
    {
        ScopeEvent e(p, "part 1");
        p.submitFlowEndEvent("t1 -> t2", "exampleCategory", "1");
        this_thread::sleep_for(7ms);
        p.submitFlowEndEvent("t1 -> t2", "exampleCategory", "2");
        this_thread::sleep_for(10ms);
    }
    this_thread::sleep_for(10ms);
    {
        ScopeEvent e(p, "part 2");
        p.submitFlowStartEvent("t2 -> t1", "exampleCategory", "1");
        this_thread::sleep_for(5ms);
        p.submitFlowStartEvent("t2 -> t1", "exampleCategory", "2");
        this_thread::sleep_for(10ms);
    }
}

int main() {
    p.setProcessName("Flow Example");
    p.setThreadName("main thread");
    ScopeEvent event(p, "main()");
    jthread t1(t1Func);
    jthread t2(t2Func);
}
