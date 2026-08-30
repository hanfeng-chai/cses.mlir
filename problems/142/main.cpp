#include <bits/stdc++.h>
using namespace std;
// Persistent segment tree: each list entry keeps a root; copies share structure.
struct Node { long long sum; int l, r; };
vector<Node> t;
int n;
int build(int lo, int hi, vector<long long> &v) {
    int id = t.size(); t.push_back({0, 0, 0});
    if (lo == hi) { t[id].sum = v[lo]; return id; }
    int m = (lo + hi) / 2, L = build(lo, m, v), R = build(m + 1, hi, v);
    t[id].l = L; t[id].r = R; t[id].sum = t[L].sum + t[R].sum;
    return id;
}
int update(int prev, int lo, int hi, int pos, long long val) {
    int id = t.size(); t.push_back(t[prev]);
    if (lo == hi) { t[id].sum = val; return id; }
    int m = (lo + hi) / 2;
    if (pos <= m) t[id].l = update(t[prev].l, lo, m, pos, val);
    else t[id].r = update(t[prev].r, m + 1, hi, pos, val);
    t[id].sum = t[t[id].l].sum + t[t[id].r].sum;
    return id;
}
long long query(int id, int lo, int hi, int ql, int qr) {
    if (qr < lo || hi < ql) return 0;
    if (ql <= lo && hi <= qr) return t[id].sum;
    int m = (lo + hi) / 2;
    return query(t[id].l, lo, m, ql, qr) + query(t[id].r, m + 1, hi, ql, qr);
}
int main() {
    int q; scanf("%d %d", &n, &q);
    vector<long long> v(n + 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &v[i]);
    t.reserve((size_t)(n + q) * 20 + 10);
    vector<int> root;
    root.push_back(build(1, n, v));
    while (q--) {
        int type; scanf("%d", &type);
        if (type == 1) { int k, a; long long x; scanf("%d %d %lld", &k, &a, &x); root[k - 1] = update(root[k - 1], 1, n, a, x); }
        else if (type == 2) { int k, a, b; scanf("%d %d %d", &k, &a, &b); printf("%lld\n", query(root[k - 1], 1, n, a, b)); }
        else { int k; scanf("%d", &k); root.push_back(root[k - 1]); }
    }
}
