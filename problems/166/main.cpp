#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7, P1 = MOD - 1, M2 = 2 * (MOD - 1);
long long pw(long long a, long long b, long long m) { a %= m; if (a < 0) a += m; long long r = 1; while (b) { if (b & 1) r = r * a % m; a = a * a % m; b >>= 1; } return r; }
long long inv(long long a) { return pw(a, MOD - 2, MOD); }
int main() {
    int n; scanf("%d", &n);
    vector<long long> x(n), k(n);
    long long num = 1, sum = 1, D2 = 1;
    bool Deven = false;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &x[i], &k[i]);
        num = num * ((k[i] + 1) % MOD) % MOD;
        long long t = (pw(x[i], k[i] + 1, MOD) - 1 + MOD) % MOD;
        t = t * inv((x[i] - 1) % MOD) % MOD;
        sum = sum * t % MOD;
        D2 = D2 * ((k[i] + 1) % M2) % M2;  // number of divisors mod 2(p-1)
        if (k[i] % 2 == 1) Deven = true;   // D even iff some (k+1) even iff some k odd
    }
    // product of divisors = n^(D/2) = prod x_i^(k_i * D/2)
    long long prod = 1;
    if (Deven) {
        long long half = (D2 / 2) % P1;
        for (int i = 0; i < n; i++) prod = prod * pw(x[i], (k[i] % P1) * half % P1, MOD) % MOD;
    } else {
        long long Dm = D2 % P1;
        for (int i = 0; i < n; i++) prod = prod * pw(x[i], ((k[i] / 2) % P1) * Dm % P1, MOD) % MOD;
    }
    printf("%lld %lld %lld\n", num, sum, prod);
}
