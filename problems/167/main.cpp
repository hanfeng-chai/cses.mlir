#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n; int k;
    scanf("%lld %d", &n, &k);
    vector<long long> a(k);
    for (auto &x : a) scanf("%lld", &x);
    long long ans = 0;
    for (int mask = 1; mask < (1 << k); mask++) {  // inclusion-exclusion over subsets of primes
        __int128 prod = 1; int bits = 0; bool over = false;
        for (int i = 0; i < k; i++)
            if (mask >> i & 1) { prod *= a[i]; bits++; if (prod > n) { over = true; break; } }
        if (over) continue;
        long long term = n / (long long)prod;
        ans += (bits & 1) ? term : -term;
    }
    printf("%lld\n", ans);
}
