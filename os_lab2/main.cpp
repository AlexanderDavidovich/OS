#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include "functions.h"

int main() {
    std::cout << "enter the size of the vector: ";
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    std::cout << "enter the elements:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::promise<std::pair<int, int>> promMinMax;
    std::future<std::pair<int, int>> futMinMax = promMinMax.get_future();

    std::promise<double> promAverage;
    std::future<double> futAverage = promAverage.get_future();

    std::thread tMinMax(minmaxThread, std::cref(arr), std::move(promMinMax));
    std::thread tAverage(averageThread, std::cref(arr), std::move(promAverage));


    tMinMax.join();
    tAverage.join();


    auto [minVal, maxVal] = futMinMax.get();
    double avg = futAverage.get();


    std::vector<int> newArr = replaceMinMaxWithAverage(arr, minVal, maxVal, avg);


    std::cout << "new vector: ";
    for (const auto& v : newArr)
        std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}
