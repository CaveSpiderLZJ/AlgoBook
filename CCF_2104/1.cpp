#include<cstdio>

int main() {
    int n, m, L, x;
    scanf("%d %d %d", &n, &m, &L);
    int* cnt = new int[L];
    for(int i = 0; i < L; i++) cnt[i] = 0;
    for (int i = 0; i < n*m; i++) {
        scanf("%d", &x);
        cnt[x]++;
    }
    for (int i = 0; i < L; i++)
        printf("%d ", cnt[i]);
    printf("\n");
    return 0;
}