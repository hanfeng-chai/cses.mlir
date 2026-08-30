#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef __int128 u128;
typedef vector<u64> Big;  // base 2^32, little-endian limbs each < 2^32

void norm(Big &a) { while (a.size() > 1 && a.back() == 0) a.pop_back(); }
Big fromU64(u64 x) { Big a; a.push_back(x & 0xffffffffULL); a.push_back(x >> 32); norm(a); return a; }
Big mulSmall(const Big &a, u64 x) {
    Big r(a.size() + 2, 0);
    u128 carry = 0;
    size_t i = 0;
    for (; i < a.size(); i++) { u128 cur = (u128)a[i] * x + carry; r[i] = (u64)(cur & 0xffffffffULL); carry = cur >> 32; }
    while (carry) { r[i++] = (u64)(carry & 0xffffffffULL); carry >>= 32; }
    norm(r); return r;
}
Big addBig(const Big &a, const Big &b) {
    Big r; u128 carry = 0; size_t n = max(a.size(), b.size());
    for (size_t i = 0; i < n; i++) { u128 cur = carry; if (i < a.size()) cur += a[i]; if (i < b.size()) cur += b[i]; r.push_back((u64)(cur & 0xffffffffULL)); carry = cur >> 32; }
    if (carry) r.push_back((u64)carry);
    norm(r); return r;
}
int cmpBig(const Big &a, const Big &b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    for (int i = a.size() - 1; i >= 0; i--) if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    return 0;
}
Big subBig(const Big &a, const Big &b) {  // a >= b
    Big r; long long borrow = 0;
    for (size_t i = 0; i < a.size(); i++) {
        long long cur = (long long)a[i] - borrow - (i < b.size() ? (long long)b[i] : 0);
        if (cur < 0) { cur += (1LL << 32); borrow = 1; } else borrow = 0;
        r.push_back((u64)cur);
    }
    norm(r); return r;
}
Big divSmall(const Big &a, u64 d) {  // exact/floor division by small d < 2^32
    Big r(a.size(), 0); u128 cur = 0;
    for (int i = a.size() - 1; i >= 0; i--) { cur = (cur << 32) | a[i]; r[i] = (u64)(cur / d); cur %= d; }
    norm(r); return r;
}
int main() {
    int n; scanf("%d", &n);
    vector<long long> r(n);
    for (auto &v : r) scanf("%lld", &v);
    // common denominator D divisible by every m*q (m,q <= 100)
    Big D = fromU64(1);
    auto mulP = [&](u64 p, int e) { for (int i = 0; i < e; i++) D = mulSmall(D, p); };
    mulP(2, 12); mulP(3, 8); mulP(5, 4); mulP(7, 4);
    for (int p = 11; p <= 97; p++) { bool pr = true; for (int j = 2; j * j <= p; j++) if (p % j == 0) { pr = false; break; } if (pr) mulP(p, 2); }
    Big N = fromU64(0);
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++) {
            long long m = r[a], q = r[b], s;
            if (m - 1 <= q) s = (m - 1) * m / 2;
            else s = q * (q + 1) / 2 + (m - (q + 1)) * q;
            if (s == 0) continue;
            Big t = mulSmall(divSmall(D, (u64)m * q), (u64)s);  // s * D/(m*q)
            N = addBig(N, t);
        }
    Big Npq = mulSmall(N, 1000000ULL);  // value * 1e6 = Npq / D
    u64 lo = 0, hi = 200000000000ULL;
    while (lo < hi) { u64 mid = lo + (hi - lo + 1) / 2; if (cmpBig(mulSmall(D, mid), Npq) <= 0) lo = mid; else hi = mid - 1; }
    u64 T = lo;
    Big rem2 = mulSmall(subBig(Npq, mulSmall(D, T)), 2);
    int c = cmpBig(rem2, D);
    if (c > 0) T++;
    else if (c == 0 && (T & 1ULL)) T++;  // ties to even
    printf("%llu.%06llu\n", T / 1000000ULL, T % 1000000ULL);
}
