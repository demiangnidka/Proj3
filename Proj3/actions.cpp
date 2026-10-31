#include "actions.h"

#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

void f(char set, int i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::osyncstream(std::cout) << "Action " << i << " of set " << set << " completed.\n";
}
