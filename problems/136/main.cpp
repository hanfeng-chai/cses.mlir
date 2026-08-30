#include <bits/stdc++.h>
using namespace std;
// "all distinct in [l,r]" iff min over i in [l,r] of nxt[i] > r,
// where nxt[i] = next position with the same value. Maintain with per-value sets.
int n, q, SZ;
vector<int> seg;
void supd(int p, int v) { for (seg[p += SZ] = v, p >>= 1; p >= 1; p >>= 1) seg[p] = min(seg[2 * p], seg[2 * p + 1]); }
int sqry(int l, int r) {
    int res = INT_MAX;
    for (l += SZ, r += SZ + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = min(res, seg[l++]);
        if (r & 1) res = min(res, seg[--r]);
    }
    return res;
}
int main() {
    scanf("%d %d", &n, &q);
    vector<int> a(n + 1);
    map<int, set<int>> pos;
    for (int i = 1; i <= n; i++) { scanf("%d", &a[i]); pos[a[i]].insert(i); }
    SZ = n + 1;
    int INF = n + 1;
    vector<int> nxt(n + 2, INF);
    for (auto &[v, s] : pos) { int prev = -1; for (int p : s) { if (prev != -1) nxt[prev] = p; prev = p; } }
    seg.assign(2 * SZ, INF);
    for (int i = 1; i <= n; i++) seg[SZ + i] = nxt[i];
    for (int i = SZ - 1; i >= 1; i--) seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    auto setNxt = [&](int i, int v) { nxt[i] = v; supd(i, v); };
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int k, u; scanf("%d %d", &k, &u);
            int ov = a[k];
            if (ov == u) continue;
            auto &s = pos[ov];
            auto it = s.find(k);
            int pred = -1, succ = INF;
            if (it != s.begin()) pred = *prev(it);
            if (next(it) != s.end()) succ = *next(it);
            if (pred != -1) setNxt(pred, succ);
            s.erase(it);
            auto &s2 = pos[u];
            auto jt = s2.insert(k).first;
            int pred2 = -1, succ2 = INF;
            if (jt != s2.begin()) pred2 = *prev(jt);
            if (next(jt) != s2.end()) succ2 = *next(jt);
            if (pred2 != -1) setNxt(pred2, k);
            setNxt(k, succ2);
            a[k] = u;
        } else {
            int l, r; scanf("%d %d", &l, &r);
            puts(sqry(l, r) > r ? "YES" : "NO");
        }
    }
}
