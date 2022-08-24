#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 110

int current[MAX] = {0};
int pending[MAX] = {0};
int remaining[MAX] = {0};
int sorted[MAX] = {0};
int mask[MAX] = {0};

int main() {
    int n, m, w, d, x, k;
    int t, pre = 0, diff = 0;
    char op;
    scanf("%d %d %d %d\n", &n, &m, &w, &d);
    for (int i = 0; i < m; i++) {
        scanf("%c %d", &op, &t);
        // update data
        diff = t - pre;
        pre = t;
        for (int j = 1; j <= n; j++) {
            if (remaining[j] > 0) {
                remaining[j] -= diff;
                if (remaining[j] <= 0) {
                    current[j] = pending[j];
                    remaining[j] = 0;
                }
            }
        }
        if (op == 'R') {
            for (int j = 0; j < MAX; j++) {
                mask[j] = 0;
                sorted[j] = current[j];
            }
            sort(sorted+1, sorted+n+1);
            int target = sorted[(n+1)/2];
            int v = 0, cnt = 0;
            for (int j = 0; j < w; j++) {
                scanf("%d", &x);
                mask[x] = 1;
                v += 1;
                if (current[x] == target) {
                    cnt += 1;
                } else if (pending[x] < target) {
                    pending[x] = target;
                    remaining[x] = d;
                }
            }
            if (cnt < w) {
                for (int j = 1; j <= n; j++) {
                    if (mask[j] == 0) {
                        v += 1;
                        mask[j] = 1;
                        if (current[x] == target) {
                            cnt += 1;
                        } else if (pending[x] < target) {
                            pending[x] = target;
                            remaining[x] = d;
                        }
                        if (cnt >= w) break;
                    }
                }
            }
            getchar();
            printf("%d %d\n", v, target);
        } else if (op == 'W') {
            scanf("%d", &k);
            for (int j = 0; j < k; j++) {
                scanf("%d", &x);
                if (pending[x] < t + d) {
                    pending[x] = t + d;
                    remaining[x] = d;
                }
            }
            getchar();
        }
    }
    return 0;
}