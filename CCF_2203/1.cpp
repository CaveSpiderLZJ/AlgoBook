#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int main() {
    int n, k, x, y, cnt = 0;
    scanf("%d %d", &n, &k);
    set<int> init = {0};
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &x, &y);
        if (init.find(y) == init.end())
            cnt += 1;
        init.insert(x);
    }
    printf("%d\n", cnt);
    return 0;
}