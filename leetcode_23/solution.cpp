#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

inline int val(ListNode* node) {
    if (node == nullptr) return INT_MAX;
    return node->val;
}

class Heap {

public:

    vector<ListNode*> nodes;

    void insert(ListNode* node) {
        // Insert a ListNode and reorganize the heap nodes.
        int idx = nodes.size();
        nodes.push_back(node);
        if (node == nullptr) return;
        while (true) {
            if (idx == 0) break;
            int pIdx = (idx-1) / 2;
            if (nodes[pIdx] != nullptr && nodes[pIdx]->val <= node->val)
                break;
            ListNode* tmp = nodes[idx];
            nodes[idx] = nodes[pIdx];
            nodes[pIdx] = tmp;
            idx = pIdx;
        }
    }

    int top() {
        // Return the value of heap top.
        if (!nodes.empty() && nodes[0] != nullptr)
            return nodes[0]->val;
        return INT_MAX;
    }

    int pop() {
        // Pop the top value and reorganize the heap nodes.
        int res = top();
        if (nodes.size() == 0) return res;
        ListNode* node = nodes[0];
        if (node == nullptr) return res;
        nodes[0] = nodes[0]->next;
        if (nodes.size() == 1) return res;
        int idx = 0, c;
        int size = nodes.size();
        while (true) {
            if (idx > (size-2) / 2) break;
            c = 2 * idx + 1;
            if (c + 1 < size) {
                if (val(nodes[c+1]) < val(nodes[c]))
                    c = c + 1;
            }
            if (val(nodes[c]) < val(nodes[idx])) {
                ListNode* tmp = nodes[idx];
                nodes[idx] = nodes[c];
                nodes[c] = tmp;
                idx = c;
            } else break;
        }
        return res;
    }
};

class Solution {

public:

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        Heap heap;
        for (ListNode* node: lists)
            heap.insert(node);
        if (heap.top() == INT_MAX) return nullptr;
        ListNode* res = new ListNode(heap.pop());
        ListNode* current = res;
        while (true) {
            int val = heap.pop();
            if (val == INT_MAX) break;
            current->next = new ListNode(val);
            current = current->next;
        }
        return res;
    }
};
