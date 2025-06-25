#include <gtest/gtest.h>
#include "prime_utils.h"

// Тесты для isPrime()
TEST(PrimeTest, NonPrimeNumbers) {
    EXPECT_FALSE(isPrime(0));
    EXPECT_FALSE(isPrime(1));
    EXPECT_FALSE(isPrime(4));
    EXPECT_FALSE(isPrime(9));
    EXPECT_FALSE(isPrime(15));
    EXPECT_FALSE(isPrime(27));
}

TEST(PrimeTest, SmallPrimes) {
    EXPECT_TRUE(isPrime(2));
    EXPECT_TRUE(isPrime(3));
    EXPECT_TRUE(isPrime(5));
    EXPECT_TRUE(isPrime(7));
    EXPECT_TRUE(isPrime(11));
    EXPECT_TRUE(isPrime(13));
}

TEST(PrimeTest, LargePrimes) {
    EXPECT_TRUE(isPrime(7919));     // 1000-е простое число
    EXPECT_TRUE(isPrime(104729));   // 10000-е простое число
}

TEST(PrimeTest, NegativeNumbers) {
    EXPECT_FALSE(isPrime(-1));
    EXPECT_FALSE(isPrime(-2));
    EXPECT_FALSE(isPrime(-5));
    EXPECT_FALSE(isPrime(-1000));
}

// Тесты для generatePrimes()
TEST(GeneratePrimesTest, FirstFewPrimes) {
    std::vector<__int32> expected = { 2, 3, 5, 7, 11, 13 };
    EXPECT_EQ(generatePrimes(6), expected);
}

TEST(GeneratePrimesTest, SinglePrime) {
    std::vector<__int32> expected = { 2 };
    EXPECT_EQ(generatePrimes(1), expected);
}

TEST(GeneratePrimesTest, ZeroPrimes) {
    std::vector<__int32> expected = {};
    EXPECT_EQ(generatePrimes(0), expected);
}

TEST(GeneratePrimesTest, ManyPrimes) {
    std::vector<__int32> result = generatePrimes(1000);
    EXPECT_EQ(result.size(), 1000);
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_TRUE(isPrime(result[i]));
    }
}