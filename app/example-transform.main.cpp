#include <ProfilerLib/Profiler.hpp>   // for Profiler
#include <ProfilerLib/ScopeEvent.hpp> // for ScopeEvent
#include <algorithm>                  // for transform
#include <execution>
#include <numeric> // for iota
#include <vector>  // for vector, allocator
/**
 * This example demonstrates using the profiler to compare different execution policies
 * for std::transform where the duration of each calculation is dependent on the input.
 */
int main() {
    constexpr auto size = 1000;

    Profiler p("profiler", "trace-transform.json");
    p.setProcessName("Example: std::transform");
    p.setThreadName("main thread");

    ScopeEvent mainScope(p, "int main()");

    auto calculate = [&p](auto v) {
        ScopeEvent e(p, "calculate");
        decltype(v) res = 1;
        for (int i = 0; i < 1000 * v; i++) {
            res *= v;
        }
        return res;
    };

    std::vector<double> v(size);
    {
        ScopeEvent i(p, "initializing");
        std::iota(v.begin(), v.end(), 0);
    }

    std::vector<double> res(size);
    {
        ScopeEvent t(p, "std::transform");
        std::transform(v.begin(), v.end(), res.begin(), calculate);
    }

    {
        ScopeEvent t(p, "std::transform seq");
        std::transform(std::execution::seq, v.begin(), v.end(), res.begin(), calculate);
    }

    {
        ScopeEvent t(p, "std::transform unseq");
        std::transform(std::execution::unseq, v.begin(), v.end(), res.begin(), calculate);
    }

    {
        ScopeEvent t(p, "std::transform par");
        std::transform(std::execution::par, v.begin(), v.end(), res.begin(), calculate);
    }

    {
        ScopeEvent t(p, "std::transform par_unseq");
        std::transform(std::execution::par_unseq, v.begin(), v.end(), res.begin(), calculate);
    }
}
