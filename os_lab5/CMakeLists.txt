cmake_minimum_required(VERSION 3.14)
project(IPCPrimeLab)

set(CMAKE_CXX_STANDARD 17)

# Подключение Google Test
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Исполняемые файлы
add_executable(lab5 lab5.cpp prime_utils.cpp)
add_executable(Simple Simple.cpp prime_utils.cpp)

# Тесты
add_executable(RunTests tests/prime_tests.cpp prime_utils.cpp)
target_link_libraries(RunTests PRIVATE gtest gtest_main pthread)