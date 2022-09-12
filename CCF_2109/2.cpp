#include<cstdio>
#include<unordered_map>
#define MAX 10005

int main() {
    int n, a = 0, b, c, base = 0;
    scanf("%d %d", &n, &b);
    std::unordered_map<int, int> mins, maxs;
    if (b > a) base++;
    for (int i = 0; i < n-1; i++) {
        scanf("%d", &c);
        if (c > 0 && b == 0) base++;
        if (c == b) continue;
        if (b > a && b > c) {
            if (maxs.find(b) == maxs.end()) maxs[b] = 1;
            else maxs[b] += 1;
        }
        if (b < a && b < c) {
            if (mins.find(b) == mins.end()) mins[b] = 1;
            else mins[b] += 1;
        }
        a = b; b = c;
    }
    if (b > a) {
        if (maxs.find(b) == maxs.end()) maxs[b] = 1;
        else maxs[b] += 1;
    }
    int res = base;
    for (int i = 1; i < MAX; i++) {
        if (mins.find(i) != mins.end()) base += mins[i];
        if (maxs.find(i) != maxs.end()) base -= maxs[i];
        if (base > res) res = base;
    }
    printf("%d\n", res);
    return 0;
}