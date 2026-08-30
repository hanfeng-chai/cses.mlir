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
    static char buf[1000006]; scanf("%s", buf);
    int k = strlen(buf), b = 0;
    for (int i = 0; i < k; i++) { b += (buf[i] == '(') ? 1 : -1; if (b < 0) { printf("0\n"); return 0; } }
    int L = n - k;  // remaining steps; need a path from height b to 0 staying >= 0
    if ((L - b) % 2 != 0 || b > L) { printf("0\n"); return 0; }
    int up = (L - b) / 2;  // reflection: good = C(L,up) - C(L,up-1)
    printf("%lld\n", (C(L, up) - C(L, up - 1) + MOD) % MOD);
}
