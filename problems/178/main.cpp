#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long pw(long long a, long long b) { long long r = 1; a %= MOD; while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; } return r; }
long long phi(long long x) { long long r = x; for (long long p = 2; p * p <= x; p++) if (x % p == 0) { while (x % p == 0) x /= p; r -= r / p; } if (x > 1) r -= r / x; return r; }
int main() {
    long long n, m; scanf("%lld %lld", &n, &m);
    long long ans = 0;
    for (long long d = 1; d * d <= n; d++)  // necklaces: (1/n) sum_{g|n} phi(n/g) m^g
        if (n % d == 0) {
            ans = (ans + phi(n / d) % MOD * pw(m, d)) % MOD;
            if (d != n / d) ans = (ans + phi(d) % MOD * pw(m, n / d)) % MOD;
        }
    ans = ans * pw(n, MOD - 2) % MOD;
    printf("%lld\n", ans);
}
