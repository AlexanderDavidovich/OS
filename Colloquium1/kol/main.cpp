#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>
#include "factorial.h"
#include "remove_duplicates.h"
#include "linked_list.h"

void testComputeFactorials() {
    {
        int n = 5;
        std::vector<unsigned long long> expected = { 1, 2, 6, 24, 120 };
        std::vector<unsigned long long> result = computeFactorials(n);
        assert(result == expected);
    }
    {
        bool exceptionThrown = false;
        try {
            computeFactorials(0);
        }
        catch (const std::invalid_argument&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
    }
    {
        bool exceptionThrown = false;
        try {
            computeFactorials(21);
        }
        catch (const std::out_of_range&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
    }
}

void testRemoveDuplicates() {
    {
        std::vector<int> input;
        std::vector<int> result = removeDuplicates(input);
        assert(result.empty());
    }
    {
        std::vector<int> input = { 1, 2, 3, 4, 5 };
        std::vector<int> expected = input;
        std::vector<int> result = removeDuplicates(input);
        assert(result == expected);
    }
    {
        std::vector<int> input = { 1, 2, 2, 3, 1, 4, 3, 5 };
        std::vector<int> expected = { 1, 2, 3, 4, 5 };
        std::vector<int> result = removeDuplicates(input);
        assert(result == expected);
    }
}

void testReverseList() {
    {
        ListNode* head = nullptr;
        ListNode* reversed = reverseList(head);
        assert(reversed == nullptr);
    }
    {
        ListNode* head = new ListNode(42);
        ListNode* reversed = reverseList(head);
        std::vector<int> expected = { 42 };
        std::vector<int> result = listToVector(reversed);
        assert(result == expected);
        freeList(reversed);
    }
    {
        std::vector<int> values = { 1, 2, 3, 4, 5 };
        ListNode* head = createList(values);
        ListNode* reversed = reverseList(head);
        std::vector<int> expected = { 5, 4, 3, 2, 1 };
        std::vector<int> result = listToVector(reversed);
        assert(result == expected);
        freeList(reversed);
    }
}

int main() {
    try {
        setlocale(LC_ALL, "russian");
        testComputeFactorials();
        testRemoveDuplicates();
        testReverseList();
        std::cout << "Все тесты успешно пройдены." << std::endl;
        int n = 5;
        std::vector<unsigned long long> factorials = computeFactorials(n);
        std::cout << "Первые " << n << " факториалов:" << std::endl;
        for (size_t i = 0; i < factorials.size(); ++i) {
            std::cout << (i + 1) << "! = " << factorials[i] << std::endl;
        }
        std::vector<int> numbers = { 1, 2, 2, 3, 1, 4, 3, 5 };
        std::vector<int> uniqueNumbers = removeDuplicates(numbers);
        std::cout << "\nМассив без дубликатов: ";
        for (int num : uniqueNumbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        std::vector<int> listValues = { 10, 20, 30, 40, 50 };
        ListNode* listHead = createList(listValues);
        ListNode* reversedHead = reverseList(listHead);
        std::vector<int> reversedList = listToVector(reversedHead);
        std::cout << "\nРазвернутый список: ";
        for (int value : reversedList) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        freeList(reversedHead);
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
