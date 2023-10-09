#pragma once
#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>

enum time_unit
{
    millis, micros, nanos
};

template <class T>
void run_with_time_measurement(
    T &&algorithm,
    time_unit unit
) {
    using clock = std::chrono::high_resolution_clock;
    using milli = std::chrono::milliseconds;
    using micro = std::chrono::microseconds;
    using nano = std::chrono::nanoseconds;
    using std::chrono::duration_cast;

    std::string str_unit;
    clock::time_point start, end;

    start = clock::now();
    algorithm();
    end = clock::now();

    uint64_t time;
    switch (unit)
    {
    case nanos:
        time = duration_cast<nano>(end - start).count();
        str_unit = "ns";
        break;
    case micros:
        time = duration_cast<micro>(end - start).count();
        str_unit = "μs";
        break;
    case millis:
        time = duration_cast<milli>(end - start).count();
        str_unit = "ms";
        break;
    }
    std::cout << "Elapsed time: " << time << str_unit << std::endl;
};