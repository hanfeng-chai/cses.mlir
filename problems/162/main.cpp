#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long pw(long long a, long long b, long long m) { a %= m; if (a < 0) a += m; long long r = 1; while (b) { if (b & 1) r = r * a % m; a = a * a % m; b >>= 1; } return r; }
int main() {
    int n; scanf("%d", &n);
    while (n--) {
        long long a, b, c; scanf("%lld %lld %lld", &a, &b, &c);
        if (a % MOD == 0) {  // a == 0 (since a < MOD): 0^(b^c) is 1 only if exponent is 0
            printf("%d\n", (b == 0 && c > 0) ? 1 : 0);
        } else {
            long long e = pw(b, c, MOD - 1);  // b^c mod (p-1), Fermat
            printf("%lld\n", pw(a, e, MOD));
        }
    }
}
