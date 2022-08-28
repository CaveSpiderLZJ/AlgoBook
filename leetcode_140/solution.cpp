#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define W_MAX 12

class Node {
public:
    char c;
    bool valid;
    vector<Node*> children;

    Node(char _c, bool _valid) {
        c = _c;
        valid = _valid;
    }

    Node* query(char c) {
        Node* res = nullptr;
        for (Node* child: children) {
            if (child->c == c) {
                res = child;
                break;
            }
        }
        return res;
    }
};

class Trie {
public:
    Node* root;

    Trie() { root = new Node(' ', false); }

    void insert(string s) {
        Node* current = root;
        for (int i = 0; i < s.size() - 1; i++) {
            char c = s[i];
            Node* child = current->query(c);
            if (child != nullptr) {
                current = child;
            } else {
                Node* newChild = new Node(c, false);
                current->children.push_back(newChild);
                current = newChild;
            }
        }
        char c = s[s.size() - 1];
        Node* child = current->query(c);
        if (child != nullptr) {
            child->valid = true;
        } else {
            Node* newChild = new Node(c, true);
            current->children.push_back(newChild);
        }
    }

    bool query(string s) {
        Node* current = root;
        bool res = true;
        for (int i = 0; i < s.size(); i++) {
            Node* child = current->query(s[i]);
            if (child == nullptr) {
                res = false;
                break;
            } else current = child;
        }
        return res && current->valid;
    }
};

class Solution {

    Trie trie;
    unordered_map<int, vector<string>> memory;

public:

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        for (string word: wordDict)
            trie.insert(word);
        if (s.size() == 0) return {};
        return search(s, wordDict);
    }

    vector<string> search(string s, vector<string>& wordDict) {
        if (s.size() == 0) return {""};
        vector<string> res;
        for (int i = 1; i <= min(W_MAX, (int)s.size()); i++) {
            string prefix = s.substr(0, i);
            if (!trie.query(prefix)) continue;
            vector<string> substrs;
            if (memory.find(s.size() - i) != memory.end()) {
                substrs = memory[s.size() - i];
            } else {
                substrs = search(s.substr(i, s.size() - i), wordDict);
                memory.insert({s.size()-i, substrs});
            }
            for (string substr: substrs) {
                if (substr == "") {
                    res.push_back(prefix);
                } else {
                    res.push_back(prefix + " " + substr);
                }
            }
        }
        return res;
    }
};

int main() {
    string s = "catsanddog";
    vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};
    Solution solution;
    vector<string> res = solution.wordBreak(s, wordDict);
    for (string str: res) {
        cout << str << endl;
    }
    return 0;
}
