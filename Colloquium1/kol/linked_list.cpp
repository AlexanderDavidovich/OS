#include "linked_list.h"

ListNode::ListNode(int x) : val(x), next(nullptr) {}

ListNode* reverseList(ListNode* head) {
    if (!head || !head->next)
        return head;
    ListNode* newHead = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

ListNode* createList(const std::vector<int>& values) {
    if (values.empty())
        return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

std::vector<int> listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* current = head;
    while (current) {
        result.push_back(current->val);
        current = current->next;
    }
    return result;
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}
