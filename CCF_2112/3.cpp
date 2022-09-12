#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

#define MOD 929

int type(char c) {
    if ('A' <= c && c <= 'Z') return 0;
    if ('a' <= c && c <= 'z') return 1;
    return 2;
}

int code(char c) {
    if (type(c) == 0) return c - 'A';
    if (type(c) == 1) return c - 'a';
    return c - '0';
}

vector<int> g(int k) {
    vector<int> res = {1};
    int p = 1;
    for (int i = 1; i <= k; i++) {
        p = (p * 3) % MOD;
        res.push_back(0);
        for (int j = i; j >= 1; j--)
            res[j] = (res[j] - res[j-1] * p) % MOD;
    }
    return res;
}

vector<int> mod(vector<int> a, vector<int> b) {
    // return r = a % b s.t. a = b * c - r
    int base = 0, bsize = b.size();
    while (a.size() - base >= b.size()) {
        int r = a[base];
        for (int i = 1; i < bsize; i++)
            a[base+i] = (a[base+i] - b[i]*r) % MOD;
        base++;
    }
    vector<int> res(bsize - 1);
    for (int i = 0; i < res.size(); i++)
        res[i] = ((-a[base+i]) % MOD + MOD) % MOD;
    return res;
}

int main() {
    int w, s, k, mode = 0;
    string word;
    cin >> w >> s >> word;
    vector<int> nums = {}, data = {0};
    for (char c: word) {
        int t = type(c);
        if (mode == 0) {
            if (t == 1) nums.push_back(27);
            else if (t == 2) nums.push_back(28);
        } else if (mode == 1) {
            if (t == 0) {
                nums.push_back(28);
                nums.push_back(28);
            } else if (t == 2) nums.push_back(28);
        } else if (mode == 2) {
            if (t == 0) nums.push_back(28);
            else if (t == 1) nums.push_back(27);
        }
        mode = t;
        nums.push_back(code(c));
    }
    if ((nums.size()&1) != 0) nums.push_back(29);
    for (int i = 0; i < nums.size(); i += 2)
        data.push_back(30*nums[i] + nums[i+1]);
    if (s == -1) k = 0;
    else k = (int) pow(2, s+1);
    while ((data.size() + k) % w != 0)
        data.push_back(900);
    data[0] = data.size();
    if (k > 0) {
        for (int i = 0; i < k; i++)
        data.push_back(0);
        vector<int> res = mod(data, g(k));
        for (int i = 0; i < k; i++)
            data[data.size()-k+i] = res[i];
    }
    for (int d: data) cout << d << endl;
    return 0;
}