#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define LEN 7

class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int, int> wordMap;
        for (string word: words) {
            int key = 0, cnt = 0, mask;
            for (char c: word) {
                mask = (1 << (c-'a'));
                if ((mask|key) != key) { key |= mask; cnt++; }
                if (cnt > LEN) break;
            }
            if (cnt > LEN) continue;
            if (wordMap.find(key) == wordMap.end()) {
                wordMap.insert({key, 1});
            } else wordMap[key] += 1;
        }
        vector<int> res;
        for (string puzzle: puzzles) {
            int cnt = 0, base = (1 << (puzzle[0]-'a'));
            for (int i = 0; i < (1<<(LEN-1)); i++) {
                int key = base;
                for (int j = 0; j < LEN-1; j++)
                    if (i & (1<<j)) key += (1 << (puzzle[j+1]-'a'));
                if (wordMap.find(key) != wordMap.end())
                    cnt += wordMap[key];
            }
            res.push_back(cnt);
        }
        return res;
    }
};
