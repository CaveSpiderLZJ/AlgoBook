#include<cstdio>

int main() {
    int n, a = -1, b, min = 0, max = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &b);
        if (b > a) min += b;
        max += b; a = b;
    }
    printf("%d\n%d\n", max, min);
    return 0;
}