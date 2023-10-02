#pragma once
#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>

enum time_unit
{
    millis, micros, nanos
};

/**
 * Запуск с измерением времени
 */
template <class T>
void run_with_time_measurement(
    T &&algorithm,
    time_unit unit
) {
    using namespace std::chrono;

    std::string str_unit;
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;

    start = high_resolution_clock::now();
    algorithm();
    end = high_resolution_clock::now();

    uint64_t time;
    switch (unit)
    {
    case nanos:
        time = duration_cast<nanoseconds>(end - start).count();
        str_unit = "ns";
        break;
    case micros:
        time = duration_cast<microseconds>(end - start).count();
        str_unit = "μs";
        break;
    case millis:
        time = duration_cast<milliseconds>(end - start).count();
        str_unit = "ms";
        break;
    }
    std::cout << "Elapsed time: " << time << str_unit << std::endl;
};