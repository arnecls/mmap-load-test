#pragma once

#include <chrono>
#include <string>

class Timer {
private:
    std::string mLabel;
    std::chrono::high_resolution_clock::time_point mStart;
    
public:
    inline Timer(const std::string& aLabel);
    inline ~Timer();
};

#include "timer.hpp"
