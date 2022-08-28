#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define S_MAX 305
#define W_MAX 25

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
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        Trie trie;
        for (const string& word: wordDict)
            trie.insert(word);
        bool d[S_MAX]; d[0] = true;
        for (int i = 1; i <= s.size(); i++) {
            bool res = false;
            for (int j = max(0, i-W_MAX); j < i; j++) {
                if (d[j] && trie.query(s.substr(j, i-j))) {
                    res = true;
                    break;
                }
            }
            d[i] = res;
        }
        return d[s.size()];
    }
};
