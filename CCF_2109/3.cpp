#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>
using namespace std;

#define MAX 1005
#define T_MAX 100005

int T;
double vmin = 1e38, vmax = -1e38;
int cmin = (1<<30), cmax = 0;

class Neuron {
public:
    int cnt;
    double v, u, a, b, c, d;

    Neuron() {}

    Neuron(double _v, double _u, double _a, double _b, double _c, double _d):
        v(_v), u(_u), a(_a), b(_b), c(_c), d(_d), cnt(0) {}

    bool update(double I, double dt, int t) {
        double v1 = v + dt*(0.04*v*v+5.0*v+140.0-u) + I;
        u = u + dt*a*(b*v-u);
        v = v1;
        bool res = false;
        if (v >= 30.0) {
            cnt++;
            v = c;
            u = u + d;
            res = true;
        }
        if (t == T) {
            if (v < vmin) vmin = v;
            if (v > vmax) vmax = v;
            if (cnt < cmin) cmin = cnt;
            if (cnt > cmax) cmax = cnt;
        }
        return res;
    }
};

class Edge {
public:
    int t, D;
    double w;
    queue<int> timestamps;

    Edge() {}

    Edge(int _t, int _D, double _w):
        t(_t), D(_D), w(_w) {}
} pool[MAX];
int poolHead = 0;

Neuron neurons[MAX];
int pulses[MAX];
vector<int> edges[2*MAX];
vector<int> edges2[MAX];

static unsigned long seed = 1;

/* RAND_MAX assumed to be 32767 */
int myrand(void) {
    seed = seed * 1103515245 + 12345;
    return((unsigned)(seed/65536) % 32768);
}

int main() {
    // start
    int N, S, P, RN, r, s, t, D, cnt = 0;
    double w, dt, v, u, a, b, c, d, I;
    scanf("%d %d %d %d %lf", &N, &S, &P, &T, &dt);
    while (cnt < N) {
        scanf("%d %lf %lf %lf %lf %lf %lf", &RN, &v, &u, &a, &b, &c, &d);
        for (int i = 0; i < RN; i++)
            neurons[cnt+i] = Neuron(v, u, a, b, c, d);
        cnt += RN;
    }
    for (int i = 0; i < P; i++) {
        scanf("%d", &r);
        pulses[i] = r;
    }
    for (int i = 0; i < S; i++) {
        scanf("%d %d %lf %d", &s, &t, &w, &D);
        pool[poolHead++] = Edge(t, D, w);
        edges[s].push_back(poolHead-1);
        edges2[t].push_back(poolHead-1);
    }
    // simulation
    for (t = 1; t <= T; t++) {
        // neurons
        for (int i = 0; i < N; i++) {
            int k1 = t, k2 = i;
            I = 0.0;
            for (int idx: edges2[i]) {
                if (!pool[idx].timestamps.empty() && pool[idx].timestamps.front() == t) {
                    I += pool[idx].w;
                    pool[idx].timestamps.pop();
                }
            }
            if (neurons[i].update(I, dt, t)) {
                for (int idx: edges[i])
                    pool[idx].timestamps.push(t+pool[idx].D);
            }
        }
        // pulses
        for (int i = 0; i < P; i++) {
            if (pulses[i] > myrand()) {
                for (int idx: edges[i+N]) {
                    pool[idx].timestamps.push(t+pool[idx].D);
                }
            }
        }
    }
    printf("%.3lf %.3lf\n%d %d\n", vmin, vmax, cmin, cmax);
    return 0;
}