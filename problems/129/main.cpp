#include <bits/stdc++.h>
using namespace std;
// Segment tree storing (sum, best prefix sum >= 0) for max prefix queries.
int n, q;
struct Node { long long sum, pre; };
vector<Node> seg;
Node merge(const Node &a, const Node &b) { return {a.sum + b.sum, max(a.pre, a.sum + b.pre)}; }
void build(int p, int l, int r, vector<long long> &v) {
    if (l == r) { seg[p] = {v[l], max(0LL, v[l])}; return; }
    int m = (l + r) / 2;
    build(2 * p, l, m, v); build(2 * p + 1, m + 1, r, v);
    seg[p] = merge(seg[2 * p], seg[2 * p + 1]);
}
void upd(int p, int l, int r, int pos, long long val) {
    if (l == r) { seg[p] = {val, max(0LL, val)}; return; }
    int m = (l + r) / 2;
    if (pos <= m) upd(2 * p, l, m, pos, val); else upd(2 * p + 1, m + 1, r, pos, val);
    seg[p] = merge(seg[2 * p], seg[2 * p + 1]);
}
Node qry(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg[p];
    int m = (l + r) / 2;
    if (qr <= m) return qry(2 * p, l, m, ql, qr);
    if (ql > m) return qry(2 * p + 1, m + 1, r, ql, qr);
    return merge(qry(2 * p, l, m, ql, qr), qry(2 * p + 1, m + 1, r, ql, qr));
}
int main() {
    scanf("%d %d", &n, &q);
    vector<long long> v(n + 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &v[i]);
    seg.assign(4 * (n + 1), {0, 0});
    build(1, 1, n, v);
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) { int k; long long u; scanf("%d %lld", &k, &u); upd(1, 1, n, k, u); }
        else { int a, b; scanf("%d %d", &a, &b); printf("%lld\n", qry(1, 1, n, a, b).pre); }
    }
}
