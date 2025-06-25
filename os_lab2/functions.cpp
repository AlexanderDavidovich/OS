#include "functions.h"
#include <iostream>
#include <chrono>
#include <thread>

std::pair<int, int> computeMinMax(const std::vector<int>& arr) {
    int minVal = arr[0];
    int maxVal = arr[0];
    for (const auto& v : arr) {
        if (v < minVal)
            minVal = v;
        if (v > maxVal)
            maxVal = v;
        std::this_thread::sleep_for(std::chrono::milliseconds(7));
    }
    return { minVal, maxVal };
}


double computeAverage(const std::vector<int>& arr) {
    double sum = 0;
    for (const auto& v : arr) {
        sum += v;
        std::this_thread::sleep_for(std::chrono::milliseconds(12));
    }
    return sum / arr.size();
}


std::vector<int> replaceMinMaxWithAverage(const std::vector<int>& arr, int minVal, int maxVal, double avg) {
    std::vector<int> result = arr;
    for (auto& v : result) {
        if (v == minVal || v == maxVal)
            v = static_cast<int>(avg);
    }
    return result;
}


void minmaxThread(const std::vector<int>& arr, std::promise<std::pair<int, int>> prom) {
    auto result = computeMinMax(arr);
    std::cout << "Min: " << result.first << ", Max: " << result.second << std::endl;
    prom.set_value(result);
}


void averageThread(const std::vector<int>& arr, std::promise<double> prom) {
    double avg = computeAverage(arr);
    std::cout << "Average: " << avg << std::endl;
    prom.set_value(avg);
}
