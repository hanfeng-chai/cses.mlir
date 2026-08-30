#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
const int MX = 1000002;
long long f[MX], invf[MX];
long long pw(long long a, long long b) { long long r = 1; a %= MOD; while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; } return r; }
long long C(int a, int b) { if (b < 0 || b > a) return 0; return f[a] * invf[b] % MOD * invf[a - b] % MOD; }
int main() {
    f[0] = 1; for (int i = 1; i < MX; i++) f[i] = f[i - 1] * i % MOD;
    invf[MX - 1] = pw(f[MX - 1], MOD - 2); for (int i = MX - 2; i >= 0; i--) invf[i] = invf[i + 1] * (i + 1) % MOD;
    int n; scanf("%d", &n);
    if (n & 1) { printf("0\n"); return 0; }
    int h = n / 2;
    printf("%lld\n", (C(n, h) - C(n, h + 1) + MOD) % MOD);  // Catalan number
}
