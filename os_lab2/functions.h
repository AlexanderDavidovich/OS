#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <utility>
#include <future>

std::pair<int, int> computeMinMax(const std::vector<int>& arr);
double computeAverage(const std::vector<int>& arr);
std::vector<int> replaceMinMaxWithAverage(const std::vector<int>& arr, int minVal, int maxVal, double avg);

void minmaxThread(const std::vector<int>& arr, std::promise<std::pair<int, int>> prom);
void averageThread(const std::vector<int>& arr, std::promise<double> prom);

#endif // FUNCTIONS_H
