#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 1010

int value1[MAX] = {0}, value2[MAX] = {0};   // [1, n], [1, m]
int parent1[MAX] = {0}, lchild1[MAX] = {0}, rchild1[MAX] = {0};   // [1, n]
int parent2[MAX] = {0}, lchild2[MAX] = {0}, rchild2[MAX] = {0};   // [1, m]
int edge1[MAX][3] = {0}, edge2[MAX][3] = {0};   // [1, n], [1, m]
int stack[MAX], head = 0, tail = 0;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first < b.first) return true;
    if (a.first > b.first) return false;
    if (a.second < b.second) return true;
    return false;
}

int main() {
    int n, m, sum, n1, n2;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", value1 + i);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &n1, &n2);
        if (edge1[n1][0] == 0) edge1[n1][0] = n2;
        else if (edge1[n1][1] == 0) edge1[n1][1] = n2;
        else edge1[n1][2] = n2;
        if (edge1[n2][0] == 0) edge1[n2][0] = n1;
        else if (edge1[n2][1] == 0) edge1[n2][1] = n1;
        else edge1[n2][2] = n1;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", value2 + i);
    for (int i = 0; i < m - 1; i++) {
        scanf("%d %d", &n1, &n2);
        if (edge2[n1][0] == 0) edge2[n1][0] = n2;
        else if (edge2[n1][1] == 0) edge2[n1][1] = n2;
        else edge2[n1][2] = n2;
        if (edge2[n2][0] == 0) edge2[n2][0] = n1;
        else if (edge2[n2][1] == 0) edge2[n2][1] = n1;
        else edge2[n2][2] = n1;
    }
    scanf("%d", &sum);
    stack[tail++] = 1;
    while (head != tail) {
        int current = stack[head++];
        for (int j = 0; j < 3; j++) {
            int next = edge1[current][j];
            if (next > 0 && next != parent1[current]) {
                if (lchild1[current] == 0) lchild1[current] = next;
                else rchild1[current] = next;
                parent1[next] = current;
                stack[tail++] = next;
            }   
        }
    }
    head = 0; tail = 0;
    stack[tail++] = 1;
    while (head != tail) {
        int current = stack[head++];
        for (int j = 0; j < 3; j++) {
            int next = edge2[current][j];
            if (next > 0 && next != parent2[current]) {
                if (lchild2[current] == 0) lchild2[current] = next;
                else rchild2[current] = next;
                parent2[next] = current;
                stack[tail++] = next;
            }   
        }
    }
    vector<pair<int, int>> res;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (value1[i] + value2[j] != sum) continue;
            if (lchild1[i] != 0 && rchild1[i] != 0
                && lchild2[j] != 0 && rchild2[j] != 0)
                res.push_back({i, j});
        }
    }
    sort(res.begin(), res.end(), cmp);
    if (res.size() > 0) {
        for (pair<int, int> item: res)
            printf("%d %d\n", item.first, item.second);
    } else printf("-1\n");
    return 0;
}