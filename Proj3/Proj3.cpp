#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

#include "computation.h"

int main() {
    using clock = std::chrono::steady_clock;

    std::osyncstream(std::cout) << "Computation started.\n";
    const auto start = clock::now();

    {
        std::vector<std::jthread> threads;
        threads.reserve(nt);
        for (int id = 0; id < nt; ++id) {
            threads.emplace_back(worker, id);
        }
        for (auto& t : threads) {
            t.join();
        }
    }

    const std::chrono::duration<double> elapsed = clock::now() - start;
    std::osyncstream(std::cout) << "Computation finished. Elapsed time: "
        << elapsed.count() << " seconds.\n";
}
