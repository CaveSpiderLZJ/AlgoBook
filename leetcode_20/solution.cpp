#include <string>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        char stack[10010];
        int head = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(' || c == '[' || c =='{')
                stack[head++] = c;
            else if (c == ')') {
                if (head <= 0) return false;
                else if (stack[head-1] != '(') return false;
                else head--;
            } else if (c == ']') {
                if (head <= 0) return false;
                else if (stack[head-1] != '[') return false;
                else head--;
            } else if (c == '}') {
                if (head <= 0) return false;
                else if (stack[head-1] != '{') return false;
                else head--;
            }
        }
        return head == 0;
    }
};