#include<cstdio>
#include<vector>
using namespace std;
#define MAX 10000

bool mask[MAX];
vector<int> primes;

int main() {
    for (int i = 2; i < MAX; i++)
        mask[i] = true;
    mask[0] = mask[1] = false;
    for (int i = 2; i < MAX; i++) {
        if (mask[i]) primes.push_back(i);
        for (int j = 0; j < primes.size(); j++) {
            if (i * primes[j] >= MAX) break;
            mask[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
        }
    }
    return 0;
}