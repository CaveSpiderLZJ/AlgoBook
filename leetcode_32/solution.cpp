#include <string>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int res = 0;
        int size = s.size();
        int head = 0;
        for (int i = 0; i < size; i++) {
            if (res >= size - i) break;
            head = 0;
            bool breaked = false;
            int j;
            for (j = i; j < size; j++) {
                if (head == 0 && j - i > res)
                    res = j - i;
                char c = s[j];
                if (c == '(') head++;
                else {
                    if (head <= 0) {
                        if (j - i > res) res = j - i;
                        breaked = true;
                        break;
                    } else head--;
                }
            }
            if (!breaked && head == 0 && size - i > res)
                res = size - i;
        }
        return res;
    }
};