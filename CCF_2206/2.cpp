#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define N_MAX 1005
#define S_MAX 55

int main() {
    int n, L, S, x, y;
    set<pair<int, int>> trees;
    int map[S_MAX][S_MAX];
    scanf("%d %d %d", &n, &L, &S);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        trees.insert({x, y});
    }
    for(int i = 0; i <= S; i++) {
        for (int j = 0; j <= S; j++) {
            scanf("%d", &map[S-i][j]);
        }
    }
    int cnt = 0;
    for (pair<int, int> tree: trees) {
        if (tree.first > L-S || tree.second > L-S)
            continue;
        bool match = true;
        for (int i = 0; i <= S; i++) {
            for (int j = 0; j <= S; j++) {
                if (((map[i][j] == 0) && (trees.find({i+tree.first,
                    j+tree.second}) != trees.end())) ||
                    ((map[i][j] != 0) && (trees.find({i+tree.first,
                    j+tree.second}) == trees.end()))) {
                        match = false;
                        break;    
                    }
            }
            if (!match) break;
        }
        if (match) cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}