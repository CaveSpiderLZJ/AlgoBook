#include<cstdio>

int main() {
    int n, N, a = 0, b, res = 0;;
    scanf("%d %d", &n, &N);
    for (int i = 0; i < n; i++) {
        scanf("%d", &b);
        res += i * (b-a);
        a = b;
    }
    res += n * (N-a);
    printf("%d\n", res);
    return 0;
}