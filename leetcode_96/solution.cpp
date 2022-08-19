class Solution {

    int table[20];

public:

    Solution() {
        table[0] = 1; table[1] = 1;
        table[2] = 2; table[3] = 5;
        for (int i = 4; i < 20; i++)
            table[i] = 0;
    }

    int numTrees(int n) {
        if (table[n] != 0) return table[n];
        int res = 0;
        for (int i = 1; i <= n; i++)
            res += numTrees(i - 1) * numTrees(n - i);
        return res;
    }
};