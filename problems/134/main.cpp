#include <bits/stdc++.h>
using namespace std;
// Range max subarray sum queries (empty allowed).
int n, q;
struct Node { long long sum, pre, suf, best; };
vector<Node> seg;
Node mk(long long v) { return {v, max(0LL, v), max(0LL, v), max(0LL, v)}; }
Node merge(const Node &a, const Node &b) {
    return {a.sum + b.sum, max(a.pre, a.sum + b.pre), max(b.suf, b.sum + a.suf),
            max({a.best, b.best, a.suf + b.pre})};
}
void build(int p, int l, int r, vector<long long> &v) {
    if (l == r) { seg[p] = mk(v[l]); return; }
    int md = (l + r) / 2;
    build(2 * p, l, md, v); build(2 * p + 1, md + 1, r, v);
    seg[p] = merge(seg[2 * p], seg[2 * p + 1]);
}
Node qry(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg[p];
    int md = (l + r) / 2;
    if (qr <= md) return qry(2 * p, l, md, ql, qr);
    if (ql > md) return qry(2 * p + 1, md + 1, r, ql, qr);
    return merge(qry(2 * p, l, md, ql, qr), qry(2 * p + 1, md + 1, r, ql, qr));
}
int main() {
    scanf("%d %d", &n, &q);
    vector<long long> v(n + 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &v[i]);
    seg.assign(4 * (n + 1), {0, 0, 0, 0});
    build(1, 1, n, v);
    while (q--) {
        int a, b; scanf("%d %d", &a, &b);
        printf("%lld\n", qry(1, 1, n, a, b).best);
    }
}
