#include <bits/stdc++.h>
using namespace std;
// Heavy-Light Decomposition + iterative max segment tree for path-max with point updates.
int n, q;
vector<vector<int>> adj;
vector<int> par, depth, sz, heavy, head, pos;
vector<long long> seg;
void supd(int p, long long v) { for (seg[p += n] = v, p >>= 1; p >= 1; p >>= 1) seg[p] = max(seg[2 * p], seg[2 * p + 1]); }
long long sqry(int l, int r) {
    long long res = LLONG_MIN;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, seg[l++]);
        if (r & 1) res = max(res, seg[--r]);
    }
    return res;
}
int main() {
    scanf("%d %d", &n, &q);
    vector<long long> val(n + 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &val[i]);
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    par.assign(n + 1, 0); depth.assign(n + 1, 0); sz.assign(n + 1, 1);
    heavy.assign(n + 1, 0); head.assign(n + 1, 0); pos.assign(n + 1, 0);
    vector<int> order; order.reserve(n);
    {
        vector<char> vis(n + 1, 0); vis[1] = 1; vector<int> st = {1};
        while (!st.empty()) { int u = st.back(); st.pop_back(); order.push_back(u); for (int v : adj[u]) if (!vis[v]) { vis[v] = 1; par[v] = u; depth[v] = depth[u] + 1; st.push_back(v); } }
    }
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i], best = 0;
        for (int v : adj[u]) if (v != par[u]) { sz[u] += sz[v]; if (sz[v] > best) { best = sz[v]; heavy[u] = v; } }
    }
    int timer = 0;
    {  // assign chain heads and positions; heavy child gets the contiguous next slot
        vector<pair<int, int>> st; st.push_back({1, 1});
        while (!st.empty()) {
            auto [u, h] = st.back(); st.pop_back();
            head[u] = h; pos[u] = timer++;
            for (int v : adj[u]) if (v != par[u] && v != heavy[u]) st.push_back({v, v});
            if (heavy[u]) st.push_back({heavy[u], h});
        }
    }
    seg.assign(2 * n, LLONG_MIN);
    for (int i = 1; i <= n; i++) seg[n + pos[i]] = val[i];
    for (int i = n - 1; i >= 1; i--) seg[i] = max(seg[2 * i], seg[2 * i + 1]);
    auto pathMax = [&](int a, int b) {
        long long res = LLONG_MIN;
        while (head[a] != head[b]) {
            if (depth[head[a]] < depth[head[b]]) swap(a, b);
            res = max(res, sqry(pos[head[a]], pos[a]));
            a = par[head[a]];
        }
        if (depth[a] > depth[b]) swap(a, b);
        return max(res, sqry(pos[a], pos[b]));
    };
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) { int s; long long x; scanf("%d %lld", &s, &x); supd(pos[s], x); }
        else { int a, b; scanf("%d %d", &a, &b); printf("%lld\n", pathMax(a, b)); }
    }
}
