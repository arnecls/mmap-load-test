#pragma once

inline Timer::Timer(const std::string& aLabel)
: mLabel(aLabel)
, mStart(std::chrono::high_resolution_clock::now())
{
}

inline Timer::~Timer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - mStart);
    
    ::fprintf(::stderr, "%s took: %llu ms\n", mLabel.c_str(), duration.count());
}
