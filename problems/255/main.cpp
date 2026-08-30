#include <bits/stdc++.h>
using namespace std;
int n;
int par[100005], rnk_[100005], comps;
vector<pair<int, int>> undo;  // DSU with rollback (union by rank, no path compression)
int find(int x) { while (par[x] != x) x = par[x]; return x; }
void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) { undo.push_back({-1, -1}); return; }
    if (rnk_[a] < rnk_[b]) swap(a, b);
    undo.push_back({b, rnk_[a] == rnk_[b] ? 1 : 0});
    par[b] = a; if (rnk_[a] == rnk_[b]) rnk_[a]++;
    comps--;
}
void rollback() {
    auto [b, rf] = undo.back(); undo.pop_back();
    if (b == -1) return;
    int a = par[b]; par[b] = b; if (rf) rnk_[a]--; comps++;
}
int K;
vector<vector<pair<int, int>>> segE;
void add(int node, int lo, int hi, int ql, int qr, pair<int, int> e) {
    if (qr < lo || hi < ql) return;
    if (ql <= lo && hi <= qr) { segE[node].push_back(e); return; }
    int mid = (lo + hi) / 2; add(2 * node, lo, mid, ql, qr, e); add(2 * node + 1, mid + 1, hi, ql, qr, e);
}
vector<int> ans;
void dfs(int node, int lo, int hi) {
    int cnt = 0;
    for (auto &e : segE[node]) { unite(e.first, e.second); cnt++; }
    if (lo == hi) ans[lo] = comps;
    else { int mid = (lo + hi) / 2; dfs(2 * node, lo, mid); dfs(2 * node + 1, mid + 1, hi); }
    while (cnt--) rollback();
}
int main() {
    int m, k; scanf("%d %d %d", &n, &m, &k); K = k;
    map<pair<int, int>, int> active;
    for (int i = 0; i < m; i++) { int a, b; scanf("%d %d", &a, &b); if (a > b) swap(a, b); active[{a, b}] = 0; }
    vector<tuple<int, int, int, int>> iv;
    for (int t = 1; t <= k; t++) {
        int type, a, b; scanf("%d %d %d", &type, &a, &b); if (a > b) swap(a, b);
        if (type == 1) active[{a, b}] = t;
        else { int st = active[{a, b}]; active.erase({a, b}); iv.push_back({a, b, st, t - 1}); }
    }
    for (auto &[e, st] : active) iv.push_back({e.first, e.second, st, k});
    segE.assign(4 * (k + 1), {});
    for (auto &[a, b, lo, hi] : iv) if (lo <= hi) add(1, 0, k, lo, hi, {a, b});
    for (int i = 1; i <= n; i++) { par[i] = i; rnk_[i] = 0; } comps = n;
    ans.assign(k + 1, 0);
    dfs(1, 0, k);
    string out;
    for (int t = 0; t <= k; t++) { out += to_string(ans[t]); out += " \n"[t == k]; }
    cout << out;
}
