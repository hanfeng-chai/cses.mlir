#include <bits/stdc++.h>
using namespace std;
// Centroid decomposition: count paths with exactly K edges.
int n, K;
vector<vector<int>> adj;
vector<char> removed;
vector<int> sz, par;
vector<long long> cnt;
long long ans = 0;
int findCentroid(int u) {
    vector<int> ord = {u}; par[u] = 0;
    for (int i = 0; i < (int)ord.size(); i++) { int x = ord[i]; for (int v : adj[x]) if (!removed[v] && v != par[x]) { par[v] = x; ord.push_back(v); } }
    int total = ord.size();
    for (int i = (int)ord.size() - 1; i >= 0; i--) { int x = ord[i]; sz[x] = 1; for (int v : adj[x]) if (!removed[v] && v != par[x]) sz[x] += sz[v]; }
    for (int x : ord) {
        int mx = total - sz[x];
        for (int v : adj[x]) if (!removed[v] && v != par[x]) mx = max(mx, sz[v]);
        if (mx <= total / 2) return x;
    }
    return u;
}
void process(int c) {
    cnt[0] = 1;
    vector<int> touched = {0};
    for (int w : adj[c]) if (!removed[w]) {
        vector<int> ord = {w}, dep = {1}; par[w] = c;
        for (int i = 0; i < (int)ord.size(); i++) { int x = ord[i]; for (int v : adj[x]) if (!removed[v] && v != par[x]) { par[v] = x; ord.push_back(v); dep.push_back(dep[i] + 1); } }
        for (int d : dep) if (K - d >= 0 && K - d <= n) ans += cnt[K - d];
        for (int d : dep) { if (d <= n) { cnt[d]++; touched.push_back(d); } }
    }
    for (int d : touched) cnt[d] = 0;
}
void decompose(int u) {
    int c = findCentroid(u);
    process(c);
    removed[c] = 1;
    for (int v : adj[c]) if (!removed[v]) decompose(v);
}
int main() {
    scanf("%d %d", &n, &K);
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    removed.assign(n + 1, 0); sz.assign(n + 1, 0); par.assign(n + 1, 0); cnt.assign(n + 1, 0);
    decompose(1);
    printf("%lld\n", ans);
}
