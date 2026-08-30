#include <bits/stdc++.h>
using namespace std;
int n, q;
vector<int> seg;
void upd(int p, int v) { p += n; seg[p] = v; for (p >>= 1; p >= 1; p >>= 1) seg[p] = min(seg[2 * p], seg[2 * p + 1]); }
int qmin(int l, int r) {  // inclusive, 0-indexed
    int res = INT_MAX;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = min(res, seg[l++]);
        if (r & 1) res = min(res, seg[--r]);
    }
    return res;
}
int main() {
    scanf("%d %d", &n, &q);
    seg.assign(2 * n, INT_MAX);
    for (int i = 0; i < n; i++) scanf("%d", &seg[n + i]);
    for (int i = n - 1; i >= 1; i--) seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) { int k, u; scanf("%d %d", &k, &u); upd(k - 1, u); }
        else { int a, b; scanf("%d %d", &a, &b); printf("%d\n", qmin(a - 1, b - 1)); }
    }
}
