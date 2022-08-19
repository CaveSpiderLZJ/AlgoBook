struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int val = l1->val + l2->val;
        ListNode* res = new ListNode(val % 10);
        ListNode* current = res;
        bool carry = val >= 10;
        l1 = l1->next; l2 = l2->next;
        while (l1 != nullptr && l2 != nullptr) {
            val = l1->val + l2->val;
            if (carry) val += 1;
            carry = val >= 10;
            current->next = new ListNode(val % 10);
            current = current->next;
            l1 = l1->next; l2 = l2->next;
        }
        while (l1 != nullptr) {
            val = l1->val;
            if (carry) val += 1;
            carry = val >= 10;
            current->next = new ListNode(val % 10);
            current = current->next;
            l1 = l1->next;
        }
        while (l2 != nullptr) {
            val = l2->val;
            if (carry) val += 1;
            carry = val >= 10;
            current->next = new ListNode(val % 10);
            current = current->next;
            l2 = l2->next;
        }
        if (carry) current->next = new ListNode(1);
        return res;
    }
};