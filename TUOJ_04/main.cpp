#include <cstdio>
#include <vector>
using namespace std;

#define MAX 100010

int m, k, u, v;
vector<int> edges[MAX];

int main() {
    scanf("%d %d", &m, &k);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    int mask[MAX];
    for (int i = 0; i <= m; i++) mask[i] = -1;
    int queue[MAX], head = 0, tail = 0;
    queue[tail++] = 0;
    mask[0] = 0;
    int depth = 0;
    while (head != tail) {
        depth++;
        int current = queue[head++];
        vector<int> vs = edges[current];
        for (int i = 0; i < vs.size(); i++) {
            v = vs[i];
            if (mask[v] >= 0 && mask[v] >= depth) {
                printf("It's not a tree!\n");
                return 0;
            }
            if (mask[v] == -1) {
                mask[v] = depth;
                queue[tail++] = v;
            }
        }
    }
    if (tail != m+1) {
        printf("It's not a tree!\n");
        return 0;
    }
    bool p1 = true, p2 = false;
    int res = 0;
    for (int i = 0; i <= m; i++) {
        int size = edges[i].size();
        if (size <= k && !p2) {
            p2 = true;
            res = i;
        }
        if (size > k + 1) p1 = false;
    }
    if (!p1 || !p2) printf("No such a node!\n");
    else printf("%d\n", res);
    return 0;
}