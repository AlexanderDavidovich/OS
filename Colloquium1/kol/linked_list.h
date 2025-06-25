#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x);
};

ListNode* reverseList(ListNode* head);
ListNode* createList(const std::vector<int>& values);
std::vector<int> listToVector(ListNode* head);
void freeList(ListNode* head);

#endif // LINKED_LIST_H
