#include<cstdio>
#include<cstdlib>

int main() {
    int n, N, r, a = 0, b, x, y;
    long long error = 0;
    scanf("%d %d", &n, &N);
    r = N / (n+1);
    for (int i = 0; i <= n; i++) {
        if (i < n) scanf("%d", &b);
        else b = N;
        x = a; y = a/r*r+r; a = b;
        while (y < b) {
            error += abs(x/r-i) * (y-x);
            x = y; y += r;
        }
        error += abs(x/r-i) * (b-x);
    }
    printf("%lld\n", error);
    return 0;
}