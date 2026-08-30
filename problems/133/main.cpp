#include <bits/stdc++.h>
using namespace std;
// Point updates; report max subarray sum of the whole array (empty allowed).
int n, m;
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
void upd(int p, int l, int r, int pos, long long val) {
    if (l == r) { seg[p] = mk(val); return; }
    int md = (l + r) / 2;
    if (pos <= md) upd(2 * p, l, md, pos, val); else upd(2 * p + 1, md + 1, r, pos, val);
    seg[p] = merge(seg[2 * p], seg[2 * p + 1]);
}
int main() {
    scanf("%d %d", &n, &m);
    vector<long long> v(n + 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &v[i]);
    seg.assign(4 * (n + 1), {0, 0, 0, 0});
    build(1, 1, n, v);
    while (m--) {
        int k; long long x; scanf("%d %lld", &k, &x);
        upd(1, 1, n, k, x);
        printf("%lld\n", seg[1].best);
    }
}
