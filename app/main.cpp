#include <ProfilerLib/include/ProfilerLib/DurationEvent.hpp>
#include <ProfilerLib/include/ProfilerLib/Profiler.hpp>
#include <ProfilerLib/include/ProfilerLib/ScopeEvent.hpp>
#include <future>
#include <iostream>
#include <random>
#include <thread>

std::random_device rd;
std::mt19937 gen(rd());

Profiler p("MainProfiler", "trace.json");

void importantFunction(int recurse = 5) {
    ScopeEvent e(p, "importantFunction");
    if (recurse > 0) {
        importantFunction(recurse - 1);
    }
    std::uniform_int_distribution distribution(5, 10);
    std::this_thread::sleep_for(std::chrono::milliseconds(distribution(gen)));
    static int i = 0;
    p.submitCounterEvent("some counter", {{"i", i},
                                          {"c", 0}});
    i++;
}

void asyncCalls() {
    ScopeEvent e(p, "asyncCalls");
    std::vector<std::future<void>> futures;
    futures.reserve(10);

    DurationEvent threadsStarting(p,"Starting threads");
    threadsStarting.start();

    for (int i = 0; i < 10; i++) {
        futures.emplace_back(std::async([i]() {
            ScopeEvent e(p, "lambda in asyncCalls");
            p.setThreadName("async call nr. " + std::to_string(i));
            importantFunction(0);
        }));
    }

    threadsStarting.stop();

    p.submitInstantEvent("tasks started, now waiting", Scope::Process);

    for (auto &f:futures) {
        f.wait();
    }
}

int main() {
    ScopeEvent e(p, "main function");
    p.setProcessName("TestProcess");
    p.setThreadName("main thread");
    std::cout << "Hello, World!" << std::endl;
    importantFunction();
    asyncCalls();
    return 0;
}
