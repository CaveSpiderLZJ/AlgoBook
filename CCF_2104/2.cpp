#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX 605
#define R_MAX 105

int n, L, r, t;
int img[MAX][MAX] = {0};
int rowSum[MAX] = {0};
int colSum[MAX][MAX] = {0};

int pixel(int i, int j) {
    if (0<=i && i<n && 0<=j && j<n)
        return img[i][j];
    return 0;
}

int pixelCnt(int i, int j) {
    int x = min(i+r, n-1) - max(i-r, 0);
    int y = min(j+r, n-1) - max(j-r, 0);
    return (x+1) * (y+1);
}

int main() {
    scanf("%d %d %d %d", &n, &L, &r, &t);
    int v, res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &v);
            img[i][j] = v;
        }
    }
    // row sum
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j <= r; j++)
            sum += img[i][j];
        rowSum[i] = sum;
    }
    // col sum
    for (int j = 0; j < n; j++) {
        int sum = 0;
        for (int i = 0; i < r; i++)
            sum += img[i][j];
        for (int i = 0; i < n; i++) {
            sum += pixel(i+r, j);
            sum -= pixel(i-r-1, j);
            colSum[i][j] = sum;
        }
    }
    for (int i = 0; i < n; i++) {
        int base = 0;
        for (int j = max(0, i-r); j <= min(n-1, i+r); j++)
            base += rowSum[j];
        if (base <= t * pixelCnt(i, 0)) res++;
        for (int j = 1; j < n; j++) {
            if (j+r < n) base += colSum[i][j+r];
            if (j-r-1 >= 0) base -= colSum[i][j-r-1];
            if (base <= t * pixelCnt(i, j)) res++;
        }
    }
    printf("%d\n", res);
    return 0;
}