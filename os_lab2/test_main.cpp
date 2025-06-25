#include "gtest/gtest.h"
#include "functions.h"
#include <vector>

TEST(ComputeMinMaxTest, BasicTest) {
    std::vector<int> arr = { 10, 3, 7, 2, 9 };
    auto result = computeMinMax(arr);
    EXPECT_EQ(result.first, 2);
    EXPECT_EQ(result.second, 10);
}

TEST(ComputeAverageTest, BasicTest) {
    std::vector<int> arr = { 1, 2, 3, 4 };
    double avg = computeAverage(arr);
    EXPECT_NEAR(avg, 2.5, 1e-6);
}

TEST(ReplaceMinMaxTest, BasicTest) {
    std::vector<int> arr = { 10, 3, 7, 2, 9 };
    auto [minVal, maxVal] = computeMinMax(arr);
    double avg = computeAverage(arr);
    auto newArr = replaceMinMaxWithAverage(arr, minVal, maxVal, avg);

    for (auto v : newArr) {
        if (v == minVal || v == maxVal)
            EXPECT_EQ(v, static_cast<int>(avg));
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
