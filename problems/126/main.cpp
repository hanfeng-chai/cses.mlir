#include <bits/stdc++.h>
using namespace std;
int n, m, sz;
vector<long long> seg;
int main() {
    scanf("%d %d", &n, &m);
    sz = 1;
    while (sz < n) sz <<= 1;  // pad to a power of two for clean top-down descent
    seg.assign(2 * sz, 0);
    for (int i = 0; i < n; i++) scanf("%lld", &seg[sz + i]);
    for (int i = sz - 1; i >= 1; i--) seg[i] = max(seg[2 * i], seg[2 * i + 1]);
    while (m--) {
        long long r; scanf("%lld", &r);
        if (seg[1] < r) { printf("0 "); continue; }
        int p = 1;
        while (p < sz) p = (seg[2 * p] >= r) ? 2 * p : 2 * p + 1;  // leftmost hotel with enough rooms
        printf("%d ", p - sz + 1);
        seg[p] -= r;
        for (p >>= 1; p >= 1; p >>= 1) seg[p] = max(seg[2 * p], seg[2 * p + 1]);
    }
    printf("\n");
}
