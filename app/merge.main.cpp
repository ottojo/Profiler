/**
 * @file merge.main.cpp.c
 * @author ottojo
 * @date 1/23/21
 * Tool to merge the trace events of multiple files
 */

#include <cstdlib> // for exit
#include <fstream>
#include <iomanip>           // for operator<<, setw
#include <iostream>          // for char_traits, operator<<, basic_ostream
#include <nlohmann/json.hpp> // for basic_json<>::array_t, json, basic_json...

int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << "<file1> <file2> [ ... <fileN>] > output.json" << std::endl;
        std::exit(1);
    }

    std::ifstream i1(argv[1]);
    nlohmann::json j1;
    i1 >> j1;

    for (int i = 2; i < argc; i++) {
        std::ifstream i2(argv[i]);
        nlohmann::json j2;
        i2 >> j2;

        for (const auto &event : j2.at("traceEvents").get<nlohmann::json::array_t>()) {
            j1.at("traceEvents").emplace_back(event);
        }
    }
    std::cout << std::setw(4) << j1 << std::endl;
}
