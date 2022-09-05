#include <cstdio>
#include <cmath>
using namespace std;

#define MAX 1010

int main() {
    int n, v;
    double sum = 0, values[MAX];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v);
        sum += v;
        values[i] = v;
    }
    double mean = sum / n, std = 0.0;
    for (int i = 0; i < n; i++)
        std += (values[i] - mean) * (values[i] - mean);
    std = sqrt(std / n);
    for (int i = 0; i < n; i++)
        printf("%.8f\n", (values[i] - mean) / std);
    return 0;
}