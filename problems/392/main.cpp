#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

// 392 GCD Subsets: for each g, let cnt[g] = number of x_i divisible by g, so
// f[g] = 2^cnt[g]-1 counts non-empty subsets whose elements are ALL divisible by
// g (their gcd is therefore some multiple of g). The count with gcd EXACTLY g is
// obtained by Mobius-style inclusion-exclusion over multiples, processed from
// large g down to small g (harmonic-sum sieve, O(n log n)).
ll pw(ll b, ll e, ll m) {
    ll r = 1 % m; b %= m;
    while (e) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> x(n);
    for (auto &v : x) scanf("%d", &v);

    vector<int> cnt(n + 1, 0);
    for (int v : x) cnt[v]++;

    vector<ll> f(n + 1, 0);
    for (int g = 1; g <= n; g++) {
        ll c = 0;
        for (int m = g; m <= n; m += g) c += cnt[m];
        f[g] = (c == 0) ? 0 : (pw(2, c, MOD) - 1 + MOD) % MOD;
    }

    vector<ll> exact(n + 1, 0);
    for (int g = n; g >= 1; g--) {
        ll val = f[g];
        for (int m = 2 * g; m <= n; m += g) val = (val - exact[m] % MOD + MOD) % MOD;
        exact[g] = val;
    }

    for (int g = 1; g <= n; g++) printf("%lld ", exact[g]);
    printf("\n");
}
