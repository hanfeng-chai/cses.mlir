#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7, INV2 = (MOD + 1) / 2;
long long S(long long x) { x %= MOD; return x * ((x + 1) % MOD) % MOD * INV2 % MOD; }  // sum 1..x mod p
int main() {
    long long n; scanf("%lld", &n);
    long long ans = 0;
    for (long long d = 1; d <= n;) {  // sum_{d} d * floor(n/d), grouped by equal quotient
        long long q = n / d, hi = n / q;
        ans = (ans + (q % MOD) * ((S(hi) - S(d - 1) + MOD) % MOD)) % MOD;
        d = hi + 1;
    }
    printf("%lld\n", ans);
}
