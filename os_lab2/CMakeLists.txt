cmake_minimum_required(VERSION 3.10)
project(Lab2Threads)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab2Threads main.cpp functions.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(UnitTests test_main.cpp functions.cpp)
target_link_libraries(UnitTests gtest_main)

include(GoogleTest)
gtest_discover_tests(UnitTests)
