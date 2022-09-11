#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<set>
#include<unordered_map>
#include<algorithm>
using namespace std;

#define MAX 1005

vector<int> area2nodes[MAX];   // [1, m]
vector<int> node2tasks[MAX];   // [1, n]
unordered_map<int, set<int>> task2nodes;
int node2area[MAX];         // [1, n]

bool cmp(int a, int b) {
    if (node2tasks[a].size() < node2tasks[b].size()) return true;
    if (node2tasks[a].size() > node2tasks[b].size()) return false;
    return a < b;
}

int main() {
    int n, m, l, g, f, a, na, pa, paa, paar;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &l);
        area2nodes[l].push_back(i);
        node2area[i] = l;
    }
    scanf("%d", &g);
    for (int i = 0; i < g; i++) {
        scanf("%d %d %d %d %d %d", &f, &a, &na, &pa, &paa, &paar);
        for (int j = 0; j < f; j++) {
            set<int> filtered;
            if (na <= 0) {
                for (int k = 1; k <= n; k++) filtered.insert(k);
            } else filtered = set<int>(area2nodes[na].begin(), area2nodes[na].end());
            if (pa > 0 && task2nodes.find(pa) != task2nodes.end()) {
                set<int> nodes = task2nodes[pa];
                set<int> areas;
                for (int node: nodes)
                    areas.insert(node2area[node]);
                nodes.clear();
                for (int area: areas) {
                    for (int node: area2nodes[area])
                        nodes.insert(node);
                }
                set<int> erased;
                for (int node: filtered) {
                    if (nodes.find(node) == nodes.end())
                        erased.insert(node);
                }
                for (int node: erased)
                    filtered.erase(node);
            }
            set<int> filtered2 = set<int>(filtered.begin(), filtered.end());
            if (paa > 0 && task2nodes.find(paa) != task2nodes.end()) {
                set<int> nodes = task2nodes[paa];
                set<int> erased;
                for (int node: filtered2) {
                    if (nodes.find(node) != nodes.end())
                        erased.insert(node);
                }
                for (int node: erased)
                    filtered2.erase(node);
            }
            if (filtered2.size() > 0 || paar == 1)
                filtered = filtered2;
            if (filtered.size() == 0) {
                printf("0 ");
                continue;
            }
            vector<int> nodes(filtered.begin(), filtered.end());
            sort(nodes.begin(), nodes.end(), cmp);
            int node = nodes[0];
            node2tasks[node].push_back(a);
            if (task2nodes.find(a) == task2nodes.end())
                task2nodes[a] = {};
            task2nodes[a].insert(node);
            printf("%d ", node);
        }
        printf("\n");
    }
    return 0;
}