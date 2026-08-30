#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef __uint128_t u128;
u64 mulmod(u64 a, u64 b, u64 m) { return (u128)a * b % m; }
u64 pw(u64 a, u64 b, u64 m) { u64 r = 1; a %= m; while (b) { if (b & 1) r = mulmod(r, a, m); a = mulmod(a, a, m); b >>= 1; } return r; }
bool isP(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) if (n % p == 0) return n == p;
    u64 d = n - 1; int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    for (u64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        u64 x = pw(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int i = 0; i < s - 1; i++) { x = mulmod(x, x, n); if (x == n - 1) { ok = true; break; } }
        if (!ok) return false;
    }
    return true;
}
int main() {
    int t; scanf("%d", &t);
    while (t--) { u64 n; scanf("%llu", &n); n++; while (!isP(n)) n++; printf("%llu\n", n); }
}
