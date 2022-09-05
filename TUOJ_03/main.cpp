#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 205
#define IMAX 2147483647

int n, m;
int nodes[MAX][MAX];
int hedges[MAX][MAX];
int vedges[MAX][MAX];
int dis[MAX][MAX];
int idx[MAX][MAX];
bool s[MAX][MAX];

class Building {
    // a power station or a factory
public:
    int i, j, v;
    Building(int _i, int _j, int _v): i(_i), j(_j), v(_v) {}
};

class PriorityQueue {
public:
    int size;
    pair<int, int> nodes[MAX * MAX];

    PriorityQueue(): size(0) {}

    void up(int x) {
        while (x > 0) {
            int p = (x - 1) / 2;
            pair<int, int> pnode = nodes[p];
            pair<int, int> node = nodes[x];
            if (dis[node.first][node.second] < dis[pnode.first][pnode.second]) {
                nodes[x] = pnode;
                idx[pnode.first][pnode.second] = x;
                nodes[p] = node;
                idx[node.first][node.second] = p;
                x = p;
            } else break;
        }
    }

    void down(int x) {
        while (x+x+1 < size) {  // have a child
            int child = x+x+1;
            pair<int, int> node = nodes[x+x+1];
            if (x+x+2 < size) { // have right child
                pair<int, int> node2 = nodes[x+x+2];
                if (dis[node2.first][node2.second] < dis[node.first][node.second]) {
                    child += 1;
                    node = node2;
                }
            }
            pair<int, int> pnode = nodes[x];
            if (dis[node.first][node.second] < dis[pnode.first][pnode.second]) {
                nodes[x] = node;
                idx[node.first][node.second] = x;
                nodes[child] = pnode;
                idx[pnode.first][pnode.second] = child;
                x = child;
            } else break;
        }
    }

    pair<int, int> top() { return nodes[0]; } 

    void push(pair<int, int> node) {
        nodes[size++] = node;
        idx[node.first][node.second] = size - 1;
        up(size - 1);
    }

    pair<int, int> pop() {
        pair<int, int> res = top();
        pair<int, int> last = nodes[--size];
        nodes[0] = last;
        idx[last.first][last.second] = 0;
        down(0);
        return res;
    }
};

int minDis(Building factory, Building station) {
    // search the min distance between a factory and a station
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dis[i][j] = IMAX;
            s[i][j] = false;
        }
    }
    dis[factory.i][factory.j] = 0;
    PriorityQueue queue;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            queue.push({i, j});
        }
    }
    int res = 0;
    while (true) {
        if (queue.size <= 0) break;
        pair<int, int> node = queue.pop();
        int x = node.first, y = node.second;
        if (x == station.i && y == station.j) {
            res = dis[x][y] + station.v;
            break;
        }
        s[x][y] = true;
        if (x < n-1 && !s[x+1][y]) {
            dis[x+1][y] = min(dis[x+1][y], dis[x][y] + vedges[x][y]);
            queue.up(idx[x+1][y]);
        }
        if (x > 0 && !s[x-1][y]) {
            dis[x-1][y] = min(dis[x-1][y], dis[x][y] + vedges[x-1][y]);
            queue.up(idx[x-1][y]);
        }
        if (y < m-1 && !s[x][y+1]) {
            dis[x][y+1] = min(dis[x][y+1], dis[x][y] + hedges[x][y]);
            queue.up(idx[x][y+1]);
        }
        if (y > 0 && !s[x][y-1]) {
            dis[x][y-1] = min(dis[x][y-1], dis[x][y] + hedges[x][y-1]);
            queue.up(idx[x][y-1]);
        }
    }
    return res;
}

int main() {
    vector<Building> stations;
    vector<Building> factories;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &nodes[i][j]);
            if (nodes[i][j] > 0) stations.push_back(Building(i, j, nodes[i][j]));
            else if (nodes[i][j] < 0) factories.push_back(Building(i, j, nodes[i][j]));
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m-1; j++)
            scanf("%d", &hedges[i][j]);
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < m; j++)
            scanf("%d", &vedges[i][j]);
    }
    // assume factories.size() == 1
    Building factory = factories[0];
    int res = IMAX;
    for (Building station: stations) {
        int dis = minDis(factory, station);
        if (dis < res) res = dis;
    }
    printf("%d\n", res);
    return 0;
}