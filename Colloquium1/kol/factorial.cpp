#include "factorial.h"

std::vector<unsigned long long> computeFactorials(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Входное число должно быть натуральным (больше 0)");
    }
    if (n > 20) {
        throw std::out_of_range("Входное число слишком велико для вычисления факториалов с использованием 64-битного типа");
    }
    std::vector<unsigned long long> factorials;
    factorials.reserve(n);
    unsigned long long factorial = 1;
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
        factorials.push_back(factorial);
    }
    return factorials;
}
