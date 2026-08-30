#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long pw(long long a, long long b) { long long r = 1; a %= MOD; while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; } return r; }
int main() {
    long long n; scanf("%lld", &n);
    long long nn = n * n;  // up to 1e18
    // Burnside over 4 rotations: (2^(n^2) + 2*2^(ceil(n^2/4)) + 2^(ceil(n^2/2))) / 4
    long long e1 = nn % (MOD - 1), e90 = ((nn + 3) / 4) % (MOD - 1), e180 = ((nn + 1) / 2) % (MOD - 1);
    long long ans = (pw(2, e1) + 2 * pw(2, e90) + pw(2, e180)) % MOD * pw(4, MOD - 2) % MOD;
    printf("%lld\n", ans);
}
