#ifndef REMOVE_DUPLICATES_H
#define REMOVE_DUPLICATES_H

#include <vector>
#include <unordered_set>

template<typename T>
std::vector<T> removeDuplicates(const std::vector<T>& input) {
    std::vector<T> result;
    std::unordered_set<T> seen;
    for (const auto& elem : input) {
        if (seen.find(elem) == seen.end()) {
            result.push_back(elem);
            seen.insert(elem);
        }
    }
    return result;
}

#endif // REMOVE_DUPLICATES_H
