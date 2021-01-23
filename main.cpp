#include <iostream>
#include <thread>
#include <random>

#include <ProfilerLib/Profiler.hpp>
#include <ProfilerLib/ScopeEvent.hpp>

std::random_device rd;
std::mt19937 gen(rd());

Profiler p("MainProfiler", "trace.json");

void importantFunction(bool recurse = true) {
    ScopeEvent e(p, "importantFunction");
    if (recurse) {
        importantFunction(false);
    }
    std::uniform_int_distribution distribution(5, 10);
    std::this_thread::sleep_for(std::chrono::milliseconds(distribution(gen)));
}

int main() {
    ScopeEvent e(p, "main");
    std::cout << "Hello, World!" << std::endl;
    importantFunction();
    return 0;
}
